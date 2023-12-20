#include "Account.h"
#include <iostream>

Account::Account(
	const std::string& name,
	const std::string& email, 
	const std::string& telephone,
	short age) 
{
	try {
		checkAccountDataCorrectness(name, email, telephone, age);
		this->name = name;
		this->email = email;
		this->telephone = telephone;
		this->age = age;
		this->balance = 0;
	}

	catch (const std::string& ex) {
		setDefaultValues();
		std::cerr << ex << std::endl;
		std::cerr << "Чтобы пользоваться сервисом, пожалуйста, обновите личную информацию на действительную." << std::endl;
	}
}

Account::Account() {
	setDefaultValues();
}

Account::~Account() = default;

// Метод, предназначенный для установки информации профиля по умолчанию.
void Account::setDefaultValues() {
	this->name = this->email = this->telephone = "";
	this->age = this->balance = 0;
}

// Метод, предназначенный для проверки правильности информации профиля.
void Account::checkAccountDataCorrectness(
	const std::string& name,
	const std::string& email,
	const std::string& telephone,
	short age) const 
{
	if (std::count(name.cbegin(), name.cend(), ' ') != 2)
		throw std::string("Вы неверно ввели ФИО.");
	if (!checkEmailCorrectness(email))
		throw std::string("Вы ввели недействительный адрес электронной почты.");
	if (telephone[0] != '+' || telephone.length() != 12)
		throw std::string("Вы ввели недействительный номер телефона.");
	if (age < 18)
		throw std::string("Чтобы создать аккаунт, вам должно быть как минимум 18 лет.");
	if (age < 0 || age > 99)
		throw std::string("Вы ввели недействительный возраст.");
}

// Метод, предназначенный для базовой проверки правильности адреса электронной почты.
bool Account::checkEmailCorrectness(const std::string& email) const {
	bool email_correctness = true;
	if (std::find(email.cbegin(), email.cend(), '@') == email.cend()) email_correctness = false;
	else if (std::find(email.cbegin(), email.cend(), '.') == email.cend()) email_correctness = false;
	else if (std::find(email.cbegin(), email.cend(), '@.') != email.cend()) email_correctness = false;
	else if (email[0] == '@' || email[email.length() - 1] == '.') email_correctness = false;

	return email_correctness;
}

// Метод, предназначенный для определения того, инициализирован аккаунт или нет.
bool Account::isInitialized() const {
	return !(name == "" && email == "" && telephone == "" && age == 0);
}

// Методы для демонстрации перегрузки метода базового класса в производном.
void Account::overloadWithoutCall() const {
	std::cout << "Account::overloadWithoutCall()" << std::endl;
}

void Account::overloadWithCall() const {
	std::cout << "Account::overloadWithCall()";
}

// Метод для демонстрации вызова виртуального метода производного класса из базового.
void Account::callVirtualMethodFromBaseClass() const {
	displayAccountInfo();
}

std::string Account::getName() const {
	return name;
}

std::string Account::getEmail() const {
	return email;
}

std::string Account::getTelephone() const {
	return telephone;
}

int Account::getAge() const {
	return age;
}
