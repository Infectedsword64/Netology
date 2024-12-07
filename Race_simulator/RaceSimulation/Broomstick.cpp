#include "Broomstick.h"

Broomstick::Broomstick()
{
	_name = "Метла";
	_velocityKmh = 20;
}

double Broomstick::getDistanceReductionPercent(const int distanceKm) const
{
	int percent = distanceKm / 1000;
	if (percent > 100)
	{
		percent = 100;
	}

	return percent;
}