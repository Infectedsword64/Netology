#include "Camel.h"

Camel::Camel()
{
    _name = "Верблюд";
    _velocityKmh = 10;
    _motionTimeBeforeRestHr = 30;
}

double Camel::getRestTimeHr(const int distanceKm) const
{
    const auto restNumber = getRestNumber(distanceKm);
    double result = 0;
    if (restNumber > 0)
    {
        // первый отдых 5, остальные 8 часов
        result += 5 + (restNumber - 1) * 8;
    }
    
    return result;
}
