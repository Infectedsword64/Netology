#pragma once
#include "Vehicle.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API GroundVehicle: public Vehicle
{
    public:
        GroundVehicle();
    protected:
        // Время движения до отдыха
        int _motionTimeBeforeRestHr = 0;
        double getRaceTimeHr(const int distanceKm) const override;
        virtual double getMotionTimeHr(const int distanceKm) const;
        // Суммарное время отдыха на дистанции. У каждого ТС свой алгоритм
        virtual double getRestTimeHr(const int distanceKm) const = 0;
        // Количество раз, когда нужно отдохнуть на дистанции
        int getRestNumber(const int distanceKm) const;
};
