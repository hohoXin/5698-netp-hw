/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include <cstddef>
#include <type_traits>


void
checkArrayDecayToPointer(int array[8])
{
  std::cout << "use extent to get the size of an array passed as argument: " 
    << std::extent<decltype(array)>::value 
    << " (returns the wrong size)"
    << std::endl;
}


int main(int argc, char* argv[])
{
  // pointers
  int variable {10};
  int* pointer_to_variable {&variable}; // & is the address of operator
  int another_variable = *pointer_to_variable; // dereferencing or indirection
  int* pointer_to_another_variable = &another_variable;

  std::cout << "variable " << variable 
    << " pointer_to_variable " << pointer_to_variable
    << " another_variable " << another_variable
    << " pointer_to_another_variable " << pointer_to_another_variable
    << std::endl;


  // void*
  void* void_pointer = pointer_to_variable; // ok: implicit conversion of int* to void*
  void* void_pointer_2 {pointer_to_variable}; // also ok: not considered narrowing
  // int dereferenced_variable = *void_pointer; // compilation error : can’t dereference void*
  // ++void_pointer; // warning (but should be an error): can’t increment void* (the size of the object pointed to is unknown)

  void* void_pointer_to_same_variable = &variable;

  // you can compare void pointers
  if(void_pointer == void_pointer_to_same_variable)
  {
    std::cout << "Point to the same entity" << std::endl;
  }
  
  if(void_pointer == pointer_to_variable)
  {
    std::cout << "Point to the same entity, and you can compare void* and int*"
      << std::endl;
  }

  // you can use static_cast to explicitly cast it to a pointer of another type
  // but it is unsafe, because you may use or not know the correct type
  double* pointer_to_wrong_type = static_cast<double*>(void_pointer);
  std::cout << "Correct int value = " << *pointer_to_variable 
    << ", wrong double representation = " << *pointer_to_wrong_type
    << std::endl;

  pointer_to_wrong_type = nullptr; // now pointer_to_wrong_type does not point to anything
  std::cout << "This pointer has nullptr, which in this architecture has value = " 
    << pointer_to_wrong_type << std::endl;

  // pointers and const
  const char* p = "unipd"; // read from right to left: this is a pointer to a const char
  char single_char = 'b';
  char* p_single = &single_char;
  ++p; // not error
  // (*p) = 'c'; //error
  (*p_single) = 'c'; // not error
  const char* const p2 = "unipd"; // the pointer is const as well 
  // ++p2; // error


  // arrays
  double array[3] {0.1, 0.2, 0.3};
  // very low-level entity, to be possibly avoided
  // no range checking
  std::cout << "array - entry 0 = " << array[0]
    << ", entry 1 = " << array[1]
    << ", entry 2 = " << array[2]
    << ", entry out of range = " << array[99]
    << std::endl;


  // initialization
  // with a list
  int v[] = {1,2,3,4}; // the size is assigned automatically (4)
  const int size = 8;
  // the size with which an array is initialized must be const
  int v2[size] = {1,2,3,4}; // the size is 8 -> 1,2,3,4,0,0,0,0
  // int v3[2] = {1,2,3,4}; // compilation error (too many initializers)

  // string literals
  const char string_example[6] = "unipd"; // this is an array with 5 characters + 1
  std::cout << sizeof(string_example) << std::endl; // 6

  // pointers and arrays
  // the name of an array can be used as pointer to its first element
  std::cout << "v[0] = " << v[0] << ", *v = " << *v << std::endl;
  std::cout << "&v[0] = " << &v[0] << ", v = " << v << std::endl;
  
  // navigating arrays
  // the size must be known explicitely when navigating arrays
  for(int * p1 = v2; p1 < v2 + size; ++p1) // this check is on the value of the pointer (i.e., the address)
  {
    std::cout << *p1 << std::endl;
  }

  // equivalent to
  for(int index = 0; index < size; ++index)
  {
    std::cout << v2[index] << std::endl;
  }

  // it is possible to use extent to get the size of an array
  std::cout << "use extent to get the size of array v " << std::extent<decltype(v)>::value << std::endl;
  std::cout << "use extent to get the size of array v2 " << std::extent<decltype(v2)>::value << std::endl;
  // but it does not always work! The array decays (or "adjusts") into a pointer when passed to a function
  checkArrayDecayToPointer(v2);

  // the size does not need to be known for string literals
  const char* str_lit_without_explicit_size = "unipd";

  // you can directly use the array name, but in this way 
  // you may lose a pointer to the first element
  // thus it would be better to use another pointer
  for(; *str_lit_without_explicit_size != '\0'; ++str_lit_without_explicit_size)
  {
    std::cout << *str_lit_without_explicit_size  << std::endl;
  }

  // this is wrong: sizeof(str_lit_without_explicit_size) is the size of the pointer
  const char* str_lit_without_explicit_size_2 = "unipd";
  size_t sizeof_ptr_to_str_lit = sizeof(str_lit_without_explicit_size_2);
  std::cout << "this is the size of a pointer! " << sizeof_ptr_to_str_lit << std::endl;
  for(unsigned int index = 0; index < sizeof_ptr_to_str_lit; ++index)
  {
    std::cout << str_lit_without_explicit_size_2[index] << std::endl;
  }
  // this is correct (no access out of range)
  const char str_lit_without_explicit_size_3[] = "unipd";
  // an array does not decay into a pointer for sizeof
  // the size is 6 (5 characters and the zero terminator)
  size_t sizeof_str_lit = sizeof(str_lit_without_explicit_size_3);
  std::cout << "this is the size of the string literal " << sizeof_str_lit << std::endl;
  for(unsigned int index = 0; index < sizeof_str_lit; ++index)
  {
    std::cout << str_lit_without_explicit_size_3[index] << std::endl;
    // the last iteration will print the character '\0',
    // which appears as an empty line
  }

  int v_int_1[10];
  int v_int_2[10];

  int* v_int_1_begin = v_int_1;
  std::cout << "v_int_1_begin = " << v_int_1_begin << std::endl;
  std::cout << "++v_int_1_begin = " << ++v_int_1_begin << std::endl;

  std::cout << "&v_int_1[5] - &v_int_1[3] = " << &v_int_1[5] - &v_int_1[3] << std::endl;
  std::cout << "&v_int_1[5] - &v_int_2[3] = " << &v_int_1[5] - &v_int_2[3] 
    << " (undefined)" << std::endl; // result undefined


  // references
  int var {1};
  int &ref {var}; // always need initialization, and cannot be changed after

  int var2 = ref + 10; // increase the numeric value, not the address!
  int* pointer = &ref;
  int* pointer2 = pointer + 10; // increase the pointer, not the value!
  std::cout << "var = " << var << ", var2 = " << var2 << ", *pointer2 = " << *pointer2 << std::endl;

  return 0;
}
