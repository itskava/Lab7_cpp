#pragma once

#include "Account.h"

class PremiumAccount : public Account {
private:
	const float cashback_percent = 0.04f;
	unsigned int bonuses;

private:
	PremiumAccount(const PremiumAccount& other);

	void setDefaultValues() override;
	
	unsigned int calculateBonuses(int ticket_price) const;

	friend class TravelService;

public:
	PremiumAccount();

	PremiumAccount(const std::string& name, const std::string& email, const std::string& telephone, short age);

	~PremiumAccount();
	
	void displayAccountInfo() const override;

	static PremiumAccount createFromConsole();

	friend std::ostream& operator<<(std::ostream& out, const PremiumAccount& obj);
};

