#pragma once
#include "VehicleAssignmentItem.h"
#include "RaceSimulationExports.h"

class VehicleAssignmentReport
{
	friend class Race;
	public:
		static const int MIN_VEHICLE_NUMBER = 2;
		RACESIMULATION_API ~VehicleAssignmentReport();
		RACESIMULATION_API VehicleAssignmentItem* const* const getItems() const;
		RACESIMULATION_API int getCount() const;
		RACESIMULATION_API int getAssignedCount() const;
		RACESIMULATION_API bool isReadyToRace() const;
		RACESIMULATION_API VehicleAssignmentItem* const operator [](const int i) const;
	protected:
		VehicleAssignmentReport(VehicleAssignmentItem** items, int count);
	private:
		VehicleAssignmentItem** _items;
		int _count;
		int _assignedCount;
};
