#include "FastCamel.h"

FastCamel::FastCamel()
{
    _name = "Верблюд-быстроход";
    _velocityKmh = 40;
    _motionTimeBeforeRestHr = 10;
}

double FastCamel::getRestTimeHr(const int distanceKm) const
{
    const auto restNumber = getRestNumber(distanceKm);
    double result = 0;
    if (restNumber >= 1)
    {
        // первый отдых 5 ч.
        result += 5;
    }

    if (restNumber >= 2)
    {
        // Второй - 6.5 ч, остальные  - 8 ч.
        result += 6.5 + (restNumber - 2) * 8;
    }

    return result;
}