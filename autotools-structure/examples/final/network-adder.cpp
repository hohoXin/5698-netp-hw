/* 
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <network-adder.h>
#include <udp-server.h>
#include <iostream>

NetworkAdder::NetworkAdder(int port_num)
{
  // Exercise 3: implement the constructor, which initializes
  // the member variables appropriately
  std::cout << "NetworkAdder constructor, using the server = " << *m_server << std::endl;
}

void NetworkAdder::sum(std::shared_ptr<std::array<char,MTU>> buf)
{
  // Exercise 6: implement this method, which has to do the following operations:
  // 1- convert the char buffer to an integer, using std::strtol (preferrable) or std::atoi
  // 2- sums the number to m_sum
  // 3- prints to the terminal the received number and the sum so far
}

int NetworkAdder::prepareTxBuffer(std::shared_ptr<std::array<char,MTU>> buf) const
{
  // convert the sum to a string, and then put the characters into the tx_buffer
  std::string sum_to_str = std::to_string(m_sum);
  unsigned int char_index = 0;
  for (; char_index < sum_to_str.size(); ++char_index)
  {
    (*buf)[char_index] = sum_to_str[char_index];
  }
  // an alternative is 
  // memcopy(buf->data(),sum_to_str.c_str(),sum_to_str.size());

  // terminate with a '\n' character to print each sum to a new line
  (*buf)[char_index] = '\n';

  return sum_to_str.size() + 1;
}

int NetworkAdder::run(int max_num_to_add)
{
  auto rx_buffer = std::make_shared<std::array<char,MTU>>();
  auto tx_buffer = std::make_shared<std::array<char,MTU>>();
  int num_added = 0;

  while(true)
  {
    // clear the rx and tx buffer
    rx_buffer->fill(0);
    tx_buffer->fill(0);

    // data structures to store the address and port of the sender
    struct sockaddr_in srcaddr; 
    socklen_t addrlen = sizeof(srcaddr);
    // receive a packet
    int size = m_server->receiveFrom(rx_buffer, srcaddr, addrlen);

    // check if the "exit" string was sent, this signal the NetworkAdder
    // to exit
    if(std::string(rx_buffer->data()).compare("exit\n") == 0)
    {
      return 0;
    }

    if(size < 0)
    {
      std::cout << "error: the receiveFrom call return " << size << std::endl;
      return size;
    }

    sum(rx_buffer);

    int number_of_bytes = prepareTxBuffer(tx_buffer);
    
    // send the correct number of bytes (given by the size of the tx array)
    int to_tx_size = sizeof(char) * number_of_bytes;

    // send the buffer
    int txed_size = m_server->transmitTo(tx_buffer, to_tx_size, srcaddr, addrlen);

    if(txed_size < 0)
    {
      std::cout << "error: the transmitTo call return " << txed_size << std::endl;
      return txed_size;
    }

    if(++num_added >= max_num_to_add)
    {
      std::cout << "num_added " << num_added 
        << " max_num_to_add " << max_num_to_add << std::endl; 
      num_added = 0;
      m_sum = 0;
    }
  }
}
