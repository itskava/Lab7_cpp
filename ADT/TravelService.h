#pragma once

#include "Account.h"
#include <vector>

// Класс, представляющий собой сам сервис для покупки и продажи билетов для путешествий.
// Содержит в себе вектор, хранящий все доступные маршруты, и указатель на аккаунт пользователя.
class TravelService {
private:
	std::vector<Route> routes;
	Account* account;
public:
	TravelService(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		int age,
		int balance);

	TravelService();

	TravelService(const Account& account);

	~TravelService();

	static TravelService createFromConsole();

	void printAvailableRouts() const;

	void printAccountInfo() const;

	void changeAccountInfo(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		int age);

	int getBalance() const;

	void topUpBalance(int amount);
	
	void addRoute(const Route& route);

	void removeRoute(const Route& route);

	void searchTicketsByCity(const std::string& desired_city) const;

	void searchTicketsByPrice(int available_money) const;

	void buyTicket(const Route& route) const;

	void sellTicket();

	void printTicketInfo() const;
};