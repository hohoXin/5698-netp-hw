/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese 
*/

#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << "Received " << argc << " arguments from the command line." << std::endl; 
  
  for (int i = 0; i < argc; ++i)
  {
    std::cout << "Argument " << i << " is " << argv[i] << std::endl;
  }
  
  return 0;
}
