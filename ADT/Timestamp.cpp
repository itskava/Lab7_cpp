#include "Timestamp.h"
#include <iostream>

Timestamp::Timestamp()
	: Timestamp(0, 0, 0, 0)
{}

Timestamp::Timestamp(int hour, int minute, int day, int month)
	: hour(hour), minute(minute), day(day), month(month) 
{}

Timestamp::Timestamp(const Timestamp& other) {
	this->hour = other.hour;
	this->minute = other.minute;
	this->day = other.day;
	this->month = other.month;
}

Timestamp::~Timestamp() = default;

// —татический метод, необходимый дл€ создани€ экземпл€ра класса Timestamp через консоль.
Timestamp Timestamp::createFromConsole() {
	int hour, minute, day, month;
	std::cout << "¬ведите часы, минуты, день и мес€ц временной отметки через пробел (HH mm dd MM): ";
	std::cin >> hour >> minute >> day >> month;

	return Timestamp(hour, minute, day, month);
}

// ћетод, распечатывающий информацию о данной временной метке.
void Timestamp::printTimestamp() const {
	if (hour < 10) std::cout << '0';
	std::cout << hour << ':';
	if (minute < 10) std::cout << '0';
	std::cout << minute << ", ";
	if (day < 10) std::cout << '0';
	std::cout << day << '.';
	if (month < 10) std::cout << '0';
	std::cout << month << '\n';
}

bool Timestamp::operator==(const Timestamp& other) const {
	return this->day == other.day && this->month == other.month &&
		this->hour == other.hour && this->minute == other.minute;
}

bool Timestamp::operator!=(const Timestamp& other) const {
	return !(*this == other);
}


Timestamp& Timestamp::operator=(const Timestamp& other) {
	if (this == &other) return *this;

	this->hour = other.hour;
	this->minute = other.minute;
	this->day = other.day;
	this->month = other.month;

	return *this;
}