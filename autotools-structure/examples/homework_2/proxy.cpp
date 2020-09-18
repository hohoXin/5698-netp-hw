/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Nithyakumar
*/

#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./proxy has argc = 1 and no command line arguments
  //   ./proxy 55556 has argc = 2 and the tcp_server port as argument
  //   ./proxy 55556 55557 has argc = 3 and the tcp_server port and udp_client port as argument
  
  const int listen_port = argc == 1 ? 55555 : atoi(argv[1]);
  const int udp_port = argc <= 2 ? 55556 : atoi(argv[2]);
  const char* udp_ip = "127.0.0.1";
  
  // Open UDP client
  // Creating socket file descriptor 
  int sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd_udp < 0) { 
      std::cout  << "UDP socket creation failed" << std::endl; 
      return -1; 
  } 
  
  struct sockaddr_in servaddr_udp = {0};     
  // Fill UDP server information 
  servaddr_udp.sin_family = AF_INET; 
  servaddr_udp.sin_port = htons(udp_port); 
  if (inet_pton(AF_INET, udp_ip, &servaddr_udp.sin_addr) <= 0) { 
    std::cout << "Conversion from char* to IP failed" << std::endl;
    close(sockfd_udp); // if conversion fail, close the socket and return error -2
    return -2;
  }

  // Open a SOCK_STREAM (TCP) socket called scklist
  int scklist = socket(AF_INET, SOCK_STREAM, 0);
  if (scklist < 0) { 
    std::cout  << "TCP socket creation failed" << std::endl; 
    close(scklist);
    close(sockfd_udp);
    return -3;
  }

  // Set socket options to release the socket address immediately after, on both sockets 
  // the socket is closed
  int option(1);
  setsockopt(scklist, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  setsockopt(sockfd_udp, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));

  // bind the TCP listen socket
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)
  // convert listener_port to network number format
  my_addr.sin_port = htons(listen_port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the port
  if (bind(scklist, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout  << "TCP socket bind failed" << std::endl; 
    close(scklist);
    close(sockfd_udp);
    return -4;
  }

  // Accept at max 1 client at a time: by changing 1 to 5 in the next line 
  // you accept at most the connection of 5 clients in parallel.
  if (listen(scklist, 1) < 0) { 
    std::cout  << "TCP socket listen failed" << std::endl; 
    close(scklist);
    close(sockfd_udp);
    return -5;
  }

  // Create a sockaddr_in for clientaddr_tcp
  struct sockaddr_in clientaddr_tcp;
  socklen_t addr_l = sizeof(clientaddr_tcp);

  // the next line does 3 operations:
  // 1) it accepts the connection of a new client.
  // 2) it creates a new socket used to perform the actual data transmission 
  //    between client ad server. If the socket creation fails, it returns -1.
  // 3) it Saves into clientaddr_tcp the address of the client connected, so you 
  //    can know who is sending what.
  int sockfd = accept(scklist, (struct sockaddr*) &clientaddr_tcp, &addr_l);
  if(sockfd < 0) {
    std::cout  << "TCP socket accept failed" << std::endl; 
    close(sockfd);
    close(scklist);
    close(sockfd_udp);
    return -6;
  }

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(clientaddr_tcp.sin_addr) << std::endl; 

  // Prepare the receive buffer, with at most 512 bytes
  const size_t max_size = 512;
  char buf[max_size] = {0};

  // Create a while(true) loop
  while(true) {
    // Set the buf memory to 0
    memset(buf, 0, sizeof(buf));

    // Receive from the TCP sockfd (not the listening socket)
    int rcv_size = recv(sockfd, buf, max_size, 0);

    // Check if the receive was correct
    if(rcv_size < 0) {
      std::cout  << "TCP socket receive failed" << std::endl; 
      close(sockfd);
      close(scklist);
      close(sockfd_udp);
      return -7;
    } else if (rcv_size == 0) {
      // this means that the socket has been closed
      std::cout  << "TCP socket closed" << std::endl; 
      close(sockfd);
      close(scklist);
      close(sockfd_udp);
      return 0;
    }

    // Print the buffer and the received size
    std::cout << "Received: " << buf << std::endl;
    std::cout << "Size: " << rcv_size << std::endl;

    // Send buf on sockfd_udp using sendto
    int sent_size = sendto(sockfd_udp, (const char *)buf, strlen(buf), 0, 
      (const struct sockaddr *) &servaddr_udp, sizeof(servaddr_udp)); 

    // Check if the send was correct
    if(sent_size <= 0) {
      std::cout  << "UDP socket send failed" << std::endl; 
      close(sockfd);
      close(scklist);
      close(sockfd_udp);
      return -8;
    }

    std::cout << "Message sent to udp server" << std::endl; 
  }

  // close the sockets
  close(sockfd);
  close(scklist);
  close(sockfd_udp);
}
