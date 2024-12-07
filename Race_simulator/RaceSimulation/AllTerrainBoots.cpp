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
    const int FIRST_REST_TIME = 10;
    const int REST_NUMBER_REDUCTION = 1;
    const int MULTIPLIER = 5;

    double result = 0;
    if (restNumber > 0)
    {
        // первый отдых 10, остальные 5 часов
        result += FIRST_REST_TIME + (restNumber - REST_NUMBER_REDUCTION) * MULTIPLIER;
    }

    return result;
}