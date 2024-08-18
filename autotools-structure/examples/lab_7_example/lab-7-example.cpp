/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-server.h>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string.h>
#include <iostream>
#include <cctype>

std::queue<MyBuffer> q; /**< queue to store data chunks to transmit**/
std::mutex queue_access_mt; /**<mutex to access the queue in thread safe way**/
std::atomic<bool> exit_flag{false}; /**<Exit flag to terminate the thread**/
std::atomic<int> transmission_result{0}; /**<Last transmission result**/
std::condition_variable queue_cv; /**<condition variable to wait for data**/

/**
 * Method used to accept a new connection from an opened server
 * @param server pointer to an EthConn, that points to a TcpServer
 * @return false if the object is not a TcpServer or if the accept fails
 */
bool acceptTcpConn(std::shared_ptr<EthConn> server) 
{
  auto casted_server = std::dynamic_pointer_cast<TcpServer>(server);
  if(casted_server != nullptr && casted_server->acceptConn()) {
    std::cout << "server accepted client " << casted_server->getIp() << std::endl;
    return true;
  }
  return false;
}

/**
 * Method used continuosly transmit data stored in the queue to the socket.
 * If no data is available within a certain time, it prints 
 * to the socket to provide some data.
 * @param pointer to an EthConn pointing to the server
 * @param timeout timeout in seconds
 */
void consumer(std::shared_ptr<EthConn> server, 
  std::chrono::seconds timeout) 
{
  while(!exit_flag) {
    std::unique_lock<std::mutex> lck(queue_access_mt);
    queue_cv.wait_for(lck, timeout, [&](){
      return exit_flag || !q.empty();
    });
    if(!q.empty()) {
      MyBuffer tx_buffer = q.front();
      q.pop();
      lck.unlock();
      if(server->transmit(tx_buffer) < 0) {
        transmission_result = 0;
      } else {
        transmission_result = 1;
      }
    } else if(!exit_flag) {
      lck.unlock();
      MyBuffer tx_buffer(150);
      std::string message = "Waiting data from user\n";
      std::cout << message ;
      memcpy(tx_buffer.dataAccess(), message.c_str(), message.size());
      tx_buffer.n_bytes = message.size();
      if(server->transmit(tx_buffer) < 0) {
        transmission_result = 0;
      } else {
        transmission_result = 1;
      }
    }
  }
}

int main(int argc, char** argv) 
{

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument
  const int listen_port = argc == 1 ? 55555 : atoi(argv[1]);
  std::shared_ptr<EthConn> server = std::make_shared<TcpServer>(listen_port);
  
  if(!acceptTcpConn(server)) {
    return -1;
  }

  std::thread consumer_thread(consumer, server, std::chrono::seconds{5});

  //producer
  for(int i = 0; i < 10; i++) {
    MyBuffer rx_buffer(MTU);

    int rx_size = server->receive(rx_buffer);
    if(rx_size > 0) {
      std::cout << "received = " << rx_buffer.dataAccess() 
                << "--- buffer.n_bytes = " << rx_buffer.n_bytes << std::endl;
    } else {
      exit_flag = true;
      queue_cv.notify_one();
      if(consumer_thread.joinable()) {
        consumer_thread.join();
      }
      return -1;
    }

    std::unique_lock<std::mutex> lck(queue_access_mt);
    q.push(rx_buffer);
    lck.unlock();
    queue_cv.notify_one();
  }  

  std::cout << *server << std::endl;
  exit_flag = true;
  queue_cv.notify_one();
  if(consumer_thread.joinable()) {
    consumer_thread.join();
  }
  return (int)transmission_result.load();

}