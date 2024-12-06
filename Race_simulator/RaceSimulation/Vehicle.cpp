#include "Vehicle.h"

Vehicle::~Vehicle()
{
}

std::string& Vehicle::getName()
{
    return _name;
}

VehicleType Vehicle::getVehicleType()
{
    return _type;
}
