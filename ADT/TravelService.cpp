#include "TravelService.h"
#include <iostream>

long TravelService::profit = 0;

TravelService::TravelService(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	int age)
{
	account = new BaseAccount(name, email, telephone, age);
	is_premium = false;
}

TravelService::TravelService() {
	account = new BaseAccount();
	is_premium = false;
}

TravelService::~TravelService() {
	delete account;
}

// TODO

// Статический метод, предназначенный для создания экземпляров класса через консоль.
TravelService TravelService::createFromConsole() {
	return TravelService(BaseAccount::createFromConsole());
	is_premium = false;
}

// Метод, распечатывающий информации обо всех существующих маршрутах.
void TravelService::displayAvailableRouts() const {
	if (!routes.empty()) {
		std::cout << "Доступные маршруты:\n\n";
		std::size_t index = 1;

		for (const auto& route : routes) {
			std::cout << index++ << ". ";
			std::cout << route << std::endl;
		}
	}
	else {
		std::cout << "В данный момент нет доступных маршрутов.\n";
	}
}

// Метод, предназначенный для вывода информации о профиле.
void TravelService::displayAccountInfo() const {
	std::cout << "Информация об аккаунте:\n";
	std::cout << "ФИО: " << account->name << '\n';
	std::cout << "Возраст: " << account->age << '\n';
	std::cout << "Электронная почта: " << account->email << '\n';
	std::cout << "Контактный телефон: " << account->telephone << "\n\n";
}

// Метод, предназначенный для изменения информации профиля.
void TravelService::changeAccountData(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	short age)
{
	try {
		account->checkAccountDataCorrectness(name, email, telephone, age);
		account->name = name;
		account->email = email;
		account->telephone = telephone;
		account->age = age;
		std::cout << "Информация об аккаунте успешно изменена.\n\n";
	}
	catch (const std::string& ex) {
		std::cerr << ex << std::endl;
		std::cerr << "Пожалуйста, повторите попытку." << std::endl;
	}
}

// Метод, возвращающий баланс пользователя.
int TravelService::getBalance() const {
	return account->balance;
}

// Метод, предназначенный для пополнения баланса пользователя.
void TravelService::topUpBalance(unsigned int amount) {
	account->balance += amount;
	std::cout << "Ваш баланс успешно пополнен на " << amount << " рублей.\n";
	std::cout << "Теперь он составляет " << account->balance << " рублей.\n\n";
}

// Метод, предназначенный для добавления маршрутов.
void TravelService::addRoute(const Route& route) {
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
void TravelService::removeRoute(std::size_t desired_ind) {
	if (routes.empty()) {
		std::cout << "Сейчас нет доступных маршрутов";
		return;
	}

	if (desired_ind < 1 || desired_ind > routes.size()) {
		std::cout << "Введен некорректный номер билета." << std::endl;
		return;
	}
	
	std::size_t index = 1;
	for (auto it = routes.begin(); it != routes.end(); it++, index++) {
		if (index == desired_ind) {
			routes.erase(it);
			std::cout << "Маршрут успешно удален.\n";
			return;
		}
	}
}

// Метод, производящий поиск маршрутов по выбранному городу.
// Выводит список всех доступных городов, город посадки которых совпадает с выбранным.
void TravelService::searchTicketsByCity(const std::string& desired_city) const {
	bool is_found = false;
	std::size_t index = 1;
	for (const auto& rt : routes) {
		if (rt.arrival_city == desired_city) {
			if (!is_found) {
				is_found = true;
				std::cout << "Найдены следующие маршруты до города " << desired_city << ":\n";
			}
			std::cout << index++ << ". ";
			std::cout << rt << std::endl;
		}
	}

	if (!is_found) {
		std::cout << "Подходящих маршрутов не найдено.\n";
	}
}

// Метод, производящий поиск маршрутов по заданной цене.
// Выводит список всех доступных городов, цена билетов которых не превышает заданную.
void TravelService::searchTicketsByPrice(unsigned int available_money) const {
	bool is_found = false;
	std::size_t index = 1;
	for (const auto& rt : routes) {
		if (rt.ticket_price <= available_money) {
			if (!is_found) {
				is_found = true;
				std::cout << "Найдены следующие маршруты стоимостью до " << available_money << " рублей:\n";
			}
			std::cout << index++ << ". ";
			std::cout << rt << std::endl;
		}
	}

	if (!is_found) {
		std::cout << "Подходящих маршрутов не найдено.\n";
	}
}

// Метод, предназначенный для покупки билетов.
void TravelService::buyTicket(const Route& route) const {
	if (!account->isInitialized()) {
		std::cout << "Ваш аккаунт не инициализирован. Пожалуйста, обновите информацию профиля." << std::endl;
		return;
	}

	bool is_not_enough_money = false;
	for (const auto& rt : routes) {
		if (rt == route) {
			if (account->balance >= rt.ticket_price) {
				account->tickets.push_back(rt);
				account->balance -= route.ticket_price;
				profit += route.ticket_price;
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
void TravelService::sellTicket(std::size_t desired_ind) {
	if (!account->isInitialized()) {
		std::cout << "Ваш аккаунт не инициализирован. Пожалуйста, обновите информацию профиля." << std::endl;
		return;
	}

	if (account->tickets.empty()) {
		std::cout << "На Вашем аккаунте нет купленных билетов.\n\n";
		return;
	}

	if (desired_ind < 1 || desired_ind > account->tickets.size()) {
		std::cout << "Введен некорректный номер купленного билета." << std::endl;
		return;
	}

	std::size_t index = 1;

	for (auto it = account->tickets.begin(); it != account->tickets.end(); it++, index++) {
		if (index == desired_ind) {
			account->balance += it->ticket_price;
			profit -= it->ticket_price;
			account->tickets.erase(it);
			break;
		}
	}

	std::cout << "Билет успешно продан, на Вашем счету " << account->balance << " рублей.\n\n";
	
}

// Метод, распечатывающий информацию о купленном билете.
void TravelService::displayTicketsInfo() const {
	if (account->tickets.empty()) {
		std::cout << "На Вашем аккаунте нет купленных билетов.\n";
		return;
	}

	std::size_t index = 1;
	for (const auto& route : account->tickets) {
		std::cout << index++ << ". " << route << std::endl;
	}
}

// Метод, распечатывающий информацию о прибыли компании.
void TravelService::displayCompanyProfit() {
	std::cout << "На данный момент прибыль компании составляет " << profit << " рублей.\n\n";
}

void TravelService::upgradeToPremium() {
	if (is_premium) return;

	if (account->balance >= 2000) {
		Account* temp = account;
		account = new PremiumAccount();
		account = dynamic_cast<PremiumAccount*>(temp);
		delete temp;
	}
	else {
		std::cout << "На вашем аккаунте недостаточно средств, чтобы получить премиум-аккаунт." << std::endl;
	}
}