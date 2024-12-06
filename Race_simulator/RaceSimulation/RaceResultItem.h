#pragma once
#include "Vehicle.h"

class RaceResultItem
{
	friend class Race;
	public:
		RACESIMULATION_API Vehicle* const getVehicle() const;
		RACESIMULATION_API double getRaceTimeHr() const;
	protected:
		RaceResultItem(Vehicle* vehicle, double raceTimeHr);
		Vehicle* _vehicle;
		double _raceTimeHr;

};