#include "RaceResultReport.h"
#include "RaceResultReport.h"
#include "RaceResultReport.h"
#include "RaceResultReport.h"

RaceResultReport::RaceResultReport(RaceResultItem** items, int count)
{
	_items = items;
	_count = count;
    orderItems();
}

RaceResultReport::~RaceResultReport()
{
    // Не совсем понятно, как понять, должен ли объект освобождать объекты, которые не он выделял.
    // В данном случае мне это нужно. По-видимому, должны быть какие-то соглашения.
	for (int i = 0; i < _count; ++i)
	{
		delete _items[i];
	}

	delete[] _items;
}

RACESIMULATION_API RaceResultItem* const* const RaceResultReport::getItems() const
{
	return _items;
}

int RaceResultReport::getCount() const
{
	return _count;
}

RaceResultItem* const RaceResultReport::operator[](const int i) const
{
    return _items[i];
}

void RaceResultReport::orderItems()
{
    // взял обратный пузырек из одного из прошлых заданий
    bool swapped;
    do {
        swapped = false;
        for (int i = _count - 1; i > 0; --i) {
            if (compareItems(_items[i], _items[i - 1]) < 0) {
                swapped = true;
                RaceResultItem* tmp = _items[i];
                _items[i] = _items[i - 1];
                _items[i - 1] = tmp;
            }
        }
    } while (swapped);
}

int RaceResultReport::compareItems(RaceResultItem* item1, RaceResultItem* item2) const
{
    auto raceTime1 = item1->getRaceTimeHr();
    auto raceTime2 = item2->getRaceTimeHr();
    return raceTime1 > raceTime2 ? 1
        : (raceTime1 < raceTime2 ? -1 : 0);
}
