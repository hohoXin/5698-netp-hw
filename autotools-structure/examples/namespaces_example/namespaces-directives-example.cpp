/*
 * [2019] Signet Lab - Programming for ICT
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include "namespaces-example.h"

// use "using directives" with care, given that they can re-introduce the 
// same problems they should solve, i.e., name clashes
using namespace std;
using namespace Animals;

// this does not compile! (ambiguous name)
// using namespace Hardware;

int 
main(int argc, char const *argv[])
{
	string rat_name {"ratatouille"};
	Mouse ratatouille {rat_name, 0.2};
	
	std::cout << "Print the mice names " << ratatouille.name << std::endl;

	Hardware::Mouse logitech {true, true, false, 3};

	return 0;
}