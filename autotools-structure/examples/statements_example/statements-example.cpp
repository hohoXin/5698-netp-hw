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

enum class Actions {exec_and_display, display, other};

int main(int argc, char* argv[])
{
  // declarations as statements
  // this is generally a bad practice: it is better
  // to declare a variable and initialize it contextually, i.e.,
  // declare it when there is a value available to initialize it
  int result_of_sum, result_of_multiplication_after_sum;
  result_of_sum = 4 + 5;
  result_of_multiplication_after_sum = result_of_sum * 10;

  // a better way to write this code is
  int result_of_sum_b {4 + 5};
  int result_of_multiplication_after_sum_b {result_of_sum_b * 10};

  // selection statements
  // if
  int x {1};
  int* x_pointer {&x};

  if(x) { // the condition is implicitly converted to bool
    // equivalent to if (x != 0)
    std::cout << "x != 0" << std::endl;
  }

  if (x_pointer) { // equivalent to x_pointer != nullptr
    std::cout << "x_pointer != nullptr" << std::endl;
  }

  if (x_pointer != nullptr && *x_pointer != 0)
  { // the second condition is evaluated only
  	// if x_pointer is not a nullptr, this avoids 
  	// accessing the value of a pointer which is not valid
  	std::cout << "Pointer value " << *x_pointer << std::endl;
  }

  x_pointer = nullptr;
  if (x_pointer || x) { // the second condition is evaluated only
    // if x_pointer is a nullptr (thus the first is false)
    std::cout << "x_pointer = " << x_pointer << " and both conditions checked" << std::endl;
  }

  // conditional or ternary operator
  double coefficient = (result_of_multiplication_after_sum_b > 20) ? 0.1 : 1;
  // is equivalent to
  double coefficient_if;
  if (result_of_multiplication_after_sum_b > 20) {
    coefficient_if = 0.1;
  }
  else {
    coefficient_if = 1;
  }

  // the scope is limited
  if (int x_if = 1) {
    int x_if_in_block = x_if + 1;
    std::cout << "x_if = " << x_if << std::endl;
    std::cout << "x_if_in_block = " << x_if_in_block << std::endl;
  }
  else {
    std::cout << "x_if = " << x_if << std::endl;
    // the following line would yield a compilation error
    // because x_if_in_block is not in scope in the else block
    // std::cout << "x_if_in_block = " << x_if_in_block << std::endl;
  }

  //switch statement
  int switch_variable = 2;
  switch(switch_variable) {
    case 1:
    {
      std::cout << "Case 1" << std::endl;
      break;
    }
    case 2:
    {
      std::cout << "Case 2" << std::endl;
      // break; // comment out the break on purpose,
      // let's see what happens
    }
    case 3:
    {
      std::cout << "Case 3" << std::endl;
      break;
    }
    default: // you can have a default case
    // to handle the exception (case not covered)
    // or the case that is covered most of the times
    {
      std::cout << "This is the default" << std::endl;
    }
  }

  Actions action = Actions::exec_and_display;

  switch(action)
  {
    case Actions::exec_and_display:
    {
      std::cout << "In this case we implement only the exec part" << std::endl;
      // do not break on purpose, so that the next case will be executed
      // it is a good practice to comment when a break is left out on purpose
    }
    case Actions::display:
    {
      std::cout << "Then we display" << std::endl;
      break;
    }
    case Actions::other:
    {
      std::cout << "Other" << std::endl;
      break;
    }
    // we do not add a default case, so that the compiler
    // can check if all the cases of the enum were covered
    // by default, and, in case, it issues a warning
  }

  // range-for statements
  std::vector<int> int_vector {1,2,3,4,5,6};
  std::cout << "Print the int_vector values: ";
  for (auto value : int_vector) { // auto is handy with for loops
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::cout << "Modify int_vector values (first loop)";
  for (int& value : int_vector) { // need to specify that the type is a reference
    ++value; // the value stored in the vector is modified
  }
  std::cout << " and print them (second loop): ";
  for (auto value : int_vector) { // auto is handy with for loops
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // for statements
  std::cout << "Print the int_vector values with a for loop: ";
  // a range-for loop over int_vector can be expressed
  // also with a for loop
  // here auto replaces std::vector<int>::iterator
  for (auto iter = int_vector.begin(); iter != int_vector.end(); ++iter) {
    std::cout << *iter << " "; // we will discuss iterators in details further on
  }
  std::cout << std::endl;

  int variable_available_after_for {0};
  int accumulator {10};
  for(; variable_available_after_for < 10; ++variable_available_after_for)
  {
    --accumulator;
  }
  std::cout << "variable_available_after_for " << variable_available_after_for << std::endl;

  // while statements
  // in general, they can be used more naturally to express stopping
  // conditions than while loops
  int target_value {4};
  auto iter = int_vector.begin();
  while (iter != int_vector.end() && *iter <= target_value) 
  // check the range of the iterator first, and then the value
  {
    std::cout << *iter << " <= " << target_value << std::endl;
    ++iter;
  }

  // do statements
  const char test_string[] = "unipd";
  std::cout << "Print a string backward with a do: ";
  int i = sizeof(test_string) - 1; // we do not want to print the \0 terminator
  do {
    std::cout << test_string[--i];
  } while (i > 0); // notice the semicolon
  std::cout << std::endl;

  // it's easy to make mistakes, because the condition needs to hold 
  // also in the first loop
  const char empty_string[] = "";
  std::cout << "Print an empty string, backward with a do: ";
  i = sizeof(empty_string) - 1; // we do not want to print the \0 terminator
  do {
    std::cout << empty_string[--i]; // this points to an uninitialized byte
  } while (i > 0); // notice the semicolon
  std::cout << std::endl;

  return 0;
}
