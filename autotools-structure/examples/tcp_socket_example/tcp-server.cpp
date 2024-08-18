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
#include <cmath>

/**
 * Method to invert the elements of the buffer
 * @param buf the buffer
 * @param size the number of elements in the buffer
 */
void invertBuffer(char* buf, size_t size) 
{
  // exercise 11 (optional - do it at the end)
  // if the buf contains "abcd\0", it should contain "dcba\0" after running this function
  // suggestions: 
  // - use a for loop that iterates up to half of the size of the string (not considering the last termination char) 
  // - use a temporary char variable
  // - debug by printing your results at each cycle iteration
  // - pay attention to the index
  //   Do not place buffer[size - 1] as first, because this is a 
  //   zero-terminated string

  // std::cout << "buf[size-1]: " << buf[size-1] << std::endl; // buf[size-1] is '\0'
  // std::cout << "buf[size-2]: " << buf[size-2] << std::endl; // buf[size-1] is last char

  char tmp;
  for(size_t i = 0; 2 * i < size; i++)
  {
    tmp = buf[i];
    buf[i] = buf[size-2-i];
    buf[size-2-i]=tmp;
    // std::cout << "debugging #" << i+1 << "'s buf is " << buf << std::endl;
  }
}

int main(int argc, char** argv) {

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument

  // exercise 1: declare a variable listen_port of type const int, which is
  // 55555 if no argument is provided, or the argument otherwise
  // as for the UDP lab, skip this and declare const int listen_port {55555}; if you are not sure of how to do it
  const int listen_port = argc == 1 ? 55555 : atoi(argv[1]);

  // exercise 2: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable scklist
  // check if the operation is successful, if not, print an error, close the socket and return
  int scklist = socket(AF_INET, SOCK_STREAM, 0);
  if(scklist<0){
    /*socket file descriptor ERROR*/
    close(scklist);
    std::cout << "socket file descriptor < 0" << std::endl;
    return -1; 
  }

  // exercise 3: set socket options to release the socket address immediately after 
  // the socket is closed, so that it can be immediately reused (see SO_REUSEADDR and setsockopt from Friday's class)
  int option(1);
  setsockopt(scklist, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option));

  // exercise 4
  // declare and set to 0 a struct called my_addr and of type struct sockaddr_in 
  // then set the field sin_family of my_addr to AF_INET, the sin_port to listen_port
  // and the sin_addr.s_addr to INADDR_ANY (remember the conversions from network to host)
  struct sockaddr_in my_addr = {0};
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(listen_port);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // exercise 5
  // bind the socket to my_addr using the bind API
  // check if the bind is successful, if not, print an error, close the socket and return
  if(bind(scklist, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0){
    /*binding ERROR*/
    close(scklist);
    std::cout << "bind socket address failed" << std::endl;
    return -2;
  }

  // exercise 6: set scklist in a listening state, using the listen API (with at most 1 client)
  // check if the listen is successful, if not, print an error, close the socket and return
  if(listen(scklist, 1) < 0){
    /*set listening ERROR*/
    close(scklist);
    std::cout << "set listening state failed" << std::endl;
    return -3;
  }

  // exercise 7
  // declare a struct called client_addr and of type struct sockaddr_in
  // declare a variable addr_l of type socklen_t, and initialize it with 
  // the size of srcaddr (you can use sizeof)
  struct sockaddr_in client_addr;
  socklen_t addr_l = sizeof(client_addr);

  // exercise 8
  // performs these 3 operations using the accept API on scklist:
  // 1) accept the connection of a new client.
  // 2) create a new socket (called sockfd) used to perform the actual data transmission 
  //    between client ad server.
  // 3) save into client_addr the address of the client connected, so you 
  //    can know who is sending what.
  // check if the accept is successful, if not, print an error, close the socket(s) and return
  int sockfd = accept( scklist, (struct sockaddr*) &client_addr, &addr_l);
  if(sockfd < 0){
    /*accept ERROR*/
    close(sockfd);
    close(scklist);
    std::cout << "sockfd < 0" << std::endl;
    return -4;
  }

  // exercise 8
  // use inet_ntoa on the member sin_addr of client_addr to get the IP address in 
  // the dotted decimanl notation, in a const char* variable, and print to the terminal
  const char* client_address = inet_ntoa(client_addr.sin_addr);
  std::cout << " connection from " << client_address << std::endl;

  // exercise 9: receive from sockfd
  // create a buffer called buf, with max_size set to 256
  // receive with recv on sockfd, and save the received amount of bytes in rcv_size
  // check if the recv is successful, if not, print an error, close the socket(s) and return
  // print the received buffer and size
  const size_t max_size = 256;
  char buf[max_size] = {0};
  int rcv_size = recv( sockfd, buf, max_size, 0);
  if(rcv_size < 0){
    /*recv ERROR*/
    close(sockfd);
    close(scklist);
    std::cout << "receive from sockfd failed" << std::endl;
    return -5;
  }
  std::cout << "recieved buffer content: " << buf << "recieved buffer size = " << sizeof(buf) << std::endl;
  // no need for endl after the buf, for the content typed in client already has one

  /**
   * exercise 10
   * send back to the client whatever you received, 
   * - first try without modifying (i.e., as it is) 
   * - then (optional) by inverting the buffer order, implementing 
   *   the function void invertBuffer(char* buf,size_t size)
   */

  // call invert buffer (uncomment this line when you want to test the implementation)
  invertBuffer(buf,rcv_size);

  // call the send API on sockfd
  // check if the send is successful, if not, print an error, close the socket(s) and return
  int sent_size = send(sockfd, buf, rcv_size, 0);
  if(sent_size < 0){
    /*sent ERROR*/
    close(sockfd);
    close(scklist);
    std::cout << "send to the client failed" << std::endl;
    return -6;
  }

  // exercise 11: close the sockets
  close(sockfd);
  close(scklist);

  return 0;
}
