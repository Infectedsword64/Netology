#include "AirVehicle.h"

AirVehicle::AirVehicle()
{
	_type = AIR_VEHICLE;
}

double AirVehicle::getRaceTimeHr(const int distanceKm) const
{
	double effectiveDistanceKm = distanceKm * (1 - getDistanceReductionPercent(distanceKm) / 100);
	return effectiveDistanceKm / _velocityKmh;
}
