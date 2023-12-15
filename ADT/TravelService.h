#pragma once

#include "BaseAccount.h"
#include "PremiumAccount.h"
#include <vector>
#include <type_traits>
#include <typeinfo>

template<class T>
concept IsAccount = std::same_as<T, BaseAccount> || std::same_as<T, PremiumAccount>;

// Класс, представляющий собой сам сервис для покупки и продажи билетов для путешествий.
// Содержит в себе вектор, хранящий все доступные маршруты, и указатель на аккаунт пользователя.
class TravelService {
private:
	std::vector<Route> routes;
	Account* account;
	static bool is_premium;
	static long profit;

public:
	TravelService(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		int age);
	
	TravelService();

	template<IsAccount T>
	TravelService(const T& account) {
		if constexpr (std::same_as<T, BaseAccount>) {
			this->account = new BaseAccount(account);
		}
		else if constexpr (std::same_as<T, PremiumAccount>) {
			this->account = new PremiumAccount(account);
		}
	}

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

	void topUpBalance(unsigned int amount);
	
	void addRoute(const Route& route);

	void removeRoute(std::size_t desired_ind);

	void searchTicketsByCity(const std::string& desired_city) const;

	void searchTicketsByPrice(unsigned int available_money) const;

	void buyTicket(const Route& route) const;

	void sellTicket(std::size_t desired_ind);

	void displayTicketsInfo() const;

	static void displayCompanyProfit();

	void upgradeToPremium();
};