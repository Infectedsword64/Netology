#include "VehicleAssignmentItem.h"

VehicleAssignmentItem::VehicleAssignmentItem(Vehicle* vehicle, bool assigned, bool availableToAssign)
{
	_vehicle = vehicle;
	_assigned = assigned;
	_availableToAssign = availableToAssign;
}

Vehicle* const VehicleAssignmentItem::getVehicle() const
{
	return _vehicle;
}

bool VehicleAssignmentItem::getAssigned() const
{
	return _assigned;
}

bool VehicleAssignmentItem::getAvailableToAssign() const
{
	return _availableToAssign;
}
