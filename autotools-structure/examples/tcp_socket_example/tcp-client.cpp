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
  // if(argc==1){
  //   const char* dest_ip = "127.0.0.1";
  //   const int dest_port = 55555;
  // }
  // else if(argc==2){
  //   const int dest_port = 55555;
  //   const char* dest_ip = argv[1];
  // }
  // else{
  //   const char* dest_ip = argv[1];
  //   const int dest_port = atoi(argv[2]);
  // }

  const char* dest_ip = argc == 1 ? "127.0.0.1" : argv[1];
  const int dest_port = argc > 2 ? atoi(argv[2]) : 55555;

  // exercise 2: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable sckfd
  // check if the operation is successful, if not, print an error, close the socket and return
  int sckfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sckfd<0){
    /*open sckfd ERROR*/
    close(sckfd);
    std::cout << "sckfd < 0, client socket open failed" << std::endl;
    return -1;
  }

  // exercise 3: set socket options to release the socket address immediately after 
  // the socket is closed, so that it can be immediately reused (see SO_REUSEADDR and setsockopt)
  int option(1);
  setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option));

  // exercise 4
  // declare and set to 0 a struct called dest_addr and of type struct sockaddr_in 
  // then set the field sin_family of dest_addr to AF_INET, the sin_port to dest_port
  // finally, use inet_pton to set dest_addr.sin_addr to dest_ip
  // tip: inet_pton(AF_INET, dest_ip, and a pointer to dest_addr.sin_addr)
  // check if the conversion is successful (according to the return of inet_pton),
  // if not, print an error, close the socket and return
  struct sockaddr_in dest_addr = {0};
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(dest_port);
  if(inet_pton(AF_INET, dest_ip, &dest_addr.sin_addr)<0){
    /*conversion inet_pton ERROR*/
    close(sckfd);
    std::cout << "conversion dest_ip to AF_ADDRESS failed" << std::endl;
    return -2;
  }

  // exercise 5 connect the socket to the server ip:port specified into dest_addr
  // using the connect API on sckfd
  // check if the operation is successful, if not, print an error, close the socket and return
  if(connect(sckfd, (struct sockaddr*) &dest_addr, sizeof(dest_addr))<0){
    /*connect ERROR*/
    close(sckfd);
    std::cout << "connect socket to ip failed" << std::endl;
    return -3;
  }

  // transmit this data
  const size_t max_size = 512;
  char buf[max_size] = "Payload"; // store the data in a buffer
  std::cout << "Transmit " << buf << std::endl;
  size_t data_size = 8; // transmit the termination character too!

  // exercise 6 use the send API on sckfd to transmit the buf
  // check if the operation is successful, if not, print an error, close the socket and return
  int sent_size = send(sckfd, buf, data_size, 0);
  if(sent_size < 0){
    /*sent message ERROR*/
    close(sckfd);
    std::cout << "transmit the buf with send failed" << std::endl;
    return -4;
  }

  // set buffer to zero for next read
  memset(buf, 0, max_size);

  // exercise 7 wait to receive data with the recv API on sckfd
  // check if the operation is successful, if not, print an error, close the socket and return
  int rcv_size = recv(sckfd, buf, max_size, 0);
  if(rcv_size < 0){
    /*receive data ERROR*/
    close(sckfd);
    std::cout << "recieved the data with recv failed" << std::endl;
    return -5;
  }

  std::cout << buf << std::endl;
  
  // exercise 8 close the socket
  close(sckfd);
}

