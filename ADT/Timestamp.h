#pragma once

#include <iostream>
#include <array>

// Класс, представляющий собой временную отметку.
// Хранит в себе часы, минуты, день и месяц.
class Timestamp {
private:
	int day;
	int month;
	int year;
	int hour;
	int minute;

	bool isLeapYear(int year) const;
	int getDaysInMonth(int month, int year) const;
	void normalize();
	std::array<int, 5> getLocalTime() const;
	void setDefault();
	bool checkDateCorrectness(int day, int month, int year, int hour, int minute) const;

public:
	Timestamp();

	Timestamp(int day, int month, int year, int hour, int minute);

	Timestamp(const Timestamp& other);

	~Timestamp();

	static Timestamp createFromConsole();

	void changeData(int day, int month, int year, int hour, int minute);

	bool isDefault() const;

	bool operator==(const Timestamp& other) const;

	bool operator!=(const Timestamp& other) const;

	Timestamp& operator=(const Timestamp& other);

	Timestamp& operator++();

	Timestamp operator++(int);

	friend std::ostream& operator<<(std::ostream& out, const Timestamp& tm);

	friend Timestamp operator+(const Timestamp& lhs, const Timestamp& rhs);

	friend Timestamp operator+(const Timestamp& timestamp, int val);
};