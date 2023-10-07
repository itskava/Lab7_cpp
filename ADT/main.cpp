#include "FlightBookingService_CPP.h"


Timestamp::Timestamp(int hour, int minute, int day, int month)
		: hour(hour), minute(minute), day(day), month(month) {}
	
Timestamp::Timestamp() : Timestamp(0, 0, 0, 0) {}
	
Timestamp::Timestamp(const Timestamp& other) {
		this->hour = other.hour;
		this->minute = other.minute;
		this->day = other.day;
		this->month = other.month;
	}
	
Timestamp::~Timestamp() = default;

// Статический метод, необходимый для создания экземпляра класса Timestamp через консоль.
Timestamp Timestamp::createFromConsole() {
	int hour, minute, day, month;
	std::cout << "Введите часы, минуты, день и месяц временной отметки через пробел (HH mm dd MM): ";
	std::cin >> hour >> minute >> day >> month;

	return Timestamp(hour, minute, day, month);
}

// Метод, распечатывающий информацию о данной временной метке.
void Timestamp::printTimestamp() const {
	if (hour < 10) std::cout << '0';
	std::cout << hour << ':';
	if (minute < 10) std::cout << '0';
	std::cout << minute << ", ";
	if (day < 10) std::cout << '0';
	std::cout << day << '.';
	if (month < 10) std::cout << '0';
	std::cout << month << '\n';
}

bool Timestamp::operator!=(const Timestamp& other) const {
	if (this->day != other.day || this->month != other.month ||
		this->hour != other.hour || this->minute != other.minute) 
	{
		return true;
	}
	return false;
}

bool Timestamp::operator==(const Timestamp& other) const {
	return !(*this != other);
}

Timestamp& Timestamp::operator=(const Timestamp& other) {
	if (this == &other) return *this;

	this->hour = other.hour;
	this->minute = other.minute;
	this->day = other.day;
	this->month = other.month;

	return *this;
}

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

Route::Route() : Route(0, "", "", Timestamp(), Timestamp()) {}

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

// Метод, который распечатывает полную информацию о данном маршруте.
void Route::printRouteInfo() const {
	std::cout << "Маршрут: " << departure_city << " - " << arrival_city << '\n';
	std::cout << "Время взлёта: ";
	departure_time.printTimestamp();
	std::cout << "Время посадки: ";
	arrival_time.printTimestamp();
	std::cout << "Цена билета: " << ticket_price << "\n\n";
}

bool Route::operator==(const Route& other) const {
	if (this->ticket_price != other.ticket_price ||
		this->departure_city != other.departure_city ||
		this->arrival_city != other.arrival_city ||
		this->departure_time != other.departure_time ||
		this->arrival_time != other.arrival_time) 
	{
		return false;
	}
	return true;
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


Account::Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal)
	: name(name), email(email), telephone(tel), age(age), balance(bal), ticket(nullptr) 
{}

Account::Account() : name(""), email(""), telephone(""), age(0), balance(0), ticket(nullptr) {}

Account::Account(const Account& other) {
	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = other.balance;

	if (other.ticket) *this->ticket = *other.ticket;
	else this->ticket = nullptr;
}

Account::~Account() {
	if (ticket) delete ticket;
}

// Статический метод, необходимый для создания экземпляра класса Account через консоль.
Account Account::createFromConsole() {
	std::string name, email, telephone;
	int age, balance;
	std::cout << "Введите Ваше ФИО: ";
	std::getline(std::cin, name);

	std::cout << "Введите Вашу почту: ";
	std::getline(std::cin, email);

	std::cout << "Введите Ваш телефон: ";
	std::getline(std::cin, telephone);

	std::cout << "Введите Ваш возраст: ";
	std::cin >> age;

	std::cout << "Введите сумму, на которую будет сразу пополнен Ваш счёт: ";
	std::cin >> balance;

	return Account(name, email, telephone, age, balance);
}

Account& Account::operator=(const Account& other) {
	if (this == &other) return *this;

	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = other.balance;

	return *this;
}

FlightBookingService::FlightBookingService(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	int age,
	int balance)
{
	account = new Account(name, email, telephone, age, balance);
}

FlightBookingService::FlightBookingService() {
	account = new Account("", "", "", 0, 0);
}

FlightBookingService::FlightBookingService(const Account& account) {
	this->account = new Account();
	*this->account = account;
}

FlightBookingService::~FlightBookingService() {
	delete account;
}

// Статический метод, необходимый для создания экземпляра класса FlightBookingService через консоль.
FlightBookingService FlightBookingService::createFromConsole() {
	return FlightBookingService(Account::createFromConsole());
}
	
