#include "PremiumAccount.h"

PremiumAccount::PremiumAccount() 
	: Account()
{
	bonuses = 0;
}

PremiumAccount::PremiumAccount(const PremiumAccount& other) {
	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = 0;
	this->bonuses = 0;
}

PremiumAccount::PremiumAccount(const std::string& name, const std::string& email, const std::string& telephone, short age)
	: Account(name, email, telephone, age)
{
	bonuses = 0;
}

PremiumAccount::~PremiumAccount() = default;

PremiumAccount PremiumAccount::createFromConsole() {
	std::string name, email, telephone;
	int age;
	std::cout << "Введите Ваше ФИО: ";
	std::getline(std::cin, name);

	std::cout << "Введите Ваш адрес электронной почты: ";
	std::getline(std::cin, email);

	std::cout << "Введише Ваш телефон: ";
	std::getline(std::cin, telephone);

	std::cout << "Введите Ваш возраст: ";
	std::cin >> age;

	return PremiumAccount(name, email, telephone, age);
}

// Метод, предназначенный для подсчёта бонусов с покупки билета.
unsigned PremiumAccount::calculateBonuses(int ticket_price) const {
	return static_cast<unsigned>(ticket_price * cashback_percent);
}

void PremiumAccount::displayAccountInfo() const {
	std::cout << "ФИО: " << name << std::endl;
	std::cout << "Контактный телефон: " << telephone << std::endl;
	std::cout << "Адрес электронной почты: " << email << std::endl;
	std::cout << "Возраст: " << age << std::endl;
	std::cout << "Баланс: " << balance << std::endl;
	std::cout << "Количество бонусов: " << bonuses << std::endl;
}

PremiumAccount& PremiumAccount::operator=(const Account& account) {
	this->name = account.getName();
	this->email = account.getEmail();
	this->telephone = account.getTelephone();
	this->age = account.getAge();
	this->balance = 0;
	this->bonuses = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& out, const PremiumAccount& obj) {
	return out << "ФИО: " << obj.name << "\nКонтактный телефон : " << obj.telephone
		<< "\nАдрес электронной почты: " << obj.email << "\nВозраст: " << obj.age
		<< "\nБаланс: " << obj.balance << "\nКоличество бонусов: " << obj.bonuses << std::endl;
}