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
#include <cmath>


int main(int argc, char** argv) {

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./proxy has argc = 1 and no command line arguments
  //   ./proxy 55556 has argc = 2 and the tcp_server port as argument
  //   ./proxy 55556 55557 has argc = 3 and the tcp_server port and udp_client port as argument
  
  const int listen_port = argc == 1 ? 55555 : atoi(argv[1]);
  const int udp_port = argc <= 2 ? 55556 : atoi(argv[2]);
  
  //Opening UDP client
  struct sockaddr_in servaddr; 
  
  // Creating socket file descriptor 
  int sockfd_udp;
  if ( (sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
      perror("socket creation failed"); 
      return -6; 
  } 

  memset(&servaddr, 0, sizeof(servaddr)); 
    
  // Filling server information 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port = htons(udp_port); 
  //servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) { 
    std::cout << "ERROR CONVERTING IP TO INTERNET ADDR" << std::endl;
    close(sockfd_udp); // if conversion fail, close the socket and return error -2
    return -2;
  }
  // open a SOCK_STREAM (TCP) socket
  int scklist = socket(AF_INET, SOCK_STREAM, 0);
  if (scklist < 0){ 
    std::cout << "ERROR: OPEN SOCKET " << scklist << std::endl;
    close(scklist);
    return -1;
  }
  // set socket options to release the socket address immediately after 
  // the socket is closed
  int option(1);
  setsockopt(scklist, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert listener_port to network number format
  my_addr.sin_port = htons(listen_port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the port
  if (bind(scklist,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout << "ERROR: BIND SOCKET" << std::endl;
    close(scklist);
    return -2;
  }

  // Accept at max 1 client at a time: by changing 1 to 5 in the next line 
  // you accept at most the connection of 5 clients in parallel.
  if (listen(scklist, 1) < 0) { 
    std::cout << "ERROR: LISTEN SOCKET" << std::endl;
    close(scklist);
    return -3;
  }

  struct sockaddr_in client_addr;
  socklen_t addr_l = sizeof(client_addr);

  // the next line does 3 operations:
  // 1) it accepts the connection of a new client.
  // 2) it creates a new socket used to perform the actual data transmission 
  //    between client ad server. If the socket creation fails, it returns -1.
  // 3) it Saves into client_addr the address of the client connected, so you 
  //    can know who is sending what.
  int sockfd = accept(scklist, (struct sockaddr*) &client_addr, &addr_l);
  if(sockfd < 0) {
    std::cout << "ERROR: ACCEPT CONNECTION" << std::endl;
    close(sockfd);
    close(scklist);
    return -4;
  }

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << std::endl; 

  // receive from sockfd
  const size_t max_size = 256;
  char buf[max_size] = {0};

  while(1){
    memset(buf, 0, sizeof(buf)); 
    int rcv_size = recv(sockfd, buf, max_size, 0);
    if(rcv_size < 0) {
      std::cout << "ERROR: RECV" << std::endl;
      close(sockfd);
      close(scklist);
      return -5;
    }
    std::cout << "Received: " << buf << std::endl;
    std::cout << "Size: " << rcv_size << std::endl;
    /////////---------UDP Client sending data----------//////////


    sendto(sockfd_udp, (const char *)buf, strlen(buf), MSG_CONFIRM, 
      (const struct sockaddr *) &servaddr, sizeof(servaddr)); 

    printf("message sent to udp server.\n"); 
  }
  // close the sockets
  close(sockfd);
    close(scklist);

  close(sockfd_udp);
}
