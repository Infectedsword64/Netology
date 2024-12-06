#pragma once
#include "Vehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API VehicleAssignmentItem
{
	friend class Race;
	public:
		Vehicle* const getVehicle() const;
		bool getAssigned() const;
		bool getAvailableToAssign() const;
	protected:
		VehicleAssignmentItem(Vehicle* vehicle, bool assigned, bool availableToAssign);
		Vehicle* _vehicle;
		bool _assigned;
		bool _availableToAssign;
};

