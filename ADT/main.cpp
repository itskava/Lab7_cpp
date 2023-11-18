#pragma once

#include "TravelService.h"
#include <iostream>

int main(void) {
	setlocale(LC_ALL, "ru");
	
	// Статический метод Account::createFromConsole() указатель на экземпляр класса Account.
	TravelService* ts = TravelService::createFromConsole();

	Timestamp tmp1(18, 11, 2023, 6, 0);
	Timestamp tmp2(18, 11, 2023, 9, 0);

	// Демонстрация работы префиксного и постфиксного операторов инкремента.
	std::cout << std::endl;
	std::cout << tmp1++ << std::endl;
	std::cout << tmp1 << std::endl;
	std::cout << ++tmp2 << std::endl << std::endl;

	// Демонстрация работы оператора сложения.
	Timestamp tmp3 = tmp1 + tmp2;
	
	// Демонстрация возврата значения по ссылке (оператор присваивания).
	Timestamp tmp4;
	tmp4 = tmp3;

	Route rt(50000, "Barnaul", "Suzop", tmp1, tmp2 + 1);
	Route rt2(30000, "Barnaul", "Novosibirsk", tmp3, tmp4 + 3);
	ts->addRoute(rt);
	ts->addRoute(rt2);
	std::cout << std::endl;

	// Статический метод TravelService::printCompanyProfit() работает со статической переменной.
	TravelService::printCompanyProfit();
	ts->buyTicket(rt);
	TravelService::printCompanyProfit();
	ts->buyTicket(rt2);
	TravelService::printCompanyProfit();
	ts->sellTicket(2);
	TravelService::printCompanyProfit();
	
	delete ts;

	// Демонстрация работы с классом std::string.
	std::string demo = "some text";
	demo += " and another text"; // Конкатенация
	std::cout << demo << std::endl;

	std::string demo2 = demo.substr(0, 9); // Срез строки
	std::cout << demo2 << std::endl;
	demo2.erase(demo2.cbegin(), demo2.cbegin() + 2); // Удаление подстроки
	std::cout << demo2 << std::endl;
	std::cout << demo2.find("t") << ' ' << demo2.rfind("t") << std::endl; // Методы поиска подстрок
	std::cout << demo2.ends_with("text"); // Наличие подстроки в конце строки

	return 0;
}