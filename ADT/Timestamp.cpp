#include "Timestamp.h"
#include <string>
#include <chrono>
#include <sstream>

Timestamp::Timestamp() {
	setDefault();
}

Timestamp::Timestamp(int day, int month, int year, int hour, int minute) {
	try {
		if (checkDateCorrectness(day, month, year, hour, minute)) {
			this->day = day;
			this->month = month;
			this->year = year;
			this->hour = hour;
			this->minute = minute;
			normalize();
		}
		else {
			throw std::string("Неверный ввод, введенная дата находится в прошлом.");
		}
	}
	catch (const std::string& ex) {
		setDefault();
		std::cerr << ex << std::endl;
		std::cerr << "Установлены значения по умолчанию." << std::endl;
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

// Статический метод, предназначенный для создания экземпляра через консоль.
Timestamp Timestamp::createFromConsole() {
	int day, month, year, hour, minute;
	std::cout << "Введите временную метку (dd MM yyyy hh mm): ";
	std::cin >> day >> month >> year >> hour >> minute;

	return Timestamp(day, month, year, hour, minute);
}

// Метод, предназначенный для установки значений по умолчанию для временной метки.
void Timestamp::setDefault() {
	day = 1;
	month = 1;
	year = 1970;
	hour = 0;
	minute = 0;
}

// Метод, предназначенный для проверки действительности временной метки.
bool Timestamp::checkDateCorrectness(int day, int month, int year, int hour, int minute) const {
	std::array<int, 5> local_time = getLocalTime();
	bool date_correctness = false;

	if (year > local_time[2]) date_correctness = true;
	else if (year == local_time[2]) {
		if (month > local_time[1]) date_correctness = true;
		else if (month == local_time[1]) {
			if (day > local_time[0]) date_correctness = true;
			else if (day == local_time[0]) {
				if (hour > local_time[3]) date_correctness = true;
				else if (hour == local_time[3] && minute >= local_time[4]) date_correctness = true;
			}
		}
	}

	return date_correctness;
}

// Метод, предназначенный для изменения данных временной метки.
void Timestamp::changeData(int day, int month, int year, int hour, int minute) {
	if (checkDateCorrectness(day, month, year, hour, minute)) {
		this->day = day;
		this->month = month;
		this->year = year;
		this->hour = hour;
		this->minute = minute;
		normalize();

		std::cout << "Данные временной метки успешно изменены." << std::endl;
	}
	else {
		std::cout << "Неверный ввод, введенная дата находится в прошлом." << std::endl;
	}
}

// Метод, предназначенный для определения того, является ли метка меткой по умолчанию.
bool Timestamp::isDefault() const {
	return day == 1 && month == 1 && year == 1970 && minute == 0 && hour == 0;
}

// Служебный метод, который проверяет, является ли год високосным.
bool Timestamp::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Служебный метод, возвращающий количество дней в выбранном месяце.
int Timestamp::getDaysInMonth(int month, int year) const {
	if (month == 2) return isLeapYear(year) + 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
	else return 31;
}

// Служебный метод, предназначенный для "нормализации" временной метки.
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