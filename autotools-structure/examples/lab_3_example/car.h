/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <vector>
#include <string>
#include "passenger.h"

/**
 * The namespace Vehicle defines useful names to handle 
 * passengers inside a vehicle
 */
namespace Vehicle
{

using PassengerList = std::vector<Passenger*>;

/**
 * The C++ class Car is a user-defined type to represent 
 * a Car. This class owns resources, i.e., the passengers 
 * are created in this class as pointers, and need to be handled
 * correctly when copying or destroying a Car object
 */
class Car {

public: // public interface
	/**
	 * Constructor for a Car object
	 * It is explicit to avoid unwanted implicit conversions
	 * @param plates string to represent the plates for the class, with default empty string
	 */
	explicit Car(const int maximum_number_passengers, const std::string& plate = "");

	/**
	 * Copy constructor: needs to cope with pointers
 	 * @param car_to_copy a const lvalue ref to a Car object
	 */
	// Exercise 1: declare and implement (in the .cpp) the copy constructor

	/**
	 * Copy assignment: needs to cope with pointers
	 * @param car_to_copy a const lvalue ref to a Car object
     * @return an lvalue ref to the copied object
	 */
  	Car& operator=(const Car& car_to_copy);

  	/**
  	 * Destructor - needs to cope with memory resources
  	 */
  	~Car();

	// non-modifying members to inspect a class
	// Exercise 7 (important!): enforce the const correctness on the get methods of this class
	/**
	 * Get the number of Passengers
	 * @return the number of registered Passengers
	 */
	int getNumberOfPassengers();

	/**
	 * Get the maximum number of Passengers
	 * @return the maximum number of Passengers
	 */
	// Exercise 4: declare and implement (in the .cc) a method that gets the max number of passengers

	/**
	 * Get the list of Passengers
	 * @return a vector with the Passengers names
	 */
	PassengerList getPassengerNames() const;

	/**
	 * Get the plate
	 * @return a string with the plate
	 */
	std::string getPlates();

	/**
	 * Set the plate name
	 * @param a string with the plate
	 */
	// Exercise 5: declare and implement (in the .cc) a method that sets the plate
	// then use it in the lab_3_example executable

    /**
	 * Set the max_passengers limit 
	 * @param mx_pass int with the max passengers limit
	 */
	// Exercise 6: declare and implement (in the .cc) a method that sets the max number of passengers
	// then use it in the lab_3_example executable

	// modifying functions to change the Car
	/**
	 * Add a Passenger
	 * @param pass_name the passenger name
	 * @param pass_surname the passenger surname
	 * @param drive_flag a boolean which indicates if the passenger can drive or not
	 */
	void createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag);

private:
	PassengerList m_passengers; /**<list of pointers to Passenger objects */
	std::string m_plates; /**<plates of the Car */
    int m_max_passengers;
};


}; // end of namespace Vehicle

