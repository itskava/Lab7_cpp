#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "TravelService.h"
#include <iostream>


int main(void) {
	setlocale(LC_ALL, "ru");
	Account account("Hello ф ф", "timfe@ .[", "+79293233802", 18);
	TravelService ts(account);
	ts.changeAccountData("kava kava kava", "", "+79293233802", 18);
	ts.changeAccountData("Hello ф ф", "timfe@ .[", "+79293233802", 18);
	return 0;
}