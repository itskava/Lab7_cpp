#pragma once

// Класс, представляющий собой временную отметку.
// Хранит в себе часы, минуты, день и месяц.
class Timestamp {
private:
	int hour;
	int minute;
	int day;
	int month;

public:
	Timestamp(int hour, int minute, int day, int month);

	Timestamp();

	Timestamp(const Timestamp& other);

	~Timestamp();

	static Timestamp createFromConsole();

	void printTimestamp() const;

	bool operator!=(const Timestamp& other) const;

	bool operator==(const Timestamp& other) const;

	Timestamp& operator=(const Timestamp& other);
};