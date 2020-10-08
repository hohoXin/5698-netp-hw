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
}

int main(int argc, char** argv) {

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument

  // exercise 1: declare a variable listen_port of type const int, which is
  // 55555 if no argument is provided, or the argument otherwise
  
  // exercise 2: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable scklist
  // check if the operation is successful, if not, print an error, close the socket and return

  // exercise 3: set socket options to release the socket address immediately after 
  // the socket is closed, so that it can be immediately reused (see SO_REUSEADDR and setsockopt)
  
  // exercise 4
  // declare and set to 0 a struct called my_addr and of type struct sockaddr_in 
  // then set the field sin_family of my_addr to AF_INET, the sin_port to listen_port
  // and the sin_addr.s_addr to INADDR_ANY (remember the conversions from network to host)
  
  // exercise 5
  // bind the socket to my_addr using the bind API
  // check if the bind is successful, if not, print an error, close the socket and return
 
  // exercise 6: set scklist in a listening state, using the listen API (with at most 1 client)
  // check if the listen is successful, if not, print an error, close the socket and return

  // exercise 7
  // declare a struct called client_addr and of type struct sockaddr_in
  // declare a variable addr_l of type socklen_t, and initialize it with 
  // the size of srcaddr (you can use sizeof)

  // exercise 8
  // performs these 3 operations using the accept API on scklist:
  // 1) accept the connection of a new client.
  // 2) create a new socket (called sockfd) used to perform the actual data transmission 
  //    between client ad server.
  // 3) save into client_addr the address of the client connected, so you 
  //    can know who is sending what.
  // check if the accept is successful, if not, print an error, close the socket(s) and return

  // exercise 8
  // use inet_ntoa on the member sin_addr of client_addr to get the IP address in 
  // the dotted decimanl notation, in a const char* variable, and print to the terminal

  // exercise 9: receive from sockfd
  // create a buffer called buf, with max_size set to 256
  // receive with recv on sockfd, and save the received amount of bytes in rcv_size
  // check if the recv is successful, if not, print an error, close the socket(s) and return
  // print the received buffer and size
  
  /**
   * exercise 10
   * send back to the client whatever you received, 
   * - first try without modifying (i.e., as it is) 
   * - then (optional) by inverting the buffer order, implementing 
   *   the function void invertBuffer(char* buf,size_t size)
   */

  // call invert buffer (uncomment this line when you want to test the implementation)
  // invertBuffer(buf,rcv_size);

  // call the send API on sockfd
  // check if the send is successful, if not, print an error, close the socket(s) and return

  // exercise 11: close the sockets

}
