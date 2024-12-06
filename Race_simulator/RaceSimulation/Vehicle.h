#pragma once
#include "VehicleType.h"
#include <string>
#include "RaceSimulationExports.h"

// Абстрактный базовый класс для ТС
class RACESIMULATION_API Vehicle
{
public:
    friend class Race;
    virtual ~Vehicle();
    std::string& getName();
    VehicleType getVehicleType();
protected:
    VehicleType _type;
    int _velocityKmh;
    std::string _name;
    // Внешним пользователям библиотеки незачем иметь доступ к этому методу, но сделал доступным классу Race
    virtual double getRaceTimeHr(const int distanceKm) const = 0;
};
