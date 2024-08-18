/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

// missing header file
#include <iostream>

struct Trivial {
  int a; 
  Trivial(int aa) : a(aa) { } 
  Trivial() = default; // use the compiler generated 
                       // constructor
};

// // do not modify the enumerators, find some other way
// enum NotScoped {green, blue, red};
// enum SameEnumerators {green, yellow};

// do not modify the enumerators, find some other way
enum NotScoped {green, blue, red};
enum class SameEnumerators {green, yellow};

int main(int argc, char* argv[])
{
  // unsigned int is 4 bytes 0 to 4,294,967,295
  // short is 2 bytes -32,768 to 32,767
  // cr: www.geeksforgeeks.org/c-data-types/

  // original code:
  // unsigned int unsigned_integer_variable {-10}
  // short short_variable {90000};

  unsigned int unsigned_integer_variable {10};
  short short_variable {9000};

  std::cout << "unsigned_integer_variable " << unsigned_integer_variable
    << " short_variable " << short_variable << std::endl;

  // void* pointer {&unsigned_integer_variable};
  unsigned int* pointer {&unsigned_integer_variable};
  std::cout << "pointer content " << pointer 
    << " value pointed by pointer " << *pointer << std::endl;

  const char* p = "northeastern";
  // create a new char pointer whose value can be changed
  char* p1;
  *(p1) = *(p);
  std::cout << "before modification " << *(p1) << std::endl;
  // (*p) = 'c';
  *(p1) = 'c';
  std::cout << "after modification " << *(p1) << std::endl;

  Trivial structure{10};
  Trivial* ptr_struct{&structure};

  // std::cout << "Value in struct " << structure->a 
  //   << " with pointer " << ptr_struct.a << std::endl;
  std::cout << "Value in struct " << structure.a 
    << " with pointer " << ptr_struct->a << std::endl;
 
  return 0;
}
