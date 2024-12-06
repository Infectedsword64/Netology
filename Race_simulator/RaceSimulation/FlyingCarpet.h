#pragma once
#include "AirVehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API FlyingCarpet : public AirVehicle
{
	public:
		FlyingCarpet();
	protected:
		double getDistanceReductionPercent(const int distanceKm) const override;
};
