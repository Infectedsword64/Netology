#include "FlyingCarpet.h"

FlyingCarpet::FlyingCarpet()
{
	_name = "Ковер-самолет";
	_velocityKmh = 10;
}

double FlyingCarpet::getDistanceReductionPercent(const int distanceKm) const
{
	if (distanceKm < 1000)
	{
		return 0.0;
	}

	if (distanceKm < 5000)
	{
		return 3.0;
	}

	if (distanceKm < 10000)
	{
		return 10.0;
	}

	return 5.0;
}
