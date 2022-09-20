/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include <cstddef>
#include <type_traits>
#include "structs-enums-example.h"

using namespace StructsEnumsTest;

int main(int argc, char* argv[])
{
  Address jd;
  jd.name = "Jim Dandy";
  jd.number = 61;

  Address john_doe = {
    "John Doe",
    42,
    "Some Street",
    "A City",
    {'N', 'Y'},
    "02130"
  };

  // access by name
  std::cout << "Access by name to Address: john_doe.name = " 
    << john_doe.name
    << ", john_doe.number = "
    << john_doe.number
    << std::endl;

  // access by reference
  Address& reference_to_john_doe {john_doe};
  std::cout << "Access by name to Address: reference_to_john_doe.name = " 
    << reference_to_john_doe.name
    << ", reference_to_john_doe.number = "
    << reference_to_john_doe.number
    << std::endl;

  // access by pointer
  Address* pointer_to_john_doe {&john_doe};
  std::cout << "Access by pointer to Address: pointer_to_john_doe->name = " 
    << pointer_to_john_doe->name
    << ", pointer_to_john_doe->number = "
    << pointer_to_john_doe->number
    << std::endl;
  // alternative
  std::cout << "Another (less common) way to access by pointer to Address: (*pointer_to_john_doe).name = " 
    << (*pointer_to_john_doe).name
    << ", (*pointer_to_john_doe).number = "
    << (*pointer_to_john_doe).number
    << std::endl;

  // declare, initialize and then update consistently 
  // the struct List and struct Element examples
  List list {nullptr};
  Element first {nullptr, nullptr, &list, 0}; // arbitrarly choose 0 as value
  list.head = &first;
  Element second{&first, nullptr, &list, 1}; // arbitrarly choose 1 as value
  first.next = &second;

  std::cout << "list.head = " << list.head 
    << ", &first = " << &first
    << ", first.next = " << first.next
    << ", &second = " << &second
    << ", second.previous = " << second.previous
    << std::endl;

  // struct constructors
  int first_number = 1;
  int second_number = 2;
  Numbers numbers(first_number, second_number);  
  // this does not compile: a struct with an explicit constructor
  // does not have an implicit default constructor (you need to 
  // explicitely declare it)
  // Numbers numbers_2; 

  std::cout << "Print numbers: ";
  for (auto elem : numbers.elem)
  {
    std::cout << elem << ", ";
  }
  std::cout << std::endl;

  // Trivial trivial(5);
  std::cout << "The Trivial struct is a POD: " 
    << std::is_pod<Trivial>::value << std::endl;
  std::cout << "The Address struct is a POD: " 
    << std::is_pod<Address>::value << std::endl;
  std::cout << "The Numbers struct is not a POD (non trivial constructor): " 
    << std::is_pod<Numbers>::value << std::endl;

  // enum class: typed and scoped!
  TrafficLight a = TrafficLight::green;
  // int a2 = a; // compilation error
  // cannot initialize a variable of type 'int' with an lvalue of type 'StructsEnumsTest::TrafficLight'
  // bool a3 {a == 2}; // compilation error
  // invalid operands to binary expression ('StructsEnumsTest::TrafficLight' and 'int')
  Other b = Other::green;
  // need a cast to print it
  std::cout << "TrafficLight::green " << static_cast<int>(a) <<std::endl;

  // redefine operators on enum classes
  Printer_flags no_color = Printer_flags::out_of_color;  
  Printer_flags no_black = Printer_flags::out_of_black;
  Printer_flags printer_status = Printer_flags::out_of_color;
  printer_status = printer_status|Printer_flags::out_of_black;

  switch (printer_status)
  {
    case (Printer_flags::out_of_color|Printer_flags::out_of_black): {
      std::cout << "Out of some color" << std::endl;
      break;
    }
    case Printer_flags::busy: {
      std::cout << "Busy" << std::endl;
      break;
    }
    default: {
      std::cout << "None of the above" << std::endl;
    }
  }

  // enum
  TrafficLightEnum a_enum = green;
  int a_int = a_enum; // no errors
  bool a_bool {a_enum == 0}; // no errors

  // enum scoped in a struct
  EnumScoped::OtherEnum another_enum = EnumScoped::green;
  // this can be done, because there is an implicit conversion to integers,
  // but raises a warning because it is a comparison between enumerators
  // of different enums, and logically may not have the same meaning
  // Therefore, it is better to avoid it
  bool another_bool {a_enum == another_enum}; 
  std::cout << "another_bool " << another_bool << std::endl;

  return 0;
}
