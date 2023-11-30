#pragma once

#include "Route.h"
#include <string>
#include <vector>

// Класс, представляющий собой профиль пользователя;
// Содержит информацию об имени, почте, телефоне, возрасте и балансе пользователя, а также о купленных билетах.
class Account {
private:
	std::string name;
	std::string email;
	std::string telephone;
	short age;
	unsigned int balance;
	std::vector<Route> tickets;

	void setDefaultValues();

	void checkAccountDataCorrectness(const std::string& name, const std::string& email, const std::string& telephone, short age) const;

	bool checkEmailCorrectness(const std::string& email) const;

	bool isInitialized() const;
	
	friend class TravelService;

public:
	Account();

	Account(const std::string& name, const std::string& email, const std::string& telephone, int age);

	Account(const Account& other) = delete;

	~Account();

	static Account createFromConsole();

	Account& operator=(const Account& other) = delete;
};