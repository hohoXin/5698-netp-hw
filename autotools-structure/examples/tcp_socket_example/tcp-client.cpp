/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese 
*/

// These are the includes you need 
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) 
{
  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //    ./tcp_client has argc = 1 and no command line arguments
  //    ./tcp_client 192.168.100.12 has argc = 2 and the IP address as argument
  //    ./tcp_client 192.168.100.12 55556 has argc = 3 and IP and socket port as 
  //      arguments

  // exercise 1: declare a variable dest_ip of type const char*, which is
  // "127.0.0.1" if no argument is provided, or the first argument otherwise
  // exercise 2: declare a variable dest_port of type const int, which is
  // 55555 if no argument is provided, or the second argument otherwise

  // exercise 2: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable sckfd
  // check if the operation is successful, if not, print an error, close the socket and return

  // exercise 3: set socket options to release the socket address immediately after 
  // the socket is closed, so that it can be immediately reused (see SO_REUSEADDR and setsockopt)

  // exercise 4
  // declare and set to 0 a struct called dest_addr and of type struct sockaddr_in 
  // then set the field sin_family of dest_addr to AF_INET, the sin_port to dest_port
  // finally, use inet_pton to set dest_addr.sin_addr to dest_ip
  // tip: inet_pton(AF_INET, dest_ip, and a pointer to dest_addr.sin_addr)
  // check if the conversion is successful (according to the return of inet_pton),
  // if not, print an error, close the socket and return

  // exercise 5 connect the socket to the server ip:port specified into dest_addr
  // using the connect API on sckfd
  // check if the operation is successful, if not, print an error, close the socket and return

  // transmit this data
  const size_t max_size = 512;
  char buf[max_size] = "Payload"; // store the data in a buffer
  std::cout << "Transmit " << buf << std::endl;
  size_t data_size = 8; // transmit the termination character too!

  // exercise 6 use the send API on sckfd to transmit the buf
  // check if the operation is successful, if not, print an error, close the socket and return

  // set buffer to zero for next read
  memset(buf, 0, max_size);

  // exercise 7 wait to receive data with the recv API on sckfd
  // check if the operation is successful, if not, print an error, close the socket and return

  std::cout << buf << std::endl;
  
  // exercise 8 close the socket
}

