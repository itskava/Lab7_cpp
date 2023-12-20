#include "AdditionalRouteInfo.h"
#include <iostream>

AdditionalRouteInfo::AdditionalRouteInfo(const std::string& weather, const std::string& destination_info)
	: weather(weather), destination_info(destination_info)
{}

std::ostream& operator<<(std::ostream& out, const AdditionalRouteInfo& info) {
	return out << info.weather << "\n" << info.destination_info << "\n";
}