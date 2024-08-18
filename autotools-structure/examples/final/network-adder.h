/* 
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#ifndef H_NETWORK_ADDER
#define H_NETWORK_ADDER

#include <ethernet-connector.h>

/**
 * class NetworkAdder
 */
class NetworkAdder
{
public:  
  /**
   * Class constructor.
   * @param port_num integer with the port number on which the server will run
   */
  NetworkAdder(int port_num);

  /**
   * Class destructor.
   */
  ~NetworkAdder() {}

  /**
   * Run the adder, until the string "exit" is received
   * @param max_num_to_add the maximum number of int to add
   * @return 0 if terminated gracefully, a negative number otherwise
   */
  int run(int max_num_to_add);

  /**
   * Get the current sum
   * @return the current sum
   */
  // Exercise 2: declare and implement the getSum method
  long int getSum();

  /**
   * Get the port number
   * @return the port of the server
   */
  // Exercise 2: declare and implement the getPort method
  int getPort();

private:
  /**
   * Convert the buffer to a meaningful number and sum
   * @param buf the buffer with the data received from the socket
   */
  void sum(std::shared_ptr<std::array<char,MTU>> buf);

  /**
   * Convert m_sum to a buffer to be transmitted
   * @param buf the buffer to be transmitted
   * @return the number of bytes to be transmitted
   */
  int prepareTxBuffer(std::shared_ptr<std::array<char,MTU>> buf) const;

  long int m_sum; //<! the accumulator used for this class

  int m_port_num; //<! the port where the server runs

  std::shared_ptr<EthConn> m_server; //<! shared_ptr to a server
};

#endif /* H_NETWORK_ADDER */
