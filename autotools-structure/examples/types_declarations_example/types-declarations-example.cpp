/*
 * [2019] Signet Lab - University of Padova
 *
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <basic-utilities.h>
#include <string.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <iterator>
#include <iostream>

int main(int argc, char* argv[])
{
  // boolean
  bool boolean_variable {true}; // declare and initialze boolean_variable to true
  bool another_boolean_variable {!boolean_variable}; // decl and init another_boolean_variable

  // std::cout is the C++ standard library output stream to the terminal
  std::cout << "First variable = " 
    << boolean_variable // it is possible to concatenate output using <<
    << ", second variable = "
    << another_boolean_variable
    << std::endl;


  // characters
  char char_variable {'c'};
  unsigned char uchar_variable {255};
  signed char schar_variable {-127};
  wchar_t widechar_variable {'c'};

  // narrowing: these instructions would not compile!
  // signed char out_of_range {255};
  // unsigned char out_of_range_2 {-1};
  signed char signed_out_of_range = 255;
  unsigned char unsigned_out_of_range = -1;
  signed char signed_var {char_variable};

  std::cout << "char_variable "
    << char_variable << ", uchar_variable (as char) = "
    << uchar_variable << ", uchar_variable (as number) = "
    // cast to int to observe the numeric value
    // otherwise the terminal prints the character
    // corresponding to the ASCII value
    << (int)uchar_variable << ", schar_variable = "
    << (int)schar_variable << ", signed_out_of_range (initialized to 255) = "
    << (int)signed_out_of_range << ", unsigned_out_of_range (initialized to -1) = "
    << (int)unsigned_out_of_range << std::endl;

  // char and hex notation
  char c1 {'a'};
  char c2 {'\x61'};
  std::cout << "literal: " << c1 << " - with hex \\x61: " << c2 << std::endl; // print a


  // integers 
  int integer_variable {-2};
  unsigned int unsigned_integer_variable {10};
  signed int signed_integer_variable {-10};
  short short_variable {16};
  long long int long_variable {2147483648};

  // floating point
  double double_variable {0.2};

  // size of types
  std::cout << "sizeof(char) " << sizeof(char_variable) 
    << " <=  sizeof(short) " << sizeof(short_variable) 
    << " <=  sizeof(int) " << sizeof(integer_variable) 
    << " <=  sizeof(long) " << sizeof(long_variable) 
    << std::endl; 

  std::cout << "1 <= sizeof(bool) " << sizeof(boolean_variable) 
    << " <=  sizeof(long) " << sizeof(long_variable) 
    << std::endl; 

  std::cout << "sizeof(char) " << sizeof(char_variable) 
    << " <=  sizeof(wchar_t) " << sizeof(widechar_variable) 
    << " <=  sizeof(long) " << sizeof(long_variable) 
    << std::endl; 

  std::cout << "sizeof(int) " << sizeof(integer_variable)
    << " == sizeof(unsigned int) " << sizeof(unsigned_integer_variable)
    << " == sizeof(signed int) " << sizeof(signed_integer_variable)
    << std::endl; 

  long double long_double_variable {0.1};
  std::cout << "sizeof(double) " << sizeof(double_variable) << std::endl;
  std::cout << "sizeof(long_double_variable) " << sizeof(long_double_variable) << std::endl;

  // <cstdint> has the definition of types with a precise size
  int16_t two_byte {257};
  ++two_byte;

  // <cstddef> has the definition of size_t
  size_t size_of_int_in_this_architecture = sizeof(integer_variable);
  std::cout << "size_of_int_in_this_architecture = " 
    << size_of_int_in_this_architecture << std::endl;


  // declarations: we already used many!
  // just a couple more examples
  static const char * universities[] {"Padova", "Venezia"};
  int another_declaration {1};

  // scope and shadowing: to avoid 
  int a {1};
  {
    int a {2};
    std::cout << "inner block a = " << a << std::endl;
  }
  std::cout << "outer block a = " << a << std::endl;

  // auto 
  std::vector<int> vector = {1,2,3,4};
  std::vector<int>::iterator iter = vector.begin();
  auto iter2 = vector.begin();

  return 0;
}
