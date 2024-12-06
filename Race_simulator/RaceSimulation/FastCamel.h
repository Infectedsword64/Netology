#pragma once
#include "GroundVehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API FastCamel : public GroundVehicle
{
public:
    FastCamel();

protected:
    virtual double getRestTimeHr(const int distanceKm) const override;
private:
};