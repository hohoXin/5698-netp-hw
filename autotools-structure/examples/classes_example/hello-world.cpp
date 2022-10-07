/*
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include "student.h"

int
main(int argc, char const *argv[])
{
	Student s1{"John","Doe","jd",45235};
	std::cout << "Hello " << s1 << "!" << std::endl; 
	s1.setName("Michele");
	s1.setSurname("Polese");
	s1.setAccount("mp");
	std::cout << "Hello " << s1 << "!" << std::endl; 

	return 0;
}
