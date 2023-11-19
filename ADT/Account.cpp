#include "Account.h"
#include <iostream>

Account::Account(const std::string& name, const std::string& email, const std::string& tel, int age, int bal)
	: name(name), email(email), telephone(tel), age(age), balance(bal)
{}

Account::Account()
	: Account("", "", "", 0, 0)
{}

Account::Account(const Account& other) {
	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = other.balance;
	std::copy(other.tickets.begin(), other.tickets.end(), this->tickets.begin());
}

Account::~Account() = default;

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
	std::copy(other.tickets.begin(), other.tickets.end(), this->tickets.begin());

	return *this;
}