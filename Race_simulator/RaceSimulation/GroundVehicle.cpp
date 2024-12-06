#include "GroundVehicle.h"
#include <cmath>

GroundVehicle::GroundVehicle()
{
    _type = GROUND_VEHICLE;
}

double GroundVehicle::getMotionTimeHr(const int distanceKm) const
{
    return static_cast<double>(distanceKm) / _velocityKmh;
}

int GroundVehicle::getRestNumber(const int distanceKm) const
{
    const auto numberOfMotionPeriods = getMotionTimeHr(distanceKm) / _motionTimeBeforeRestHr;
    // если пришли на финиш в точности, когда надо отдыхать, то считаем, что отдых уже не нужен
    return numberOfMotionPeriods < 1 ? 0 : static_cast<int>(std::ceil(numberOfMotionPeriods) - 1);
}

double GroundVehicle::getRaceTimeHr(const int distanceKm) const
{
    return getMotionTimeHr(distanceKm) + getRestTimeHr(distanceKm);
}
