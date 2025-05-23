﻿#pragma once
#include "Vehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API AirVehicle : public Vehicle
{
	public:
		AirVehicle();
		AirVehicle(int _velocityKmh)
		{
			this->_velocityKmh = _velocityKmh;
		};
	protected:
		double getRaceTimeHr(const int distanceKm) const override;
		virtual double getDistanceReductionPercent(const int distanceKm) const = 0;
};