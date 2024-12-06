#pragma once
#include "GroundVehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API Centaur : public GroundVehicle
{
public:
    Centaur();

protected:
    virtual double getRestTimeHr(const int distanceKm) const override;
private:
};
