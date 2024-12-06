#include "Presentation.h"

void Presentation::greet()
{
	std::cout << "Добро пожаловать в гоночный симулятор!" << std::endl;
}

void Presentation::showInvalidInputMessage()
{
	std::cout << "Введите корректное значение!" << std::endl;
}

std::string Presentation::getRaceTypeName(RaceType raceType)
{
	switch (raceType)
	{
	case GROUND_RACE:
		return std::string("Наземная гонка");
	case AIR_RACE:
		return std::string("Воздушная гонка");
	default:
		return std::string("Смешанная гонка");
	}
}

RaceType Presentation::askRaceType()
{
	std::cout << GROUND_RACE << ". " << getRaceTypeName(GROUND_RACE) << std::endl;
	std::cout << AIR_RACE << ". " << getRaceTypeName(AIR_RACE) << std::endl;
	std::cout << MIXED_RACE << ". " << getRaceTypeName(MIXED_RACE) << std::endl;
	int input = 0;
	bool isInputValid = false;
	do
	{
		std::cout << "Выберите тип гонки: ";
		std::cin >> input;
		if (input != static_cast<int>(GROUND_RACE) &&
			input != static_cast<int>(AIR_RACE) &&
			input != static_cast<int>(MIXED_RACE))
		{
			isInputValid = true;
			showInvalidInputMessage();
		}
	} while (isInputValid);

	return static_cast<RaceType>(input);
}

int Presentation::askDistanceKm()
{
	int input = 0;
	do
	{
		std::cout << "Укажите длину дистанции, км: ";
		std::cin >> input;
		if (input <= 0)
		{
			input = 0;
			showInvalidInputMessage();
		}
	} while (input == 0);

	return input;
}

void Presentation::showRaceSummary(Race& race)
{
	std::cout << getRaceTypeName(race.getRaceType()) << ". Расстояние: " << race.getDistanceKm() << " км." << std::endl;
}

void Presentation::showRegisteredVehicles(VehicleAssignmentReport& assignmentReport)
{
	int assignedCount = assignmentReport.getAssignedCount();
	std::string vnames;

	if (assignedCount < 2)
	{
		std::cout << "Должно быть зарегистрировано хотя бы " << assignmentReport.MIN_VEHICLE_NUMBER << " транспортных средства." << std::endl;
	}

	if (assignedCount > 0)
	{
		std::cout << "Зарегистрированные транспортные средства: ";
		bool hasAssignedShown = false;
		for (int i = 0; i < assignmentReport.getCount(); ++i)
		{
			if (assignmentReport[i]->getAssigned())
			{
				if (hasAssignedShown)
				{
					std::cout << ", ";
				}

				std::cout << assignmentReport[i]->getVehicle()->getName();
				hasAssignedShown = true;
			}
		}

		std::cout << vnames << std::endl;
	}

	for (int i = 0; i < assignmentReport.getCount(); ++i)
	{
		// При желании как-то по-разному можно показать недоступные ТС
		std::cout << (i + 1) << ". " << assignmentReport[i]->getVehicle()->getName() << std::endl;
	}

	if (assignmentReport.isReadyToRace())
	{
		std::cout << "0. Закончить регистрацию" << std::endl;
	}
}

int Presentation::askRegistrationAction(Race& race)
{
	showRaceSummary(race);
	auto assignmentReport = race.createAssignmentReport();
	showRegisteredVehicles(assignmentReport);
	int input = 0;
	bool isInputValid = false;
	do
	{
		std::cout << "Выберите действие: ";
		std::cin >> input;
		isInputValid = input > 0 && input <= assignmentReport.getCount() || input == 0 && assignmentReport.isReadyToRace();
		if (!isInputValid)
		{
			showInvalidInputMessage();
		}
	} while (!isInputValid);

	return input;
}

void Presentation::registerVehicles(Race& race)
{
	bool registrationComplete = false;
	do
	{
		int input = Presentation::askRegistrationAction(race);
		registrationComplete = input == 0;
		if (!registrationComplete)
		{
			Presentation::assignVehicle(race, input - 1);
		}
	} while (!registrationComplete);
}

void Presentation::assignVehicle(Race& race, int index)
{
	clearScreen();
	auto assignmentResult = race.assignVehicle(index);
	auto vehicleName = race.getVehicle(index)->getName();
	switch (assignmentResult)
	{
	case ALREADY_ASSIGNED:
		std::cout << "Транспортное средстро '" + vehicleName << "' уже зарегистрировано на гонку." << std::endl;
		break;
	case INCOMPATIBLE_RACE_TYPE:
		std::cout << "Транспортное средстро '" + vehicleName << "' не подходит по типу." << std::endl;
		break;
	default:
		std::cout << "Транспортное средстро '" + vehicleName << "' успешно зарегистрировано!" << std::endl;
	}
}

void Presentation::showRaceResults(Race& race)
{
	RaceResultReport resultsReport = race.createRaceResultReport();
	std::cout << std::endl;
	std::cout << "Результаты гонки:" << std::endl;
	for (int i = 0; i < resultsReport.getCount(); ++i)
	{
		auto item = resultsReport[i];
		std::cout << (i + 1) << ". " << item->getVehicle()->getName() << " Время: " << item->getRaceTimeHr() << " ч." << std::endl;
	}
}

bool Presentation::askNewRaceAction()
{
	int input = 0;
	bool isInputValid = false;
	do
	{
		std::cout << std::endl;
		std::cout << "1. Провести еще одну гонку" << std::endl;
		std::cout << "2. Выйти" << std::endl;
		std::cout << "Выберите действие: ";
		std::cin >> input;

		isInputValid = input == 1 || input == 2;
		if (!isInputValid)
		{
			showInvalidInputMessage();
		}
	} while (!isInputValid);

	return input != 2;
}

void Presentation::clearScreen()
{
	std::system("cls");
}

void Presentation::showUnexpectedError(std::exception ex)
{
	std::cout << "Непредвиденная ошибка в программе: " << ex.what() << std::endl;
	std::cout << "Программа будет завершена" << std::endl;
}
