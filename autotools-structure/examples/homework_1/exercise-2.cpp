/*
 * [2020] Northeastern University - Network Programming
 *
 * All Rights Reserved.
 * 
 * Authors Michele Polese 
 */

// remember to use the relevant #include
#include <iostream>

// the binary generated from this C++ code should be called
// with at least one extra command line argument
// for example: /path/to/bin/exercise_2 extra_argument
int main (int argc, char* argv[])
{
	// declare an array of C-style strings (i.e., string literals) 
	// which should contain the command-line arguments (i.e., the elements of argv),
	// except for the name of this binary (i.e., argv[0])
	// the size of the array should adapt to the number of arguments
	// passed from the command line (i.e., use the variable argc)

	// initialize each entry in the array with the command-line arguments
	// (except for the name of the binary, which is the first entry in argv)
	int word_num = argc - 1;
	char** word_cont = argv;
	char* world_first = *(word_cont + 1);

	// print the content of the array to the terminal, one entry for each line
	// (without using argv, use the new array!)
	for(int i = 1; i <= word_num; i++)
	{
		std::cout << *(word_cont + i) << std::endl;
	}

	// print the first string literal in the array, one letter for each line
	for(; *world_first != '\0'; ++world_first)
    {
    	std::cout << *world_first << std::endl;
    }

	return 0;
}