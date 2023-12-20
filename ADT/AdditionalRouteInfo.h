#pragma once

#include <string>

// Класс, предназначенный для демонстрации работы с шаблонами.
class AdditionalRouteInfo {
private:
	std::string weather;
	std::string destination_info;
public:
	AdditionalRouteInfo(const std::string& weather, const std::string& destination_info);

	friend std::ostream& operator<<(std::ostream& out, const AdditionalRouteInfo& info);
};

