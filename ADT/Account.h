#pragma once

#include "Route.h"
#include <string>
#include <list>

// Класс, представляющий собой профиль пользователя;
// Содержит информацию об имени, почте, телефоне и возрасте, а также о купленном билете.
class Account {
private:
	std::string name;
	std::string email;
	std::string telephone;
	int age;
	int balance;
	std::list<Route> tickets;

	friend class TravelService;

public:
	Account();

	Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal);

	Account(const Account& other);

	~Account();

	static Account createFromConsole();

	Account& operator=(const Account& other);
};