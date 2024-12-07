#include "Presentation.h"
#include "AllTerrainBoots.h"
#include "Broomstick.h"
#include "Camel.h"
#include "Centaur.h"
#include "Eagle.h"
#include "FastCamel.h"
#include "FlyingCarpet.h"

int main()
{
	int applicationResult = 0;
	setlocale(LC_ALL, "Russian");
	Vehicle* vehicles[] = { new AllTerrainBoots(), new Broomstick(), new Camel(), new Centaur(), new Eagle(), new FastCamel(), new FlyingCarpet() };
	int vehicleCount = sizeof(vehicles) / sizeof(Vehicle*);

	try
	{
		Presentation::greet();
		Race race(vehicles, vehicleCount);
		bool initNewRace = false;

		do
		{
			RaceType raceType = Presentation::askRaceType();
			int distanceKm = Presentation::askDistanceKm();
			race.init(raceType, distanceKm);
			Presentation::clearScreen();
			Presentation::registerVehicles(race);
			auto raceReport = race.createRaceResultReport();
			Presentation::showRaceResults(race);
			initNewRace = Presentation::askNewRaceAction();
			if (initNewRace)
			{
				Presentation::clearScreen();
			}
		} while (initNewRace);
	}
	catch (std::exception& ex)
	{
		Presentation::showUnexpectedError(ex);
		applicationResult = 1;
	}

	for (int i = 0; i < vehicleCount; ++i)
	{
		delete vehicles[i];
	}

	return applicationResult;
}