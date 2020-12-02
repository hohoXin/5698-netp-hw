/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-server-connection.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include "service.h"

TcpServerConnection::TcpServerConnection(int port_num)
:
EthConn(port_num),
l_sock_fd(-1),
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

// Exercise 4 implement the destructor ~TcpServerConnection
// which closes the socket if still valid

bool TcpServerConnection::optionsAndBind() 
{
  int option(1);
  setsockopt(l_sock_fd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
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

  // Accept at max 1 client at a time: by changing 1 to 5 in the next line 
  // you accept at most the connection of 5 clients in parallel.
  if (listen(l_sock_fd, 1) < 0) { 
    std::cout << "ERROR: LISTEN SOCKET" << std::endl;
    close(l_sock_fd);
    return false;
  //ERR
  }
  return true;
}

bool TcpServerConnection::acceptConn() 
{
  // Exercise 3: implement the code to accept a client and print the IP of 
  // the client to the terminal
  // The IP address should be saved in the ip member variable (see EthConn)
  // Use std::make_shared to create a shared_ptr to a Service object,
  // passing the sock_fd to the constructor, and add the shared_ptr to the
  // services vector
  // Increase the connections_count by 1
  return true;
}


void TcpServerConnection::print(std::ostream& out) const
{
  out << "TcpServerConnection(localhost:" << std::to_string(port) 
      << "), last host connected = " << ip 
      << ", number of  connections so far = " 
      << std::to_string(connections_count);
}