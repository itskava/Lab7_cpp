#pragma once

#include "Account.h"
#include <vector>

// Класс, представляющий собой сам сервис для покупки и продажи билетов для путешествий.
// Содержит в себе вектор, хранящий все доступные маршруты, и указатель на аккаунт пользователя.
class TravelService {
private:
	std::vector<Route> routes;
	Account* account;
	static long profit;

public:
	TravelService(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		int age);
	
	TravelService();

	TravelService(const Account& account);

	~TravelService();

	static TravelService createFromConsole();

	void displayAvailableRouts() const;

	void displayAccountInfo() const;

	void changeAccountData(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		short age);

	int getBalance() const;

	void topUpBalance(int amount);
	
	void addRoute(const Route& route);

	void removeRoute(std::size_t desired_ind);

	void searchTicketsByCity(const std::string& desired_city) const;

	void searchTicketsByPrice(int available_money) const;

	void buyTicket(const Route& route) const;

	void sellTicket(std::size_t desired_ind);

	void displayTicketsInfo() const;

	static void displayCompanyProfit();
};