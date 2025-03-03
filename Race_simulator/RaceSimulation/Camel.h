﻿#pragma once
#include "GroundVehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API Camel: public GroundVehicle
{
    public:
        Camel();

    protected:
        double getRestTimeHr(const int distanceKm) const override;
    private:
};
