#include "Timestamp.h"
#include <string>
#include <chrono>
#include <sstream>

Timestamp::Timestamp() {
	std::array<int, 5> local_time = getLocalTime();
	this->day = local_time[0];
	this->month = local_time[1];
	this->year = local_time[2];
	this->hour = local_time[3];
	this->minute = local_time[4];
}

Timestamp::Timestamp(int day, int month, int year, int hour, int minute) {
	try {
		std::array<int, 5> local_time = getLocalTime();
		if (day < local_time[0] || month < local_time[1] || year < local_time[2] ||
			hour < local_time[3] || minute < local_time[4]) 
		{
			throw std::string("Invalid date input, this date is in the past.");
		}

		else {
			this->day = day;
			this->month = month;
			this->year = year;
			this->hour = hour;
			this->minute = minute;
			normalize();
		}
	}
	catch (const std::string& ex) {
		std::cerr << ex << std::endl;
	};
}

Timestamp::Timestamp(const Timestamp& other) {
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
	this->hour = other.hour;
	this->minute = other.minute;
}

Timestamp::~Timestamp() = default;

// Метод, возвращающий массив, представляющий собой текущее локальное время. 
std::array<int, 5> Timestamp::getLocalTime() const {
	std::array<int, 5> local_time{};


	std::time_t time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* local_tm = new std::tm();
	localtime_s(local_tm, &time_now);

	std::ostringstream oss;
	oss << std::put_time(local_tm, "%d %m %Y %H %M");
	delete local_tm;

	std::string buffer = oss.str();
	std::istringstream iss(buffer);

	std::size_t index = 0;

	while (iss >> buffer) {
		local_time[index++] = stoi(buffer);
	}
	
	return local_time;
}

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