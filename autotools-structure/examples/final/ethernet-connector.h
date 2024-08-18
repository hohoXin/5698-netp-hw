/* 
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#ifndef H_ETHERNET_C_FS
#define H_ETHERNET_C_FS

#include <string>
#include <memory>
#include <array>
#include <arpa/inet.h>

constexpr size_t MTU = 512; /** Maximum transmission unit*/

/**
 * class EthConn containing the API of an Ethernet connector
 */
class EthConn
{
public:
  /** String with the LOCAL_HOST IPv4 address. */
  static const std::string LOCAL_HOST; 
  
  /**
   * Class constructor.
   * @param ip_addr string containing the human readable IP address in IPv4
   * @param port_num integer with the port number
   */
  EthConn(const std::string& ip_addr, int port_num);

  /**
   * Class constructor.
   * @param port_num integer with the port number
   */
  EthConn(int port_num);

  /**
   * Class destructor.
   */
  virtual ~EthConn() {}

  /**
   * Receive data from a remote host.
   * @param buf pointer to the buffer where the received data is stored
   * @param srcaddr a reference to a struct to store the address
   * @param addrlen the size of the struct for the address
   * @return number of bytes received (-1 if error occurred)
   */
  virtual int receiveFrom(std::shared_ptr<std::array<char,MTU>> buf,
    sockaddr_in& srcaddr, socklen_t addrlen) = 0;

  /**
   * Send data to remote host.
   * @param buf pointer to the buffer where the data to be sent is stored
   * @param size_to_tx size to transmit
   * @param srcaddr a reference to a struct with the receiver address
   * @param addrlen the size of the struct for the address
   * @return number of bytes sent (-1 if error occurred)
   */
  virtual int transmitTo(std::shared_ptr<std::array<char,MTU>> buf, 
    size_t size_to_tx, sockaddr_in& srcaddr, socklen_t addrlen) = 0;

  /**
   * Get the IP address of the last remote host connected.
   * @return the ip address
   */
  inline std::string getIp() const {
    return ip;
  }

  /**
   * Get the socket port number.
   * @return the port number
   */
  inline int getPort() const {
    return port;
  }

  /**
   * Print the connector to the ostream
   * @param out a ostream
   */
  virtual void print(std::ostream& out) const;

protected:
  /** string containing the human readable IP address */
  std::string ip; 
  /** integer with the port number*/
  int port;

};

/**
 * Overloaded operator<< for a EthConn
 * @param out a std::ostream object
 * @param conn reference to the connector to be printed
 * @return the manipulated ostream object
 */
std::ostream& operator<<(std::ostream& out, const EthConn& conn);

#endif /* H_ETHERNET_C_FS */
