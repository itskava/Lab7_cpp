#include "Timestamp.h"
#include <string>

Timestamp::Timestamp()
	: Timestamp(1, 1, 1970, 0, 0)
{}

Timestamp::Timestamp(int day, int month, int year, int hour, int minute)
	: day(day), month(month), year(year), hour(hour), minute(minute)
{
	normalize();
}

Timestamp::Timestamp(const Timestamp& other) {
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
	this->hour = other.hour;
	this->minute = other.minute;
}

Timestamp::~Timestamp() = default;

// Статический метод, необходимый для создания экземпляра класса Timestamp через консоль.
Timestamp Timestamp::createFromConsole() {
	int day, month, year, hour, minute;
	std::cout << "Введите день, месяц, год, часы и минуты временной отметки через пробел (dd.MM.yyyy hh:mm): ";
	std::cin >> day >> month >> year >> hour >> minute;
	
	return Timestamp(day, month, year, hour, minute);
}

// Служебный метод для определения високосного года.
bool Timestamp::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Служебный метод, возвращающий количество дней в месяце.
int Timestamp::getDaysInMonth(int month, int year) const {
	if (month == 2) return isLeapYear(year) + 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	else return 31;
}

// Служебный метод, "нормализующий" временную метку - недопустимые значения корректируются в допустимые.
void Timestamp::normalize() {
	while (minute >= 60) {
		minute -= 60;
		hour++;
	}

	while (hour >= 24) {
		hour -= 24;
		day++;
	}

	while (day > getDaysInMonth(month, year)) {
		day -= getDaysInMonth(month, year);
		if (++month > 12) {
			month = 1;
			year++;
		}
	}
}

bool Timestamp::operator==(const Timestamp& other) const {
	return this->day == other.day && 
		this->month == other.month && 
		this->year == other.year &&
		this->hour == other.hour && 
		this->minute == other.minute;
}

bool Timestamp::operator!=(const Timestamp& other) const {
	return !(*this == other);
}


Timestamp& Timestamp::operator=(const Timestamp& other) {
	if (this == &other) return *this;

	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
	this->hour = other.hour;
	this->minute = other.minute;
	
	return *this;
}

Timestamp operator+(const Timestamp& lhs, const Timestamp& rhs) {
	Timestamp result = lhs;
	result.minute += rhs.minute;
	result.hour += rhs.hour;
	result.normalize();
	return result;
}

Timestamp operator+(const Timestamp& timestamp, int val) {
	Timestamp result = timestamp;
	result.hour += val;
	result.normalize();
	return result;
}

Timestamp& Timestamp::operator++() {
	hour++;
	normalize();
	return *this;
}

Timestamp Timestamp::operator++(int) {
	Timestamp copy = *this;
	++(*this);
	normalize();
	return copy;
}

std::ostream& operator<<(std::ostream& out, const Timestamp& tm) {
	std::string output;
	if (tm.day < 10) output += '0';
	output += std::to_string(tm.day) + "/";
	if (tm.month < 10) output += '0';
	output += std::to_string(tm.month) + "/";
	output += std::to_string(tm.year) + " ";
	if (tm.hour < 10) output += '0';
	output += std::to_string(tm.hour) + ":";
	if (tm.minute < 10) output += '0';
	output += std::to_string(tm.minute);
	return out << output;
}