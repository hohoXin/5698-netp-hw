/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Nithyakumar
*/

// Exercise 0: add the relevant includes
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>


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

  const int listen_port = argc < 2 ? 55557 : atoi(argv[1]);
  const int udp_port = argc < 3 ? 55556 : atoi(argv[2]);

  const char* udp_ip = "127.0.0.1";  //Local IP address
  
  // // check the argv input
  // std::cout << listen_port << "; " << udp_port << "; " << udp_ip;

  // Open UDP client
  // Exercise 2: open a SOCK_DGRAM (UDP) socket and save the file descriptor
  // in an int variable called sockfd_udp
  // Check if the operation is successful, if not, print an error, close the socket and return

  int sockfd_udp = socket( AF_INET, SOCK_DGRAM, 0);
  if(sockfd_udp<0)
  {
    close(sockfd_udp);
    std::cout << "ERROR MSG: udp client failed to open" << std::endl;
    return -1;
  }
  
  struct sockaddr_in servaddr_udp = {0};     
  // Fill UDP server information 
  servaddr_udp.sin_family = AF_INET; 
  servaddr_udp.sin_port = htons(udp_port);
  
  // Exercise 3: use inet_pton to convert udp_ip into the sin_addr field of servaddr_udp
  // Check if the operation is successful, if not, print an error, close the socket and return
  int udp_ip_status = inet_pton(AF_INET, udp_ip, &(servaddr_udp.sin_addr));

  if(udp_ip_status < 0)
  {
    close(sockfd_udp);
    std::cout << "ERROR MSG: failed to convert udp client ip" << std::endl;
    return -2;
  }
  else if(udp_ip_status == 0)
  {
    close(sockfd_udp);
    std::cout << "ERROR MSG: udp client ip is invalid" << std::endl;
    return -3;
  }


  // Open a SOCK_STREAM (TCP) socket called scklist
  // Exercise 4: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable called scklist
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
  int scklist = socket( AF_INET, SOCK_STREAM, 0);
  if(scklist<0)
  {
    close(sockfd_udp);
    close(scklist);
    std::cout << "ERROR MSG: tcp server/client failed to open" << std::endl;
    return -4;
  }

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
  struct sockaddr_in my_addr = {0};
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(listen_port);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Exercise 6: bind the socket to my_addr using the bind API
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
  if(bind( scklist, (struct sockaddr*) &my_addr, sizeof(my_addr))<0)
  {
    close(sockfd_udp);
    close(scklist);
    std::cout << "ERROR MSG: tcp server/client failed to bind" << std::endl;
    return -5;
  }

  // Exercise 7: set scklist in a listening state, using the listen API (with at most 1 client)
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
  if(listen( scklist, 1)<0)
  {
    close(sockfd_udp);
    close(scklist);
    std::cout << "ERROR MSG: tcp server/client failed to set listen" << std::endl;
    return -6;
  }

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
  int sockfd = accept( scklist, (struct sockaddr*) &clientaddr_tcp, &addr_l);
  if(sockfd<0)
  {
    close(sockfd_udp);
    close(scklist);
    close(sockfd);
    std::cout << "ERROR MSG: tcp client failed to accept connection" << std::endl;
    return -7;
  }

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(clientaddr_tcp.sin_addr) << std::endl;
  std::cout << "------------------------------------------------------" << std::endl;

  // Prepare the receive buffer, with at most 512 bytes
  const size_t max_size = 512;
  char buf[max_size] = {0};

  // Create a while(true) loop
  while(true) {
    // Exercise 9: set the buf content to 0
    memset(buf, 0, max_size);

    // Exercise 10: receive with recv on sockfd, and save the received amount of bytes in rcv_size
    // Check if the recv is successful, if not, print an error, close the socket(s) and return
    // If the recv is successful but rcv_size is 0, this means that the socket was closed 
    // by the other endpoint of the TCP connection. You need to handle this case as well, 
    // close the sockets and return 0
    // The two cases must be handled separately, e.g., 
    // if (error condition) {...} else if (close condition) {...}

    int rcv_size = recv( sockfd, buf, max_size, 0);
    if(rcv_size<0)
    {
      close(sockfd_udp);
      close(scklist);
      close(sockfd);
      std::cout << "ERROR MSG: tcp client failed to recieve buf" << std::endl;
      return -8;
    }
    else if(rcv_size == 0)
    {
      close(sockfd_udp);
      close(scklist);
      close(sockfd);
      std::cout << "WARRNING MSG: tcp client was closed" << std::endl;
      return 0;
    }

    // Exercise 11: print buf and the received size
    std::cout << "Received: " << buf;
    std::cout << "MSG Size: " << rcv_size << std::endl;    

    // Exercise 12: send buf on sockfd_udp using sendto, to the address in servaddr_udp
    // Check if the send is successful, if not, print an error, close the socket(s) and return
    int send_size = sendto( sockfd_udp, buf, rcv_size, 0, (struct sockaddr*) &servaddr_udp, sizeof(servaddr_udp));
    if(send_size<0)
    {
      close(sockfd_udp);
      close(scklist);
      close(sockfd);
      std::cout << "ERROR MSG: failed to send buf to udp client" << std::endl;
      return -9;
    }

    std::cout << "Message sent to udp server" << std::endl; 
    std::cout << "------------------------------------------------------" << std::endl;
  }

  // Exercise 13: close the sockets
  close(sockfd_udp);
  close(scklist);
  close(sockfd);
  return 0;
}
