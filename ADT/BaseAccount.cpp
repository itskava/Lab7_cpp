#include "BaseAccount.h"

BaseAccount::BaseAccount() 
	: Account() 
{}

BaseAccount::BaseAccount(const BaseAccount& other) {
	this->name = other.name;
	this->email = other.email;
	this->telephone = other.telephone;
	this->age = other.age;
	this->balance = 0;
}

BaseAccount::BaseAccount(const std::string& name, const std::string& email, const std::string& telephone, short age)
	: Account(name, email, telephone, age) 
{}

BaseAccount::~BaseAccount() = default;

BaseAccount BaseAccount::createFromConsole() {
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

	return BaseAccount(name, email, telephone, age);
}

void BaseAccount::displayAccountInfo() const {
	std::cout << "ФИО: " << name << std::endl;
	std::cout << "Контактный телефон: " << telephone << std::endl;
	std::cout << "Адрес электронной почты: " << email << std::endl;
	std::cout << "Возраст: " << age << std::endl;
	std::cout << "Баланс: " << balance << std::endl;
}

// Методы для демонстрации перегрузки метода базового класса в производном.
void BaseAccount::overloadWithoutCall() const {
	std::cout << "BaseAccount::overloadWithoutCall()" << std::endl;
}

void BaseAccount::overloadWithCall() const {
	Account::overloadWithCall();
	std::cout << " + BaseAccount::overloadWithCall()" << std::endl;
}

BaseAccount& BaseAccount::operator=(const Account& account) {
	this->name = account.getName();
	this->email = account.getEmail();
	this->telephone = account.getTelephone();
	this->age = account.getAge();
	this->balance = 0;
	
	return *this;
}

std::ostream& operator<<(std::ostream& out, const BaseAccount& obj) {
	return out << "ФИО: " << obj.name << "\nКонтактный телефон : " << obj.telephone 
		<< "\nАдрес электронной почты: " << obj.email << "\nВозраст: " << obj.age 
		<< "\nБаланс: " << obj.balance << std::endl;
}