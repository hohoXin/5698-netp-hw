/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-server-connection.h>
#include <service.h>
#include <iostream>
#include <cctype>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>


/**
 * Method use to accept a new connection from an opened server
 * @param server pointer to an EthConn, that points to a TcpServer
 * @return false if the object is not a TcpServer or if the accept fails
 */
bool acceptTcpConn(std::shared_ptr<EthConn> server) 
{
  // Exercise 2: call the acceptConn() method on the server (casting, if necessary)
  // If the call to acceptConn() returns true, print "server accepted client " and the IP
  // of the connected client using the getIp method, and return true
  // If the call to acceptConn() returns false, or if the cast does not go as expected, 
  // return false
}

int main(int argc, char** argv) 
{

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument
  const int listen_port = argc ==1 ? 55555 : atoi(argv[1]);
  std::shared_ptr<EthConn> server = std::make_shared<TcpServerConnection>(listen_port);

  for(int i = 0; i < 3; i++) {
    if(server->acceptConn()) {
      std::cout << *server << std::endl;
    } else {
      return -1;
    }
  }  

  // Exercise 9
  // block the execution of the current thread for 5 seconds

  std::cout << "Terminate the execution" << std::endl;
  return 0;

}
