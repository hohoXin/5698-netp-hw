/* 
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <network-adder.h>
#include <iostream>

int main(int argc, char** argv) 
{

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument
  const int port = argc ==1 ? 55555 : atoi(argv[1]);
  std::shared_ptr<NetworkAdder> adder = std::make_shared<NetworkAdder>(port);
  if(adder->run(4) == 0) {
    std::cout << "adder last sum = " << adder->getSum() << std::endl;
  	return 0;
  } else {
  	return -1;
  }
}