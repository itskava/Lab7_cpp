#include "Route.h"
#include <iostream>

Route::Route(
	int ticket_price,
	const std::string& departure_city,
	const std::string& arrival_city,
	const Timestamp& departure_time,
	const Timestamp& arrival_time)
	: ticket_price(ticket_price),
	departure_city(departure_city),
	arrival_city(arrival_city),
	departure_time(departure_time),
	arrival_time(arrival_time)
{}

Route::Route()
	: Route(0, "", "", Timestamp(), Timestamp()) 
{}

Route::Route(const Route& other) {
	this->ticket_price = other.ticket_price;
	this->departure_city = other.departure_city;
	this->arrival_city = other.arrival_city;
	this->departure_time = other.departure_time;
	this->arrival_time = other.arrival_time;
}

Route::~Route() = default;

// Статический метод, необходимый для создания экземпляра класса Route через консоль.
Route Route::createFromConsole() {
	int ticket_price;
	std::cout << "Введите цену билета: ";
	std::cin >> ticket_price;

	std::string departure_city, arrival_city;
	std::cout << "Введите город вылета: ";
	std::cin >> departure_city;

	std::cout << "Введите город посадки: ";
	std::cin >> arrival_city;

	std::cout << "Для вылета:\n";
	Timestamp departure_time = Timestamp::createFromConsole();
	 
	std::cout << "Для посадки:\n";
	Timestamp arrival_time = Timestamp::createFromConsole();

	return Route(ticket_price, departure_city, arrival_city, departure_time, arrival_time);
}

bool Route::operator==(const Route& other) const {
	return this->ticket_price == other.ticket_price &&
		this->departure_city == other.departure_city &&
		this->arrival_city == other.arrival_city &&
		this->departure_time == other.departure_time &&
		this->arrival_time == other.arrival_time;
}

bool Route::operator!=(const Route& other) const {
	return !(*this == other);
}

Route& Route::operator=(const Route& other) {
	if (this == &other) return *this;

	this->ticket_price = other.ticket_price;
	this->departure_city = other.departure_city;
	this->arrival_city = other.arrival_city;
	this->departure_time = other.departure_time;
	this->arrival_time = other.arrival_time;

	return *this;
}

std::ostream& operator<<(std::ostream& out, const Route& rt) {
	std::string output = "Маршрут: " + rt.departure_city + " - " + rt.arrival_city + "\n";

	return out << output << "Время взлёта: " << rt.departure_time << '\n' << "Время посадки: "
		<< rt.arrival_time << '\n' << "Цена билета: " << rt.ticket_price << std::endl;
}

