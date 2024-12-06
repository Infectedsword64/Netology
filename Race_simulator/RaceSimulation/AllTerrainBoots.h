#pragma once
#include "GroundVehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API AllTerrainBoots : public GroundVehicle
{
public:
    AllTerrainBoots();

protected:
    virtual double getRestTimeHr(const int distanceKm) const override;
private:
};
