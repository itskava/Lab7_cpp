#pragma once

#include "TravelService.h"
#include <iostream>

int main(void) {
	setlocale(LC_ALL, "ru");
	TravelService fbs = TravelService::createFromConsole(); // Создаем сам сервис
	fbs.printAccountInfo(); // Распечатываем информацию о профиле
	fbs.changeAccountInfo("Timofey Tagaev", "timofey.tagaev.2004.12@gmail.com", "88005553535", 18); // Меняем информацию профиля
	fbs.printAccountInfo(); // Распечатываем измененную информацию о профиле

	Route routes[] = {
		Route(20000, "Barnaul", "Salt Lake City", Timestamp(12, 10, 23, 11), Timestamp(18, 00, 23, 11)),
		Route(60000, "Barnaul", "Stockholm", Timestamp(18, 45, 10, 12), Timestamp(2, 0, 11, 12)),
		Route(40000, "Barnaul", "Moscow", Timestamp(10, 0, 21, 9), Timestamp(14, 10, 21, 9))
	};
	for (const auto& i : routes) fbs.addRoute(i); // Добавляем маршруты в сервис

	fbs.printAvailableRouts(); // Распечатываем все доступные маршруты
	fbs.searchTicketsByPrice(fbs.getBalance()); // Поиск маршрутов, цена которых не превосходит баланс аккаунта
	fbs.buyTicket(routes[2]); // Покупаем билет
	fbs.printTicketInfo(); // Распечатываем информацию о билете
	fbs.buyTicket(routes[1]); // Пытаемся снова купить билет и получаем информацию об ошибке
	fbs.sellTicket(); // Продаем купленный билет
	fbs.searchTicketsByCity("Stockholm"); // Поиск городов по городу назначения "Stockholm"
	fbs.buyTicket(routes[1]); // Пытаемся купить билет и получаем сообщению о недостатке средств
	fbs.topUpBalance(10000); // Пополняем баланс
	fbs.buyTicket(routes[1]); // Покупаем билет
	fbs.removeRoute(routes[2]); // Удаляем маршрут из списка доступных
	fbs.printAvailableRouts(); // Распечатываем и видим, что маршрута нет в списке
	 
	// --- Демонстрация инициализации различных массивов объектов
	
	// Создание статического массива статических объектов класса.
	TravelService static_array_of_static_objects[3];

	// Создание статического массива динамических объектов и выделение для них памяти.
	TravelService* static_array_of_dynamic_objects[3];
	for (std::size_t i = 0; i < 3; ++i) {
		static_array_of_dynamic_objects[i] = new TravelService;
	}
	
	// Освобождение памяти объектов с помощью оператора delete.
	for (std::size_t i = 0; i < 3; ++i) {
		delete static_array_of_dynamic_objects[i];
	}

	// Создание динамического массива статических объектов.
	TravelService* dynamic_array_of_static_objects = new TravelService[3];

	// Освобождение динамического массива с помощью оператора delete[].
	delete[] dynamic_array_of_static_objects;

	// Создание динамического массива динамических объектов;
	// Сначала выделяется память под сам массив, за тем для каждого из объектов.
	TravelService** dynamic_array_of_dynamic_objects = new TravelService*[3];
	for (std::size_t i = 0; i < 3; ++i) {
		dynamic_array_of_dynamic_objects[i] = new TravelService;
	}

	// И освобождение памяти: сначала всех объектов, потом самого массива.
	for (std::size_t i = 0; i < 3; ++i) {
		delete dynamic_array_of_dynamic_objects[i];
	}
	delete[] dynamic_array_of_dynamic_objects;

	// ----------------------------------------------------------

	return 0;
}