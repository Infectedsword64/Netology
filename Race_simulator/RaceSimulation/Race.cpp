#include "Race.h"
#include "Race.h"
#include "Race.h"
#include <stdexcept>

Race::Race(Vehicle** vehicles, const int count)
{
    _vehicles = vehicles;
    _vehicleCount = count;
    _vehicleAssignmentMap = new bool[count]();
}

Race::~Race()
{
    // Класс занимается освобождением только того, что сам создает
    delete[] _vehicleAssignmentMap;
}

RaceType Race::getRaceType() const
{
    return _type;
}

void Race::init(RaceType type, int distanceKm)
{
    _type = type;
    _distanceKm = distanceKm;
    _assignedVehicleCount = 0;
    for (int i = 0; i < _vehicleCount; ++i)
    {
        _vehicleAssignmentMap[i] = false;
    }
}

VehicleAssignmentResult Race::assignVehicle(const int index)
{
    if (index < 0 || index >= _vehicleCount)
    {
        throw std::out_of_range("Неверный индекс транспортного средства");
    }

    if (_vehicleAssignmentMap[index])
    {
        return ALREADY_ASSIGNED;
    }
    else
    {
        auto vehicleType = _vehicles[index]->getVehicleType();
        if (!isVehicleTypeAvailableToAssignment(vehicleType))
        {
            return INCOMPATIBLE_RACE_TYPE;
        }
    }

    _vehicleAssignmentMap[index] = true;
    ++_assignedVehicleCount;
    return SUCCESS;
}

VehicleAssignmentReport Race::createAssignmentReport() const
{
    VehicleAssignmentItem** items = new VehicleAssignmentItem*[_vehicleCount];
    for (int i = 0; i < _vehicleCount; i++)
    {
        const auto vehicle = _vehicles[i];
        const auto availableToAssignment = isVehicleTypeAvailableToAssignment(vehicle->getVehicleType());
        items[i] = new VehicleAssignmentItem(vehicle, _vehicleAssignmentMap[i], availableToAssignment);
    }

    // Уничтожением внутренних объектов будет заниматься сам отчет
    return VehicleAssignmentReport(items, _vehicleCount);
}

RaceResultReport Race::createRaceResultReport() const
{
    RaceResultItem** items = new RaceResultItem * [_assignedVehicleCount];
    int itemIndex = 0;
    for (int i = 0; i < _vehicleCount; ++i)
    {
        if (_vehicleAssignmentMap[i])
        {
            const auto vehicle = _vehicles[i];
            if (itemIndex >= _assignedVehicleCount)
            {
                throw std::logic_error("Некорректное состояние объекта Race");
            }

            items[itemIndex++] = new RaceResultItem(vehicle, vehicle->getRaceTimeHr(_distanceKm));
        }
    }

    // Уничтожением внутренних объектов будет заниматься сам отчет
    return RaceResultReport(items, _assignedVehicleCount);
}

Vehicle* const Race::getVehicle(int index) const
{
    return _vehicles[index];
}

int Race::getDistanceKm() const
{
    return _distanceKm;
}

bool Race::isVehicleTypeAvailableToAssignment(VehicleType vehicleType) const
{
    return (static_cast<int>(vehicleType) == static_cast<int>(_type) || _type == MIXED_RACE);
}
