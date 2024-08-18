/* 
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#ifndef H_UDP_SERVER
#define H_UDP_SERVER

#include "ethernet-connector.h"

/**
 * Class UdpServer
 */
class UdpServer : public EthConn
{
public:
  /**
   * Class constructor.
   * @param port_num integer with the port number
   */
  UdpServer(int port_num);

  /**
   * Class destructor.
   */
  virtual ~UdpServer();

  /**
   * Receive data from remote host.
   * @param buf pointer to the buffer where the received data is stored
   * @param srcaddr a reference to a struct to store the address
   * @param addrlen the size of the struct for the address
   * @return number of bytes received (-1 if error occurred)
   */
  int receiveFrom(std::shared_ptr<std::array<char,MTU>> buf,
    sockaddr_in& srcaddr, socklen_t addrlen) override;

  /**
   * Send data to remote host.
   * @param buf pointer to the buffer where the data to be sent is stored
   * @param size_to_tx size to transmit
   * @param srcaddr a reference to a struct with the receiver address
   * @param addrlen the size of the struct for the address
   * @return number of bytes sent (-1 if error occurred)
   */
  int transmitTo(std::shared_ptr<std::array<char,MTU>> buf, 
    size_t size_to_tx, sockaddr_in& srcaddr, socklen_t addrlen) override;

  /**
   * Print the tcp server to the ostream
   * @param out a ostream
   */
  void print(std::ostream& out) const override;

private:
  int sock_fd; /**< socket file descriptor */

  /**
   * Set the socket options and bind.
   * @return false as soon as any of the operations it performs fails
   */
  bool optionsAndBind();

};

#endif /* H_UDP_SERVER */
