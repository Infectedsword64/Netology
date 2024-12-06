#pragma once
#include "RaceResultItem.h"
#include "RaceSimulationExports.h"

class RaceResultReport
{
	friend class Race;
	public:
		RACESIMULATION_API ~RaceResultReport();
		RACESIMULATION_API RaceResultItem* const * const getItems() const;
		RACESIMULATION_API int getCount() const;
		RACESIMULATION_API RaceResultItem* const operator [](const int i) const;
	protected:
		// конструктор незачем экспортировать пользователям, т.к. они не создают.
		RaceResultReport(RaceResultItem** items, int count);
	private:
		RaceResultItem** _items;
		int _count;
		// упорядочивает элементы
		void orderItems();
		// Функция сравнения элементов отчета, используемая для упорядочивания
		int compareItems(RaceResultItem* item1, RaceResultItem* item2) const;
};
