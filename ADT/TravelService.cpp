#include "TravelService.h"
#include <iostream>
#include <algorithm>

long TravelService::profit = 0;

TravelService::TravelService(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	int age)
{
	account = new BaseAccount(name, email, telephone, age);
}

TravelService::TravelService() {
	account = new BaseAccount();
}

TravelService::~TravelService() {
	delete account;
}

// Статический метод, предназначенный для создания экземпляров класса через консоль.
TravelService TravelService::createFromConsole() {
	return TravelService(BaseAccount::createFromConsole());
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
	account->displayAccountInfo();
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
void TravelService::topUpBalance(unsigned amount) {
	account->balance += amount;
	std::cout << "Ваш баланс успешно пополнен на " << amount << " рублей.\n";
	std::cout << "Теперь он составляет " << account->balance << " рублей.\n\n";
}

// Метод, предназначенный для добавления маршрутов.
void TravelService::addRoute(const Route<std::string>& route) {
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
void TravelService::searchTicketsByPrice(unsigned available_money) const {
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

void TravelService::sortTicketsByPrice() {
	auto sort_by_price = [](const Route<std::string>& lhs, const Route<std::string>& rhs) {
		return lhs < rhs;
	};

	std::sort(routes.begin(), routes.end(), sort_by_price);
	std::cout << "Билеты успешно отсортированы." << std::endl;
}
// Метод, предназначенный для покупки билетов.
void TravelService::buyTicket(const Route<std::string>& route) const {
	if (!account->isInitialized()) {
		std::cout << "Ваш аккаунт не инициализирован. Пожалуйста, обновите информацию профиля." << std::endl;
		return;
	}

	bool is_not_enough_money = false;
	for (const auto& rt : routes) {
		if (rt == route) {
			PremiumAccount* premium_ptr = dynamic_cast<PremiumAccount*>(account);
			if (premium_ptr == nullptr) { // BaseAccount
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
			else {
				if (account->balance + premium_ptr->bonuses >= rt.ticket_price) {
					unsigned new_bonuses = premium_ptr->calculateBonuses(rt.ticket_price);
					
					if (rt.ticket_price >= premium_ptr->bonuses) {
						int price = rt.ticket_price;
						price -= premium_ptr->bonuses;
						premium_ptr->bonuses = 0;
						account->balance -= price;
					}
					else {
						premium_ptr -= rt.ticket_price;
					}

					premium_ptr->bonuses += new_bonuses;

					std::cout << "Билет успешно куплен, на счету осталось "
						<< account->balance << " рублей и " << premium_ptr->bonuses
						<< " бонусов.\n\n";
					return;
				}
				else {
					is_not_enough_money = true;
				}
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

// Метод, предназначенный для покупки премиум-аккаунта.
void TravelService::upgradeToPremium() {
	PremiumAccount* premium_ptr = dynamic_cast<PremiumAccount*>(account);
	if (premium_ptr == nullptr) {
		if (account->balance >= 2000) {
			PremiumAccount* new_account = new PremiumAccount();

			new_account->name = account->name;
			new_account->email = account->email;
			new_account->telephone = account->telephone;
			new_account->age = account->age;
			new_account->balance = account->balance - 2000;
			new_account->bonuses = 0;

			delete account;
			account = new_account;
		}
		else {
			std::cout << "На вашем аккаунте недостаточно средств, чтобы получить премиум-аккаунт." << std::endl;
		}
	}
	else {
		std::cout << "У вас уже куплен премиум-аккаунт." << std::endl;
		return;
	}
}
