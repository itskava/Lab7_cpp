#include "Account.h"
#include <iostream>

Account::Account(
	const std::string& name,
	const std::string& email, 
	const std::string& telephone,
	int age) 
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

// Статический метод, предназначенный для создания экземпляра класса через консоль.
Account Account::createFromConsole() {
	std::string name, email, telephone;
	int age;
	std::cout << "Enter Your full name: ";
	std::getline(std::cin, name);

	std::cout << "Enter Your email address: ";
	std::getline(std::cin, email);

	std::cout << "Enter Your telephone: ";
	std::getline(std::cin, telephone);

	std::cout << "Enter Your age: ";
	std::cin >> age;

	return Account(name, email, telephone, age);
}

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
	bool emailCorrectness = true;
	if (std::find(email.cbegin(), email.cend(), '@') == email.cend()) emailCorrectness = false;
	else if (std::find(email.cbegin(), email.cend(), '.') == email.cend()) emailCorrectness = false;
	else if (std::find(email.cbegin(), email.cend(), '@.') != email.cend()) emailCorrectness = false;
	else if (email[0] == '@' || email[email.length() - 1] == '.') emailCorrectness = false;

	return emailCorrectness;
}

// Метод, предназначенный для определения того, инициализирован аккаунт или нет.
bool Account::isInitialized() const {
	return !(name == "" && email == "" && telephone == "" && age == 0);
}
