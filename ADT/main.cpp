#pragma once

#include "TravelService.h"
#include "AdditionalRouteInfo.h"
#include <iostream>

int main() {
	setlocale(LC_ALL, "ru");
	BaseAccount base_acc("Nill Viktorovich Kiggers", "some@inbox.com", "+12345678901", 25);
	TravelService ts(base_acc);
	Route rt1(1000, "a", "b", Timestamp(), Timestamp());
	Route rt2(2000, "c", "d", Timestamp(), Timestamp());
	Route rt3(3000, "e", "f", Timestamp(), Timestamp());
	ts.addRoute(rt3);
	ts.addRoute(rt2);
	ts.addRoute(rt1);

	ts.displayAvailableRouts();
	ts.sortTicketsByPrice(); // Сортировка с помощью std::sort()
	ts.displayAvailableRouts();

	BaseAccount* acc = new BaseAccount();
	PremiumAccount* acc2 = new PremiumAccount();
	Account* acc3 = new BaseAccount();
	std::vector<Account*> container_demo = { acc, acc2, acc3 }; // Вектор, хранящий указатели на базовый и производный классы

	delete acc;
	delete acc2;
	delete acc3;
	return 0;
}