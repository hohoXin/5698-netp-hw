/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Nithyakumar
*/

// Exercise 0: add the relevant includes

int main(int argc, char** argv) {

  // READ from argv, the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./proxy has argc = 1 and no command line arguments
  //   ./proxy 55557 has argc = 2 and the tcp_server port as argument
  //   ./proxy 55557 55556 has argc = 3 and the tcp_server port and udp_client port as argument
  
  // Exercise 1a: declare a variable listen_port of type const int, which is
  // 55557 if no argument is provided, or the argument otherwise
  // Exercise 1b: declare a variable udp_port of type const int, which is
  // 55556 if no argument is provided, or the argument otherwise

  const char* udp_ip = "127.0.0.1";  //Local IP address
  
  // Open UDP client
  // Exercise 2: open a SOCK_DGRAM (UDP) socket and save the file descriptor
  // in an int variable called sockfd_udp
  // Check if the operation is successful, if not, print an error, close the socket and return
  
  struct sockaddr_in servaddr_udp = {0};     
  // Fill UDP server information 
  servaddr_udp.sin_family = AF_INET; 
  servaddr_udp.sin_port = htons(udp_port); 
  // Exercise 3: use inet_pton to convert udp_ip into the sin_addr field of servaddr_udp
  // Check if the operation is successful, if not, print an error, close the socket and return

  // Open a SOCK_STREAM (TCP) socket called scklist
  // Exercise 4: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable called scklist
  // Check if the operation is successful, if not, print an error, close the socket(s) and return

  // Set socket options to release the socket address immediately after, on both sockets 
  // the socket is closed
  int option(1);
  setsockopt(scklist, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  setsockopt(sockfd_udp, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));

  // At this point your code MUST compile correctly

  // Exercise 5: declare and set to 0 a struct called my_addr and of type struct sockaddr_in 
  // then set the field sin_family of my_addr to AF_INET, the sin_port to listen_port
  // and the sin_addr.s_addr to INADDR_ANY

  // Exercise 6: bind the socket to my_addr using the bind API
  // Check if the operation is successful, if not, print an error, close the socket(s) and return

  // Exercise 7: set scklist in a listening state, using the listen API (with at most 1 client)
  // Check if the operation is successful, if not, print an error, close the socket(s) and return

  // Create a sockaddr_in for clientaddr_tcp
  struct sockaddr_in clientaddr_tcp;
  socklen_t addr_l = sizeof(clientaddr_tcp);

  // Exercise 8: perform these 3 operations using the accept API on scklist:
  // 1) accept the connection of a new client.
  // 2) create a new socket (called sockfd) used to perform the actual data transmission 
  //    between TCP client and TCP server.
  // 3) save into clientaddr_tcp the address of the client connected, so you 
  //    can know who is sending what.
  // Check if the operation is successful, if not, print an error, close the socket(s) and return

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(clientaddr_tcp.sin_addr) << std::endl; 

  // Prepare the receive buffer, with at most 512 bytes
  const size_t max_size = 512;
  char buf[max_size] = {0};

  // Create a while(true) loop
  while(true) {
    // Exercise 9: set the buf content to 0

    // Exercise 10: receive with recv on sockfd, and save the received amount of bytes in rcv_size
    // Check if the recv is successful, if not, print an error, close the socket(s) and return
    // If the recv is successful but rcv_size is 0, this means that the socket was closed 
    // by the other endpoint of the TCP connection. You need to handle this case as well, 
    // close the sockets and return 0
    // The two cases must be handled separately, e.g., 
    // if (error condition) {...} else if (close condition) {...}

    // Exercise 11: print buf and the received size

    // Exercise 12: send buf on sockfd_udp using sendto, to the address in servaddr_udp
    // Check if the send is successful, if not, print an error, close the socket(s) and return

    std::cout << "Message sent to udp server" << std::endl; 
  }

  // Exercise 13: close the sockets
}
