/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#ifndef H_NAMESPACES_EXAMPLE
#define H_NAMESPACES_EXAMPLE

#include <string>

// let's define a variable in the global namespace
int a_number;

namespace Animals
{
	/**
	 * a struct that describes a mouse
	 */
	struct Mouse {
		std::string name;
		double weight;
	};

	/**
	 * a struct that describes a moose
	 */
	struct Moose {
		std::string name;
		double weight;
	};
}; // namespace Animals

namespace Hardware
{
	/**
	 * a struct that describes a mouse for a computer
	 */
	struct Mouse {
		bool isLaser;
		bool hasWheel;
		bool isWireless;
		int numButtons;
	};

	/**
	 * a struct that describes a keyboard
	 */
	struct Keyboard {
		int numKeys;
		bool isWireless;
	};
}; // namespace Hardware

#endif // H_NAMESPACES_EXAMPLE