#pragma once
#include "AirVehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API Eagle : public AirVehicle
{
	public:
		Eagle();
	protected:
		double getDistanceReductionPercent(const int distanceKm) const override;
};