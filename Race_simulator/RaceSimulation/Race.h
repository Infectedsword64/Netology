#pragma once
#include "Vehicle.h"
#include "RaceType.h"
#include "VehicleAssignmentResult.h"
#include "RaceResultReport.h"
#include "VehicleAssignmentReport.h"
#include "RaceSimulationExports.h"

class RACESIMULATION_API Race
{
    public:
        Race(Vehicle** vehicles, const int count);

        virtual ~Race();

        // Возвращает тип гонки
        RaceType getRaceType() const;

        // инициализирует новую гонку.
        void init(RaceType type, int distanceKm);

        // Добавляет ТС для участия в гонке по индексу.
        VehicleAssignmentResult assignVehicle(const int index);

        // Возвращает отчет по ТС, выбранных для гонки. Включает весь список ТС.
        VehicleAssignmentReport createAssignmentReport() const;

        // Создает результат гонки
        RaceResultReport createRaceResultReport() const;

        Vehicle* const getVehicle(int index) const;

        int getDistanceKm() const;

    private:
        RaceType _type = GROUND_RACE;
        int _distanceKm = 0;
        int _vehicleCount = 0;
        int _assignedVehicleCount = 0;
        Vehicle** _vehicles;
        bool* _vehicleAssignmentMap;
        bool isVehicleTypeAvailableToAssignment(VehicleType vehicleType) const;
};
