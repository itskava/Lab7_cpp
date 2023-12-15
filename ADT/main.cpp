#pragma once

#include "TravelService.h"
#include <iostream>

class Base {
public:
	Base() = default;

	virtual ~Base() = default;
};

class Derived : public Base {
public:
	int field;

	Derived()
		: Base() 
	{
		field = 1;
	}

	~Derived() = default;
};

int main() {
	setlocale(LC_ALL, "ru");
	/*BaseAccount bs;
	PremiumAccount ps("kava kava kava", "kava@email.com", "+79293233802", 18);
	TravelService ts(ps);
	ts.displayAccountInfo();*/
	return 0;
}