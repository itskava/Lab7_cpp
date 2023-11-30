#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "TravelService.h"
#include <iostream>
#include <algorithm>

int main(void) {
	setlocale(LC_ALL, "ru");
	Timestamp timestamp_demo(30, 11, 2022, 22, 20); // Намеренно введена дата в прошлом.
	std::cout << timestamp_demo << std::endl << std::endl;
	timestamp_demo.changeData(30, 11, 2024, 22, 20); // Время изменено на действительное в будущем.
	std::cout << timestamp_demo << std::endl << std::endl;

	Account account_demo("NotFullName", "NotEmail", "NotTelephone", 5); // Намеренно записаны недействительные данные.
	TravelService ts(account_demo);
	ts.displayAccountInfo();
	ts.changeAccountData("Totally Full Name", "totallyvalid@email.com", "+89138881122", 25); // Изменены на правильные.
	ts.displayAccountInfo();
	std::cout << std::endl;

	
	Timestamp one_dim_array[3] = {
		Timestamp(10, 12, 2023, 14, 10),
		Timestamp(31, 12, 2023, 23, 59),
		Timestamp(28, 12, 2023, 10, 10)
	};
	
	// Вывод одномерного массива экземпляров класса.
	for (const auto& tm : one_dim_array) {
		std::cout << tm << std::endl;
	}
	std::cout << std::endl;

	Timestamp two_dim_array[2][2] = {
		{ Timestamp(10, 8, 2025, 0, 1), Timestamp(11, 9, 2025, 1, 2) },
		{ Timestamp(12, 10, 2025, 2, 3), Timestamp(13, 11, 2025, 3, 4) }
	};

	// Вывод двумерного массива экземпляров класса.
	for (const auto& row : two_dim_array) {
		for (const auto& tm : row) {
			std::cout << tm << ' ';
		}
		std::cout << std::endl;
	}
	return 0;
}