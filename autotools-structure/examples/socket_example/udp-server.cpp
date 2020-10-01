/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Author Michele Polese
*/

// exercise 0: add the includes

/**
 * Method to replace the buffer with capital letters
 * @param buf the buffer
 * @param size the number of elements in the buffer
 */
void toUpper(char* buf, size_t size) {
  // exercise 10 (optional, to it at the end)
  // suggestion: iterate the buffer accessing it as an array 
  // (with []) and apply the method `toupper` to each element of the array
}

int main(int argc, char** argv) {

  // exercise 1
  // READ from argv the command line argument vector, by checking the arguments 
  // counter (argc), i.e.,
  //   ./udp_server has argc = 1 and no command line arguments
  //   ./udp_server 55556 has argc = 2 and the socket port as argument
  // the port should be saved in a variable called recv_port and of type const int
  // if the command line does not specify a port, use 55555

  // exercise 2
  // open a SOCK_DGRAM (UDP) socket using the socket API
  // the socket file descriptor should be called sckfd, and of course of type int
  // check if the socket was opened correctly, if not, return -1 to exit this program
  
  // this code sets a useful option for the socket - we'll see more next week
  int option(1);
  setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, 
            (char*)&option, sizeof(option));

  // exercise 3
  // declare and set to 0 a struct called my_addr and of type struct sockaddr_in 
  // then set the field sin_family of my_addr to AF_INET, the sin_port to recv_port
  // and the sin_addr.s_addr to INADDR_ANY (remember the conversions from network to host)
  
  // exercise 4
  // bind the socket to my_addr using the bind API
  // check if the bind was successful, if not, close the socket, return -2

  // exercise 5
  // create a char buffer 256 elements, set to 0
  // the buffer variable is called buffer
  const size_t max_size = 256;
  char buffer[max_size] = {0}; 
  
  // exercise 6
  // declare a struct called srcaddr and of type struct sockaddr_in
  // declar a variable addrlen of type socklen_t, and initialize it with 
  // the size of srcaddr (you can use sizeof)

  // exercise 7
  // UDP is not connected: we just receive from someone (that may change time 
  // by time) and that's it. We can check who sent something storing its 
  // addess to srcaddr and send him back something through the same socket.
  // use the recvfrom API, passing sckfd, the buffer, the max read size, 0 as option,
  // a pointer to srcaddr casted to a struct sockaddr pointer, and a reference to addrlen
  // the return of recvfrom should be saved in a size_t variable called size.
  
  // exercise 8
  // use inet_ntoa on the member sin_addr of srcaddr to get the IP address in 
  // the dotted decimanl notation, in a const char* variable, and print to the terminal
  
  // exercise 9
  // print the buffer to the terminal

  // exercise 10 (optional)
  // implement the toUpper function (declared above) 
  toUpper(buffer, size);
  
  // exercise 11
  // use the same socket to send the buffer back to the client, using the sendto API
  // the amount of data to transmit is the same as that you received
  // as usual, check the actual amount of byte transmitted by storing the return of 
  // sendto in a variable, if it is smaller than 0, close the socket and exit by returning -3

  // exercise 12 
  // close the socket
}

