/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include "namespaces-example.h"

int 
main(int argc, char const *argv[])
{
	// initialize the variable a_number of the global namespace
	::a_number = 1;

	// define a local variable and see that is shadows the global
	std::string a_number {"zero"}; // it's even of a different type!
	std::cout << "a_number (without qualifier) = " << a_number << std::endl;
	std::cout << "::a_number (with qualifier) = " << ::a_number << std::endl;
	// this is a bad practice and MUST be avoided

	// explicit qualification
	Animals::Mouse bianca {"bianca", 0.12};
	// using declarations
	using Animals::Mouse;
	Mouse ratatouille {"ratatouille", 0.2};
	
	using std::string;
	string rat_name {"bernie"};
	Mouse bernie {rat_name, 0.15};

	std::cout << "Print the mice names " << bianca.name << ", " 
		<< ratatouille.name << ", " << bernie.name << std::endl;

	return 0;
}