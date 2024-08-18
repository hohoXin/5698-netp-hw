/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <udp-wrapper.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

UdpWrapper::UdpWrapper(int port_num)
:
m_port{port_num},
m_last_recv_ip{},
m_exit{false},
m_sock_fd{-1}
{
  // open the m_sock_fd socket of type SOCK_DGRAM
  m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  // check if the socket creation was successful
  if (m_sock_fd < 0){ 
    std::cout << "ERROR: OPEN UDP SOCKET" << std::endl;
    return;
  }
  // call the function to set the options and bind,
  // and close the socket and return if not successful
  if(!optionsAndBind()) {
    std::cout << "ERROR: BIND" << std::endl;
    close(m_sock_fd);
    return;
  }
}

UdpWrapper::~UdpWrapper() {
  // call the function quit
  quit();
}


void 
UdpWrapper::quit() {
  // set m_exit to be true
  m_exit = true;

  // if m_sock_fd is open, close it and set the 
  // file descriptor to -1
  if(m_sock_fd >= 0){
    close(m_sock_fd);
    m_sock_fd = -1;
  }
}


void 
UdpWrapper::runServer() {
  // create a char buffer called buf, of size C_MTU
  char buf[C_MTU];


    // start a while loop to receive data and send application ACKs to this client
    // the loop ends when m_exit is true
    while(!m_exit) {

        // call recvData, passing buf, to receive data
        // save the return value of recvData in a data_size variable
        int data_size = recvData(buf);

        // check if the data_size is smaller than 0
        // if yes, set m_exit to true and break the loop
        if (data_size < 0) {
            std::cout << "Terminate - socket recvfrom error" << std::endl;
            m_exit = true;
            break;
        } 
        // // check if the data_size is equal to 0
        // // if yes, set m_exit to true and break the loop
        // else if (data_size == 0) {
        // std::cout << "Terminate - the other endpoint has closed the socket" << std::endl;
        // m_exit = true;
        // break;
        // } 
        else if(data_size > 0){
            // send an application ACK to the other endpoint
            std::string to_tx = "Packet ACK\n";
            
            if(sendData(to_tx.c_str(), to_tx.length()) >= 0) {
                // print the buf to the terminal
                std::cout << buf;
                std::cout << "UDP TX successful" << std::endl;
            } else {
                // if the transmission was not successful, set m_exit to true and break the loop
                std::cout << "Terminate - socket sendto error" << std::endl;
                m_exit = true;
                break;
            }
        }

        // // print the buf to the terminal
        // std::cout << buf;

        // reset the buffer for a new read using memset
        memset(buf, 0, C_MTU); // this cleans the buffer for a new read

    }
}


bool 
UdpWrapper::optionsAndBind() {
  // set the options for the socket
  int option(1);
  setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert m_port to network number format
  my_addr.sin_port = htons(m_port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the m_port
  if (bind(m_sock_fd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout << "ERROR: BIND SOCKET" << std::endl;
    if(m_sock_fd>=0) {
      close(m_sock_fd);
    }
    return false;
  }

  return true;
}


int 
UdpWrapper::recvData(char* buf)  
{
  if(m_sock_fd<0) {
    return -1;
  }

  socklen_t addrlen = sizeof(m_last_recv_ip);
  // call the recvfrom API
  int rcv_size = ::recvfrom(m_sock_fd, buf, C_MTU, 0, (struct sockaddr*) &m_last_recv_ip, &addrlen);
  // check if the recvfrom size is ok or not
  if(rcv_size < 0) {
    std::cout << "ERROR: RECVFROM" << std::endl;

    // here we close m_sock_fd
    if(m_sock_fd >= 0) {
      close(m_sock_fd);
      m_sock_fd = -1;
    } // if error close the socket and exit
    return -3;
  }
  return rcv_size;
}


int
UdpWrapper::sendData(const char* buf, size_t size_to_tx) 
{
  if(m_sock_fd<0) {
    return -1;
  }

  socklen_t addrlen = sizeof(m_last_recv_ip);
  // call the sendto API
  int sent_size = ::sendto(m_sock_fd, buf, size_to_tx, 0, (struct sockaddr*) &m_last_recv_ip, addrlen); 
  // check if the sendto size is ok or not
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SENDTO" << std::endl;
    if(m_sock_fd >= 0) {
      close(m_sock_fd);
      m_sock_fd = -1;
    } // if error close the socket and exit
    return -4;
  }
  return sent_size;
}


void 
UdpWrapper::print(std::ostream& out) const
{
  out << "UDP socket on port " << m_port << std::endl;
  out << "UDP socket IP " << getLastIp();
}


std::string
UdpWrapper::getLastIp() const
{
    std::string ip = inet_ntoa(m_last_recv_ip.sin_addr);
    return ip;
}