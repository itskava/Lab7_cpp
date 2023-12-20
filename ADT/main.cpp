#pragma once

#include "TravelService.h"
#include "AdditionalRouteInfo.h"
#include <iostream>

int main() {
	setlocale(LC_ALL, "ru");
	BaseAccount base_acc("Nill Viktorovich Kiggers", "some@inbox.com", "+12345678901", 25);
	
	base_acc.overloadWithoutCall(); // Перегруженный метод без вызова метода базового класса
	base_acc.overloadWithCall(); // Перегруженный метод с вызовом метода базового класса
	std::cout << std::endl;

	/* Демонстрация оператора присваивания объетку производного класса объекта
	базового класса. */
	Account* assign_demo1 = new BaseAccount("a b c", "a@email.com", "+79999999999", 69);
	BaseAccount assign_demo2("d e f", "b@email.com", "+78888888888", 52);
	assign_demo2 = *assign_demo1;
	std::cout << assign_demo2 << std::endl;
	delete assign_demo1;

	Account* virtual_demo = new BaseAccount("virtual method demo", "virtual@override.com", "+70046966969", 42);
	virtual_demo->displayAccountInfo(); // Вызов виртуального метода через указатель базового класса.
	std::cout << std::endl;
	BaseAccount* virtual_demo2 = new BaseAccount("virtual method demo2", "virtual@override.com", "+70046966969", 42);
	virtual_demo2->displayAccountInfo(); // Вызов виртуального метода через указатель производного класса.
	std::cout << std::endl;

	virtual_demo->callVirtualMethodFromBaseClass(); /* Вызов виртуального метода через не виртуальный метод
													   базового класса */
	std::cout << std::endl;
	
	delete virtual_demo;
	delete virtual_demo2;
	
	std::unique_ptr<AdditionalRouteInfo> info = std::make_unique<AdditionalRouteInfo>(AdditionalRouteInfo("windy, rainy", "cool"));
	Route<AdditionalRouteInfo> template_demo(20000, "Suzop", "Khleborob", Timestamp(), Timestamp(), 
		std::move(info));
	
	std::cout << template_demo;
	template_demo.displayAdditionalInfo();

	return 0;
}