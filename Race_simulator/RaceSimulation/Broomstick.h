#pragma once
#include "AirVehicle.h"
#include "RaceSimulationExports.h"


class RACESIMULATION_API Broomstick : public AirVehicle
{
	public:
		Broomstick();
	protected:
		double getDistanceReductionPercent(const int distanceKm) const override;
};