#pragma once

#include "Timestamp.h"
#include <string>
#include <memory>

// Концепт, проверяющий входной тип на то, что его возможно вывести в std::ostream.
template <typename T>
concept HasOutput = requires(std::ostream & out, T t) {
	{ out << t } -> std::same_as<std::ostream&>;
};

// Класс, представляющий собой описание маршрута из одного города в другой;
// Содержит информацию о городах взлета и посадки, времени взлета и посадки, а также о цене билета.
template <HasOutput T = std::string>
class Route {
private:
	unsigned int ticket_price;
	std::string departure_city;
	std::string arrival_city;
	Timestamp departure_time;
	Timestamp arrival_time;
	std::unique_ptr<T> additional_info;
	bool has_additional_info;

	friend class TravelService;
public:
	Route(
		unsigned int ticket_price,
		const std::string& departure_city,
		const std::string& arrival_city,
		const Timestamp& departure_time,
		const Timestamp& arrival_time,
		std::unique_ptr<T> additional_info = nullptr);

	Route();

	Route(const Route<T>& other);

	~Route();

	static Route<T> createFromConsole();

	void updateAdditionalInfo(const std::unique_ptr<T> additional_info);

	void displayAdditionalInfo() const;

	bool operator<(const Route<T>& other) const;

	bool operator==(const Route<T>& other) const;

	bool operator!=(const Route<T>& other) const;

	Route<T>& operator=(const Route<T>& other);

	template <HasOutput T>
	friend inline std::ostream& operator<<(std::ostream& out, const Route<T>& rt);
};

// Реализация каждого метода перенесена в заголовочный файл из-за того, что компоновщик не знает о шаблонах
// в исполняемых файлах
template <HasOutput T>
Route<T>::Route(
	unsigned int ticket_price,
	const std::string& departure_city,
	const std::string& arrival_city,
	const Timestamp& departure_time,
	const Timestamp& arrival_time,
	std::unique_ptr<T> additional_info)
	: ticket_price(ticket_price),
	departure_city(departure_city),
	arrival_city(arrival_city),
	departure_time(departure_time),
	arrival_time(arrival_time),
	additional_info(std::move(additional_info))
{
	if (static_cast<bool>(this->additional_info)) {
		has_additional_info = true;
	}
	else {
		has_additional_info = false;
		this->additional_info = std::make_unique<T>();
	}
}

template <HasOutput T>
Route<T>::Route()
	: Route(0, "", "", Timestamp(), Timestamp())
{
	has_additional_info = false;
}


template <HasOutput T>
Route<T>::Route(const Route<T>& other) {
	this->ticket_price = other.ticket_price;
	this->departure_city = other.departure_city;
	this->arrival_city = other.arrival_city;
	this->departure_time = other.departure_time;
	this->arrival_time = other.arrival_time;
	this->additional_info = std::make_unique<T>(*other.additional_info);
	this->has_additional_info = other.has_additional_info;
}

template <HasOutput T>
Route<T>::~Route() = default;

// Статический метод, необходимый для создания экземпляра класса Route через консоль.
template <HasOutput T>
Route<T> Route<T>::createFromConsole() {
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

// Метод, предназначенный для добавления дополнительной информации о маршруте.
template <HasOutput T>
void Route<T>::updateAdditionalInfo(const std::unique_ptr<T> additional_info) {
	if (static_cast<bool>(additional_info)) {
		this->additional_info = std::make_unique<T>(*additional_info);
		has_additional_info = true;
	}
}

// Метод, предназначенный для вывода дополнительной информации о маршруте.
template <HasOutput T>
void Route<T>::displayAdditionalInfo() const {
	if (has_additional_info) {
		std::cout << *additional_info << std::endl;
	}
	else {
		std::cout << "Для данного маршрута нет дополнительной информации." << std::endl;
	}
}

template<HasOutput T>
bool Route<T>::operator<(const Route<T>& other) const {
	return this->ticket_price < other.ticket_price;
}

template <HasOutput T> 
bool Route<T>::operator==(const Route<T>& other) const {
	return this->ticket_price == other.ticket_price &&
		this->departure_city == other.departure_city &&
		this->arrival_city == other.arrival_city &&
		this->departure_time == other.departure_time &&
		this->arrival_time == other.arrival_time;
}

template <HasOutput T>
bool Route<T>::operator!=(const Route<T>& other) const {
	return !(*this == other);
}

template <HasOutput T>
Route<T>& Route<T>::operator=(const Route<T>& other) {
	if (this != &other) {
		this->ticket_price = other.ticket_price;
		this->departure_city = other.departure_city;
		this->arrival_city = other.arrival_city;
		this->departure_time = other.departure_time;
		this->arrival_time = other.arrival_time;
		this->additional_info = std::make_unique<T>(*other.additional_info);
	}

	return *this;
}

	template <HasOutput T>
	std::ostream& operator<<(std::ostream& out, const Route<T>& rt) {
		return out << "Маршрут: " << rt.departure_city << " - " << rt.arrival_city 
			<< "\n" << "Время взлёта: " << rt.departure_time << '\n' << "Время посадки: "
			<< rt.arrival_time << '\n' << "Цена билета: " << rt.ticket_price << std::endl;
	}

