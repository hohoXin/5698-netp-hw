/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <iostream>
#include "car.h"

namespace Vehicle {

Car::Car(const int mx_pass, const std::string& plates) 
// Exercise 2: use the member initialization list to assign the values
// passed by the constructor to the private variables of this class,
// and to initialize an empty vector
{

}

// Exercise 1: implement the copy constructor (and declare it in the .h)
// You can take a look at the implementation of the copy assignment
// The copy constructor will have to do a member-wise copy of each variable,
// using the member init list, except for m_passengers, for which you need
// to copy the object pointed to by the entiers in m_passengers of the object 
// to be copied, or create new Passengers (as in the copy assignment below)
Car::Car(const Car& car_to_copy);

Car& Car::operator=(const Car& car_to_copy) 
{
    // clear the passengers list
    m_passengers.clear();
    m_plates = car_to_copy.m_plates; // Exercise 7: now that the get method is const, you can use the method instead than accessing the variable
    m_max_passengers = car_to_copy.m_max_passengers; // Exercise 4: use the method you implemented instead than the access to the variable

    // this is the piece of code that guarantees no shallow copy
    for (auto pass : car_to_copy.getPassengerNames())
    {
        // here, you can re-use a function rather than copying the same code twice!
        createPassenger(pass->getName(), pass->getSurname(), pass->getCanDrive());
    }

    return *this;
}

Car::~Car()
{
    // we need to delete the memory that was created in this class
    // Exercise 3: use a for loop to cycle over the entries in m_passengers, 
    // and call delete on the pointer (e.g., if the pointer is called pass, as in line
    // 37 above, you need to call "delete pass;")
}


int
Car::getNumberOfPassengers()
{
	return m_passengers.size();
}

// Exercise 4: declare (in the .h) and implement a method that gets the max number of passengers

PassengerList
Car::getPassengerNames() const
{
	return m_passengers;
}

std::string 
Car::getPlates()
{
	return m_plates;
}

// Exercise 5: declare (in the .h) and implement a method that sets the plate
// then use it in the lab_3_example executable

// Exercise 6: declare (in the .h) and implement a method that sets the max number of passengers
// then use it in the lab_3_example executable

void
Car::createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag)
{
    // Exercise 8: implement this method, that does the following:
    // - checks if there is room for a new passenger in the car
    // - if yes, it creates a new Passenger by using the operator new:
    // Passenger *pass = new Passenger{...};
    // where ... are the parameters to pass to the constructor of Passenger
    // - it adds the pointer pass to m_passengers (take a look at the documentation for std::vector)

    // - if no, it prints an error and does not do anything else
}

}
