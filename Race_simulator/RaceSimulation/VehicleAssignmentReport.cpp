#include "VehicleAssignmentReport.h"

VehicleAssignmentReport::VehicleAssignmentReport(VehicleAssignmentItem** items, int count)
{
	_items = items;
	_count = count;
	_assignedCount = 0;
	for (int i = 0; i < _count; ++i)
	{
		if (_items[i]->getAssigned())
		{
			++_assignedCount;
		}
	}
}

VehicleAssignmentReport::~VehicleAssignmentReport()
{
	for (int i = 0; i < _count; ++i)
	{
		delete _items[i];
	}

	delete[] _items;
}

VehicleAssignmentItem* const* const VehicleAssignmentReport::getItems() const
{
	return _items;
}

int VehicleAssignmentReport::getCount() const
{
	return _count;
}

RACESIMULATION_API int VehicleAssignmentReport::getAssignedCount() const
{
	return _assignedCount;
}

bool VehicleAssignmentReport::isReadyToRace() const
{
	return _assignedCount >= MIN_VEHICLE_NUMBER;
}

VehicleAssignmentItem* const VehicleAssignmentReport::operator[](const int i) const
{
	return _items[i];
}