// Метод, распечатывающий информации обо всех существующих маршрутах.
void FlightBookingService::printAvailableRouts() const {
	if (!routes.empty()) {
		std::cout << "Доступные маршруты:\n\n";
		std::size_t index = 1;

		for (const auto& route : routes) {
			std::cout << index++ << ". ";
			route.printRouteInfo();
		}
	}
	else {
		std::cout << "В данный момент нет доступных маршрутов.\n";
	}
}

// Метод, распечатывающий информацию об аккаунте.
void FlightBookingService::printAccountInfo() const  {
	std::cout << "Данные аккаунта:\n";
	std::cout << "ФИО: " << account->name << '\n';
	std::cout << "Возраст: " << account->age << '\n';
	std::cout << "Почта: " << account->email << '\n';
	std::cout << "Телефон: " << account->telephone << "\n\n";
}

// Метод, предназначенный для изменения информации профиля.
void FlightBookingService::changeAccountInfo(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	int age)
{
	account->name = name;
	account->email = email;
	account->telephone = telephone;
	account->age = age;
	std::cout << "Учетные данные Вашего аккаунта успешно изменены.\n\n";
}

// Метод, возвращающий баланс пользователя.
int FlightBookingService::getBalance() const {
	return account->balance;
}

// Метод, предназначенный для пополнения баланса пользователя.
void FlightBookingService::topUpBalance(int amount) {
	account->balance += amount;
	std::cout << "Ваш баланс успешно пополнен на " << amount << " рублей.\n";
	std::cout << "Теперь он составляет " << account->balance << " рублей.\n\n";
}

// Метод, предназначенный для добавления маршрутов.
void FlightBookingService::addRoute(const Route& route) {
	for (const auto& rt : routes) {
		if (rt == route) {
			std::cout << "Данный маршрут уже существует, добавление невозможно.\n";
			return;
		}
	}
	routes.push_back(route);
	std::cout << "Маршрут успешно добавлен.\n";
}

// Метод, предназначенный для удаления маршрута.
void FlightBookingService::removeRoute(const Route& route) {
	std::size_t index = 0;
	for (const auto& rt : routes) {
		if (rt == route) {
			routes.erase(routes.begin() + index);
			std::cout << "Маршрут успешно удален.\n";
			return;
		}
		index++;
	}
	std::cout << "Данный маршрут не найден, удаление невозможно.\n";
}

// Метод, производящий поиск маршрутов по выбранному городу.
// Выводит список всех доступных городов, город посадки которых совпадает с выбранным.
void FlightBookingService::searchTicketsByCity(const std::string& desired_city) const {
	bool is_found = false;
	std::size_t index = 1;
	for (const auto& rt : routes) {
		if (rt.arrival_city == desired_city) {
			if (!is_found) {
				is_found = true;
				std::cout << "Найдены следующие маршруты до города " << desired_city << ":\n";
			}
			std::cout << index++ << ". ";
			rt.printRouteInfo();
		}
	}
		
	if (!is_found) {
		std::cout << "Подходящих маршрутов не найдено.\n";
	}
}

// Метод, производящий поиск маршрутов по заданной цене.
// Выводит список всех доступных городов, цена билетов которых не превышает заданную.
void FlightBookingService::searchTicketsByPrice(int available_money) const {
	bool is_found = false;
	std::size_t index = 1;
	for (const auto& rt : routes) {
		if (rt.ticket_price <= available_money) {
			if (!is_found) {
				is_found = true;
				std::cout << "Найдены следующие маршруты стоимостью до " << available_money << " рублей:\n";
			}
			std::cout << index++ << ". ";
			rt.printRouteInfo();
		}
	}

	if (!is_found) {
		std::cout << "Подходящих маршрутов не найдено.\n";
	}
}

// Метод, предназначенный для покупки билетов.
void FlightBookingService::buyTicket(const Route& route) const {
	if (account->ticket != nullptr) {
		std::cout << "У Вас уже куплен билет, купить еще один невозможно.\n\n";
		return;
	}

	bool is_not_enough_money = false;
	for (const auto& rt : routes) {
		if (rt == route) {
			if (account->balance >= rt.ticket_price) {
				account->ticket = new Route();
				*account->ticket = route;
				account->balance -= route.ticket_price;
				std::cout << "Билет успешно куплен, на вашем счету "
					"осталось " << account->balance << " рублей.\n\n";
				return;
			}
			else {
				is_not_enough_money = true;
			}
		}
	}
	if (is_not_enough_money) {
		std::cout << "На Вашем счету недостаточно средств для покупки билета.\n\n";
	}
	else {
		std::cout << "Данный маршрут пока недоступен.\n\n";
	}
}

