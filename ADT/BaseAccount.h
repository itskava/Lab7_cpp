#pragma once

#include "Account.h"

class BaseAccount : public Account {
private:
	BaseAccount(const BaseAccount& other);

	friend class TravelService;
public:
	BaseAccount();

	BaseAccount(const std::string& name, const std::string& email, const std::string& telephone, short age);

	~BaseAccount();

	void displayAccountInfo() const override;

	static BaseAccount createFromConsole();

	void overloadWithoutCall() const;

	void overloadWithCall() const;

	BaseAccount& operator=(const Account& account) override;

	friend std::ostream& operator<<(std::ostream& out, const BaseAccount& obj);
};

