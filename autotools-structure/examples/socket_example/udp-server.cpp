/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Author Michele Polese
*/

// exercise 0: add the includes
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

/**
 * Method to replace the buffer with capital letters
 * @param buf the buffer
 * @param size the number of elements in the buffer
 */
void toUpper(char* buf /*, size_t size*/) {
  // exercise 10 (optional, to it at the end)
  // suggestion: iterate the buffer accessing it as an array 
  // (with []) and apply the method `toupper` to each element of the array
  for(; *buf != '\0'; ++buf)
  {
    *buf = toupper(*buf);
  }
}

int main(int argc, char** argv) {

  // exercise 1
  // READ from argv the command line argument vector, by checking the arguments 
  // counter (argc), i.e.,
  //   ./udp_server has argc = 1 and no command line arguments
  //   ./udp_server 55556 has argc = 2 and the socket port as argument
  // the port should be saved in a variable called recv_port and of type const int
  // if the command line does not specify a port, use 55555
  int user_input1;
  if(argc > 1)
    user_input1 = atoi(argv[1]);
  else
    user_input1 = 55555;
  const int recv_port = user_input1;
  std::cout << "The recv_port is " << recv_port << ". Yeah !!" << std::endl;
  // note: if you are not sure of how to do exercise 1 and want to start with sockets,
  // you can start by declaring const int recv_port {55555}; and continue with exercise 2-9
  // and 11-12 then you can come back and solve 1 and 10

  // exercise 2
  // open a SOCK_DGRAM (UDP) socket using the socket API
  // the socket file descriptor should be called sckfd, and of course of type int
  // check if the socket was opened correctly, if not, return -1 to exit this program
  int sckfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sckfd < 0)
  {/*ERR*/
    std::cout << "The socket file descriptor is " << sckfd << " < 0 !!" << std::endl;
    return -1;
  }
  else
    std::cout << "The socket file descriptor is " << sckfd << std::endl <<  "Running properly!" << std::endl;
  
  
  // this code sets a useful option for the socket - we'll see more next week
  int option(1);
  setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, 
            (char*)&option, sizeof(option));

  // exercise 3
  // declare and set to 0 a struct called my_addr and of type struct sockaddr_in 
  // then set the field sin_family of my_addr to AF_INET, the sin_port to recv_port
  // and the sin_addr.s_addr to INADDR_ANY (remember the conversions from network to host)
  struct sockaddr_in my_addr = {0};
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(recv_port);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // exercise 4
  // bind the socket to my_addr using the bind API
  // check if the bind was successful, if not, close the socket, return -2
  if(bind(sckfd, (struct sockaddr*) &my_addr, sizeof(my_addr)) < 0)
  {
    /* ERROR: bind failed: exit */
    close(sckfd);
    std::cout << "Bind ERROR!!! " <<  std::endl;
    return -2;
  }

  // exercise 5
  // create a char buffer 256 elements, set to 0
  // the buffer variable is called buffer
  const size_t max_size = 256;
  char buffer[max_size] = {0};
  // memset(buffer, 0, max_size);

  
  // exercise 6
  // declare a struct called srcaddr and of type struct sockaddr_in
  // declar a variable addrlen of type socklen_t, and initialize it with 
  // the size of srcaddr (you can use sizeof)
  struct sockaddr_in srcaddr = {0};
  socklen_t addrlen = sizeof(srcaddr);

  // exercise 7
  // UDP is not connected: we just receive from someone (that may change time 
  // by time) and that's it. We can check who sent something storing its 
  // addess to srcaddr and send him back something through the same socket.
  // use the recvfrom API, passing sckfd, the buffer, the max read size, 0 as option,
  // a pointer to srcaddr casted to a struct sockaddr pointer, and a reference to addrlen
  // the return of recvfrom should be saved in a size_t variable called size.
  // int size = recvfrom(sckfd, buffer, max_size, 0, (struct sockaddr *) &srcaddr, &addrlen);

  // exercise 8
  // use inet_ntoa on the member sin_addr of srcaddr to get the IP address in 
  // the dotted decimanl notation, in a const char* variable, and print to the terminal

  
  // exercise 9
  // print the buffer to the terminal
  while (1)
  {
    int size = recvfrom(sckfd, buffer, max_size, 0, (struct sockaddr *) &srcaddr, &addrlen);
    if (size < 0)
    {
      break;
      /* ERROR: Recieve failed: exit */
      close(sckfd);
      std::cout << "Recieve ERROR!!! " <<  std::endl;
      return -3;
    }
    
    const char* src_ip = inet_ntoa(srcaddr.sin_addr);
    std::cout << "The current IP is: " << src_ip << std::endl; 
    std::cout << buffer << std::endl;     

  // exercise 10 (optional)
  // implement the toUpper function (declared above) 
    toUpper(buffer);
  
  // exercise 11
  // use the same socket to send the buffer back to the client, using the sendto API
  // the amount of data to transmit is the same as that you received
  // as usual, check the actual amount of byte transmitted by storing the return of 
  // sendto in a variable, if it is smaller than 0, close the socket and exit by returning -3
    if(sendto(sckfd, buffer, max_size, 0, (struct sockaddr*) &srcaddr, addrlen) < 0)
    {
      break;
      /* ERROR: Send failed: exit */
      close(sckfd);
      std::cout << "Send ERROR!!! " <<  std::endl;
      return -3;
    }
    memset(buffer, 0, max_size);
  }

  // exercise 12 
  // close the socket
  close(sckfd);

  return 0;
}

