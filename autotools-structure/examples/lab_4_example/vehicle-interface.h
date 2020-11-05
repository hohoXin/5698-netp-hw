/*
 * [2020] Network Programming - Northeastern University
 * All Rights Reserved.
 * 
 * Authors Michele Polese
*/

#ifndef VEHICLE_INTERFACE_H
#define VEHICLE_INTERFACE_H

#include <vector>
#include <string>
#include "passenger.h"

/**
 * The namespace Vehicle defines useful names to handle 
 * passengers inside a vehicle
 */
namespace Vehicle
{

class VehicleInterface {

public:
	virtual ~VehicleInterface() {};

	virtual int getNumberOfPassengers() const = 0;

	virtual int getMaxNumberOfPassengers() const = 0;

	virtual PassengerList getPassengerNames() const = 0;

	virtual void createPassenger(const std::string& pass_name, const std::string& pass_surname, bool drive_flag) = 0;
};

};

#endif // VEHICLE_INTERFACE_H