// Метод, предназначенный для продажи билета.
void FlightBookingService::sellTicket() {
	if (account->ticket != nullptr) {
		account->balance += account->ticket->ticket_price;
		delete account->ticket;
		account->ticket = nullptr;
		std::cout << "Билет успешно продан, на Вашем счету " << account->balance << " рублей.\n\n";
	}
	else std::cout << "На Вашем аккаунте нет купленных билетов.\n\n";
}

// Метод, распечатывающий информацию о купленном билете.
void FlightBookingService::printTicketInfo() const {
	if (account->ticket) account->ticket->printRouteInfo();
	else std::cout << "Билет не куплен, просмотреть информацию невозможно.\n";
}


int main(void) {
	setlocale(LC_ALL, "ru");
	FlightBookingService fbs = FlightBookingService::createFromConsole(); // Создаем сам сервис
	fbs.printAccountInfo(); // Распечатываем информацию о профиле
	fbs.changeAccountInfo("Timofey Tagaev", "timofey.tagaev.2004.12@gmail.com", "88005553535", 18); // Меняем информацию профиля
	fbs.printAccountInfo(); // Распечатываем измененную информацию о профиле

	Route routes[] = {
		Route(20000, "Barnaul", "Salt Lake City", Timestamp(12, 10, 23, 11), Timestamp(18, 00, 23, 11)),
		Route(60000, "Barnaul", "Stockholm", Timestamp(18, 45, 10, 12), Timestamp(2, 0, 11, 12)),
		Route(40000, "Barnaul", "Moscow", Timestamp(10, 0, 21, 9), Timestamp(14, 10, 21, 9))
	};
	for (const auto& i : routes) fbs.addRoute(i); // Добавляем маршруты в сервис

	fbs.printAvailableRouts(); // Распечатываем все доступные маршруты
	fbs.searchTicketsByPrice(fbs.getBalance()); // Поиск маршрутов, цена которых не превосходит баланс аккаунта
	fbs.buyTicket(routes[2]); // Покупаем билет
	fbs.printTicketInfo(); // Распечатываем информацию о билете
	fbs.buyTicket(routes[1]); // Пытаемся снова купить билет и получаем информацию об ошибке
	fbs.sellTicket(); // Продаем купленный билет
	fbs.searchTicketsByCity("Stockholm"); // Поиск городов по городу назначения "Stockholm"
	fbs.buyTicket(routes[1]); // Пытаемся купить билет и получаем сообщению о недостатке средств
	fbs.topUpBalance(10000); // Пополняем баланс
	fbs.buyTicket(routes[1]); // Покупаем билет
	fbs.removeRoute(routes[2]); // Удаляем маршрут из списка доступных
	fbs.printAvailableRouts(); // Распечатываем и видим, что маршрута нет в списке
	 
	// --- Демонстрация инициализации различных массивов объектов
	
	// Создание статического массива статических объектов класса.
	FlightBookingService static_array_of_static_objects[3];

	// Создание статического массива динамических объектов и выделение для них памяти.
	FlightBookingService* static_array_of_dynamic_objects[3];
	for (std::size_t i = 0; i < 3; ++i) {
		static_array_of_dynamic_objects[i] = new FlightBookingService;
	}
	
	// Освобождение памяти объектов с помощью оператора delete.
	for (std::size_t i = 0; i < 3; ++i) {
		delete static_array_of_dynamic_objects[i];
	}

	// Создание динамического массива статических объектов.
	FlightBookingService* dynamic_array_of_static_objects = new FlightBookingService[3];

	// Освобождение динамического массива с помощью оператора delete[].
	delete[] dynamic_array_of_static_objects;

	// Создание динамического массива динамических объектов;
	// Сначала выделяется память под сам массив, за тем для каждого из объектов.
	FlightBookingService** dynamic_array_of_dynamic_objects = new FlightBookingService*[3];
	for (std::size_t i = 0; i < 3; ++i) {
		dynamic_array_of_dynamic_objects[i] = new FlightBookingService;
	}

	// И освобождение памяти: сначала всех объектов, потом самого массива.
	for (std::size_t i = 0; i < 3; ++i) {
		delete dynamic_array_of_dynamic_objects[i];
	}
	delete[] dynamic_array_of_dynamic_objects;

	// ----------------------------------------------------------

	return 0;
}