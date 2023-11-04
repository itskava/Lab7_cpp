#pragma once

//  ласс, представл€ющий собой временную отметку.
// ’ранит в себе часы, минуты, день и мес€ц.
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