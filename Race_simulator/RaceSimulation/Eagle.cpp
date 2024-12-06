#include "Eagle.h"

Eagle::Eagle()
{
	_name = "Орел";
	_velocityKmh = 8;
}

double Eagle::getDistanceReductionPercent(const int distanceKm) const
{
	return 6.0;
}