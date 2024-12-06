#include "AllTerrainBoots.h"

AllTerrainBoots::AllTerrainBoots()
{
    _name = "Ботинки-вездеходы";
    _velocityKmh = 6;
    _motionTimeBeforeRestHr = 60;
}

double AllTerrainBoots::getRestTimeHr(const int distanceKm) const
{
    const auto restNumber = getRestNumber(distanceKm);
    double result = 0;
    if (restNumber > 0)
    {
        // первый отдых 10, остальные 5 часов
        result += 10 + (restNumber - 1) * 5;
    }

    return result;
}