#pragma once
#include <iostream>
#include "RaceType.h"
#include "Race.h"

namespace Presentation
{
	// Приветствует пользователя
	void greet();

	/// Выводит сообщение об ошибке
	void showInvalidInputMessage();

	// Возврашает имя типа гонки
	std::string getRaceTypeName(RaceType raceType);

	// Запрашивает у пользователя тип гонки
	RaceType askRaceType();

	// Запрашивает дистанцию
	int askDistanceKm();

	// Выводит информацию предстоящей по гонке
	void showRaceSummary(Race& race);

	// Выводит ТС, зарегистрированные на гонку
	void showRegisteredVehicles(VehicleAssignmentReport& assignmentReport);

	// Запрашивает у пользователя и регистриует ТС на гонку
	void registerVehicles(Race& race);

	// Обеспечивает диалог с пользователем по регистрации одного ТС 
	int askRegistrationAction(Race& race);

	// Назначает ТС на гонку
	void assignVehicle(Race& race, int index);

	// Выводит результаты гонки
	void showRaceResults(Race& race);

	// Запрашивает пользователя, проводить ли еще одну гонку
	bool askNewRaceAction();

	// Очищает экран
	void clearScreen();

	// Выводит сообщение о непредвиденной ошибке
	void showUnexpectedError(std::exception ex);
}
