/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-server.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

TcpServer::TcpServer(int port_num)
:
EthConn(port_num),
l_sock_fd(-1),
sock_fd(-1),
connections_count(0)
{
  l_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (l_sock_fd < 0){ 
    std::cout << "ERROR: OPEN SOCKET" << std::endl;
    close(l_sock_fd);
    return;
  }
  if(!optionsAndBind()) {
  	std::cout << "ERROR: BIND" << std::endl;
    close(l_sock_fd);
    return;
  }
}

TcpServer::~TcpServer() {
  if(l_sock_fd >= 0) {
    close(l_sock_fd);
  }
  if(sock_fd >= 0) {
    close(sock_fd);
  }
}

bool TcpServer::optionsAndBind() 
{
  int option(1);
  if(setsockopt(l_sock_fd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option)) < 0) {
    std::cout << "ERROR: setsockopt FAILED, HOWEVER, THE PROGRAM WILL NOT STOP" 
              << std::endl;
  }
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert listener_port to network number format
  my_addr.sin_port = htons(port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the port
  if (bind(l_sock_fd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout << "ERROR: BIND SOCKET" << std::endl;
    close(l_sock_fd);
    return false;
  }

  // Accept at max 1 client at a time.
  if (listen(l_sock_fd, 1) < 0) { 
    std::cout << "ERROR: LISTEN SOCKET" << std::endl;
    close(l_sock_fd);
    return false;
  //ERR
  }
  return true;
}

bool TcpServer::acceptConn() 
{
  struct sockaddr_in client_addr;
  socklen_t addr_l = sizeof(client_addr);
  sock_fd = accept(l_sock_fd, (struct sockaddr*) &client_addr, &addr_l);
  if(sock_fd < 0) {
    std::cout << "ERROR: ACCEPT CONNECTION" << std::endl;
    return false;
  }
  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << std::endl; 
  ip = inet_ntoa(client_addr.sin_addr);
  connections_count++;
  return true;
}


int TcpServer::receive(MyBuffer& buf)  
{
  if(sock_fd < 0) {
    return -1;
  }
  int rcv_size = recv(sock_fd,buf.dataAccess(),buf.getMaxSize(),0);
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;
    close(sock_fd);
    sock_fd = -1;
  }
  else if(rcv_size == 0) {
    std::cout << "Other endpoint has closed the socket" << std::endl;
    close(sock_fd);
    sock_fd = -1;
  }
  buf.n_bytes = rcv_size;
  return rcv_size;
}


int TcpServer::transmit(MyBuffer& buf) 
{
  if(sock_fd < 0) {
    return -1;
  }
  int sent_size = send(sock_fd,buf.dataAccess(),buf.n_bytes,0); // send the data through sock_fd
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SEND" << std::endl;
    close(sock_fd); // if error close the socket and exit
    sock_fd = -1;
  }
  return sent_size;
}

void TcpServer::print(std::ostream& out) const
{
  out << "TcpServer(localhost:" << std::to_string(port) 
      << "), last host connected = " << ip 
      << ", number of  connections so far = " 
      << std::to_string(connections_count);
}