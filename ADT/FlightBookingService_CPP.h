#pragma once

#include <iostream>
#include <string>
#include <vector>

// Класс, представляющий собой временную отметку.
// Хранит в себе часы, минуты, день и месяц.
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

// Класс, представляющий собой описание маршрута из одного города в другой;
// Содержит информацию о городах взлета и посадки, времени взлета и посадки, а также о цене билета.
class Route {
private:
	int ticket_price;
	std::string departure_city;
	std::string arrival_city;
	Timestamp departure_time;
	Timestamp arrival_time;

	friend class FlightBookingService;
public:
	Route(
		int ticket_price,
		const std::string& departure_city,
		const std::string& arrival_city,
		const Timestamp& departure_time,
		const Timestamp& arrival_time);

	Route();

	Route(const Route& other);
	
	~Route();

	static Route createFromConsole();

	void printRouteInfo() const;

	bool operator==(const Route& other) const;

	bool operator!=(const Route& other) const;

	Route& operator=(const Route& other);
	
};

// Класс, представляющий собой профиль пользователя;
// Содержит информацию об имени, почте, телефоне и возрасте, а также о купленном билете.
class Account {
private:
	std::string name;
	std::string email;
	std::string telephone;
	int age;
	int balance;
	Route* ticket;

	friend class FlightBookingService;
public:
	Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal);

	Account();

	Account(const Account& other);

	~Account();

	static Account createFromConsole();

	Account& operator=(const Account& other);
};

// Класс, представляющий собой сам сервис для покупки и продажи билетов для путешествий.
// Содержит в себе вектор, хранящий все доступные маршруты, и указатель на аккаунт пользователя.
class FlightBookingService {
private:
	std::vector<Route> routes;
	Account* account;
public:
	FlightBookingService(
		const std::string& name,
		const std::string& email,
		const std::string& telephone,
		int age,
		int balance);

	FlightBookingService();

	FlightBookingService(const Account& account);

	~FlightBookingService();

	static FlightBookingService createFromConsole();

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