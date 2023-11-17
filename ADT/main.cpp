#pragma once

#include "TravelService.h"
#include <iostream>

int main(void) {
	setlocale(LC_ALL, "ru");
	
	Account* account = new Account("Artem Zinov", "pter@gmail.com", "14608810", 19, 100000);
	TravelService ts(account);
	Route rt(50000, "Barnaul", "Suzop", Timestamp(18, 11, 2023, 6, 0), Timestamp(18, 11, 2023, 9, 0));
	ts.addRoute(rt);

	ts.printCompanyProfit();
	ts.buyTicket(rt);
	ts.printCompanyProfit();
}