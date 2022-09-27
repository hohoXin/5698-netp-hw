/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include <vector>
#include <chrono>

// the following functions are just examples, and what they do 
// is not necessarily meaningful

// test functions for local variables in functions
void localAndStaticVariablesExample(int number)
{
  int local_variable = number + 2;
  // this is actually initialized only at the first call
  static int static_variable = number + 2;
  std::cout << "local_variable = " << local_variable 
    << ", static_variable = " << static_variable 
    << std::endl;
}

// this is WRONG, shown here just as an example,
// but DO NOT use it in your code
int* returnLocalPointer()
{
  int local_variable = 1; // this is local
  int another_local_variable = 4;
  int result_local_variable = local_variable + another_local_variable;
  // the compiler gives a warning!
  // DO NOT use it in your code
  return &result_local_variable;
}


// test functions for argument passing
int incrementValueAndReferenceAndPointer(int value, int& reference, int* pointer)
{
  // first, increase value by one
  ++value;
  // second, increase reference by one
  ++reference;
  // then, increase the variable pointed by the pointer
  // given that you need to dereference, it is clearer
  // than when using references that you are actually
  // modifying the value which is pointed by the pointer
  ++(*pointer);

  // sum them and return
  return value + reference + (*pointer);
}

// this is just an example, DO NOT pass an object
// by value, use a const ref as below
bool checkIfThereIsAByValue(std::string str)
{
  return (str.find_first_of("a") > 0);
}

bool checkIfThereIsAByConstReference(const std::string& str)
{
  return (str.find_first_of("a") > 0);
}


// test functions for overload resolution
void print(int a)
{
  std::cout << "print(int) " << a << std::endl;
}
void print(const char* a)
{
  // it is a good practice to check, when working with pointers
  // in functions
  if (a != nullptr)
  {
    std::cout << "print(const char*) " << *a << std::endl;
  }
}
void print(const std::string& a)
{
  std::cout << "print(const std::string& a) " << a << std::endl;
}
void print (long a)
{
  std::cout << "print(long) " << a << std::endl;
}
void print(double a)
{
  std::cout << "print(double) " << a << std::endl;
}
void print(char a)
{
  std::cout << "print(char) " << a << std::endl;
}


// test function for pointer to function conversions and default arguments
int increaseByTwo(int number = 0)
{
  std::cout << "number " << number << " " << &number << std::endl;
  return number + 2;
}



int main(int argc, char* argv[])
{
  // local and static variables
  localAndStaticVariablesExample(2);
  localAndStaticVariablesExample(3);
  localAndStaticVariablesExample(4);


  // returning a pointer or a reference to a local variable is bad
  // int a_number = *returnLocalPointer(); // this should be 5
  // std::cout << "The number returned should be 5, but is "
  //   << a_number << std::endl;


  // argument passing
  // let's compare what happens when passing by value 
  // and when passing by reference or by pointer
  int value {1};
  int value_for_reference {1}; // we not want the reference to point to value for this example
  int value_for_pointer {1};

  int return_value = incrementValueAndReferenceAndPointer(value, value_for_reference, &value_for_pointer);
  // let's check what has changed
  std::cout << "After the function was executed, value = "
    << value << ", value_for_reference = "
    << value_for_reference << ", value_for_pointer = "
    << value_for_pointer << ", return_value = "
    << return_value << std::endl;

  // let's compare what happens when passing by value or by const ref
  std::string long_string {
      "jnokzcfglpizjltxcedzvnnogiafhxgtbxvwlbbuewjnicentcscmcokyynobklusknccjdcngdpkjsemdoijlchxmxjqijvdhuhbjyxyjwnbltvsglezwbm"
  };
  
  auto start = std::chrono::system_clock::now();
  auto is_there_a_by_value = checkIfThereIsAByValue(long_string);
  auto end = std::chrono::system_clock::now();
  auto elapsed_by_value = (std::chrono::duration_cast<std::chrono::nanoseconds> (end-start)).count();
  start = std::chrono::system_clock::now();
  auto is_there_a_by_cref = checkIfThereIsAByConstReference(long_string);
  end = std::chrono::system_clock::now();
  auto elapsed_by_cref = (std::chrono::duration_cast<std::chrono::nanoseconds> (end-start)).count();
  std::cout << "Elapsed by value = " << elapsed_by_value 
    << " ns, elapsed by const ref = " << elapsed_by_cref
    << " ns" << std::endl;


  // overload resolution
  char c = 'c';
  int i = 0;
  short s = 1;
  float f = 2.0;
  print(c); // exact match: invoke print(char)
  print(i); // exact match: invoke print(int)
  print(s); // integral promotion: invoke print(int)
  print(f); // float to double promotion: print(double)
  print('a'); // exact match: invoke print(char)
  print(49); // exact match: invoke print(int)
  print(0); // exact match: invoke print(int)
  print("a"); // exact match: invoke print(const char*)
              // this does not invoke print(const std::string&)
              // because it would require an implicit cast.
              // If print(const char*) was not declared,
              // then print(const std::string&) would have been 
              // selected with the implicit cast
  print(nullptr); // nullptr_t to const char* promotion: invoke print(cost char*)
  print(long {i}); // manual overload resolution
  print(std::string {"a"}); // manual overload resolution

  // example of bad usage of pointers to functions
  using P1 = int (*)(int);
  using P2 = int (*)(void);

  P1 pf {increaseByTwo};

  P2 wrong_pointer_type = reinterpret_cast<P2>(pf);
  std::cout << wrong_pointer_type() << std::endl;

  P1 correct_pointer_type = reinterpret_cast<P1>(wrong_pointer_type);
  std::cout << correct_pointer_type(2) << std::endl;
  std::cout << increaseByTwo() << std::endl;

  return 0;
}
