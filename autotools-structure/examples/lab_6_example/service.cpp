/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <service.h>
#include <string.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>

const unsigned int Service::FILE_SIZE = 100;

Service::Service(int sk_fd)
:
sock_fd(sk_fd),
total_received_size(0)
{
  std::cout << "constructor, sock_fd = " << sock_fd << std::endl;
  // Exercise 5: launch a thread to execute run(), and save it 
  // in servent_daemon
}

Service::~Service()
{
  // Exercise 6: implement this method, which should close the socket,
  // if open, and correctly handle the thread, if possible
}


void Service::run() 
{

  const size_t MAX_BUF_SIZE = 100;
  char buffer[MAX_BUF_SIZE] = {0};

  std::cout << "Service::run" << std::endl;
  while(sock_fd > -1 && total_received_size < Service::FILE_SIZE) {
    
    // Exercise 7
    // Implement the code to read data from the socket sock_fd in the buffer buffer.
    // The number of bytes to read is the minimum between the MAX_BUF_SIZE and the
    // remaining read size (i.e., Service::FILE_SIZE - total_received_size)
    // Check if the read was correct
    // Update the total received size

    std::string message = getReport();

    // Exercise 8
    // Implement the code to send the message string through sock_fd
    // Check if the send was correct

    memset(buffer,0,MAX_BUF_SIZE);
  }

  if(sock_fd > -1) {
    std::cout << "Service finished in socket " << sock_fd << std::endl;
    close(sock_fd);
    sock_fd = -1;
    return;
  }
}

// Exercise 1: declare (in the .h file) and implement the method getReport(), 
// which returns a string as follows:
// "Number of bytes received = " + the number of bytes successfully received + ", over a total of " + the FILE_SIZE variable + " bytes \n";

// Exercise 1: declare (in the .h file) and implement file the method getSockFd(),
// which returns the socket file descriptor