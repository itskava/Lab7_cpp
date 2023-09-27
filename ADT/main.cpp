#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_FLIGHTS_AMOUNT 20

typedef struct Profile {
	char* name;
	char* email;
	char* telephone;
	unsigned int age;
	int money;
};

Profile* createProfile(const char* name, const char* email, const char* telephone, unsigned int age, int money) {
	Profile* profile = (struct Profile*)malloc(sizeof(struct Profile));
	if (profile == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	profile->name = (char*)malloc(strlen(name) + 1);
	if (profile->name == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	profile->email = (char*)malloc(strlen(email) + 1);
	if (profile->email == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	profile->telephone = (char*)malloc(strlen(telephone) + 1);
	if (profile->telephone == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	strcpy(profile->name, name);
	strcpy(profile->email, email);
	strcpy(profile->telephone, telephone);
	profile->age = age;
	profile->money = money;

	return profile;
}

void updateProfile(struct Profile* profile) {}

void deleteProfile(struct Profile* profile) {
	free(profile->name);
	free(profile->email);
	free(profile->telephone);
	free(profile);
	profile = NULL;
}

void printProfileInfo(struct Profile* profile) {
	if (profile) {
		printf("ФИО: %s\n", profile->name);
		printf("Возраст: %d\n", profile->age);
		printf("Почта: %s\n", profile->email);
		printf("Телефон: %s\n", profile->telephone);
	}
}

void topUpAccount(struct Profile* profile, int money) {
	profile->money += money;
	printf("Счет аккаунта %s успешно пополнен на сумму %d рублей.\n", profile->name, money);
}

typedef struct Timestamp {
	int hour;
	int minute;
	int day;
	int month;
};

Timestamp* createTimestamp(int hour, int minute, int day, int month) {
	Timestamp* timestamp = (struct Timestamp*)malloc(sizeof(struct Timestamp));
	if (timestamp == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	timestamp->hour = hour;
	timestamp->minute = minute;
	timestamp->day = day;
	timestamp->month = month;

	return timestamp;
}

void deleteTimestamp(struct Timestamp* timestamp) {
	free(timestamp);
}

void printTimestamp(struct Timestamp* timestamp) {
	printf("%d:%d, %d.%d\n", timestamp->hour, timestamp->minute, timestamp->day, timestamp->month);
}

typedef struct DestinationPoint {
	int ticket_price;
	char* departure_city;
	char* arrival_city;
	Timestamp departure_time;
	Timestamp arrival_time;
};

DestinationPoint* createDestinationPoint(
	int ticket_price,
	const char* departure_city,
	const char* arrival_city,
	Timestamp* departure_time,
	Timestamp* arrival_time)
{
	DestinationPoint* dp = (struct DestinationPoint*)malloc(sizeof(struct DestinationPoint));
	if (dp == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	dp->departure_city = (char*)malloc(strlen(departure_city) + 1);
	if (dp->departure_city == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	dp->arrival_city = (char*)malloc(strlen(arrival_city) + 1);
	if (dp->arrival_city == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	
	dp->ticket_price = ticket_price;
	strcpy(dp->departure_city, departure_city);
	strcpy(dp->arrival_city, arrival_city);
	memcpy(&dp->departure_time, departure_time, sizeof(struct Timestamp));
	memcpy(&dp->arrival_time, arrival_time, sizeof(struct Timestamp));

	return dp;
}

void printDestinationPointInfo(struct DestinationPoint* destination_point) {
	printf("Цена билета: %d\n", destination_point->ticket_price);
	printf("Откуда: %s\n", destination_point->departure_city);
	printf("Куда: %s\n", destination_point->arrival_city);
	printf("Дата вылета: ");
	printTimestamp(&destination_point->departure_time);
	printf("Дата посадки: ");
	printTimestamp(&destination_point->arrival_time);
}

typedef struct FlightBookingService {
	DestinationPoint destinations[MAX_FLIGHTS_AMOUNT];
	int destinations_amount;
	Profile profile;
};

FlightBookingService* createFlightBookingService(struct Profile* profile) {
	FlightBookingService* fbs = (struct FlightBookingService*)malloc(sizeof(struct FlightBookingService));
	if (fbs == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}

	fbs->destinations_amount = 0;
	memcpy(&fbs->profile, profile, sizeof(struct Profile));

	return fbs;
}

void addDestinationPoint(struct FlightBookingService* fbs, struct DestinationPoint* dp) {
	if (fbs->destinations_amount < MAX_FLIGHTS_AMOUNT) {
		memcpy(&fbs->destinations[fbs->destinations_amount++], dp, sizeof(struct DestinationPoint));
		printf("Маршрут успешно добавлен.\n");
	}
	else
		printf("Достигнуто максимально возможное количество маршрутов, невозможно добавить новый.\n");
}

void searchTicketsByCity(struct FlightBookingService* fbs, const char* city) {
	int is_found = 0, index = 1;
	for (int i = 0; i < fbs->destinations_amount; ++i) {
		if (_strcmpi(fbs->destinations[i].arrival_city, city) == 0) {
			if (!is_found) {
				is_found = 1;
				printf("Найдены следующие маршруты:\n");
			}
			printf("%d. ", index++);
			printDestinationPointInfo(&fbs->destinations[i]);
			printf("\n");
		}
	}
	if (!is_found)
		printf("Подходящих маршрутов не найдено.\n");
}

void searchTicketsByPrice(struct FlightBookingService* fbs, int money) {
	int is_found = 0, index = 1;
	for (int i = 0; i < fbs->destinations_amount; ++i) {
		if (fbs->destinations[i].ticket_price <= money) {
			if (!is_found) {
				is_found = 1;
				printf("Найдены следующие маршруты:\n");
			}
			printf("%d. ", index++);
			printDestinationPointInfo(&fbs->destinations[i]);
			printf("\n");
		}
	}
	if (!is_found)
		printf("Подходящих маршрутов не найдено.\n");
}

int compareTimestamps(struct Timestamp* lhs, struct Timestamp* rhs) {
	if (lhs->day != rhs->day || lhs->month != rhs->month) return 0;
	if (lhs->minute != rhs->minute || lhs->hour != rhs->hour) return 0;
	return 1;
}

int compareDestinationPoints(struct DestinationPoint* lhs, struct DestinationPoint* rhs) {
	if (lhs->ticket_price != rhs->ticket_price) return 0;
	if (strcmp(lhs->departure_city, rhs->departure_city) != 0) return 0;
	if (strcmp(lhs->arrival_city, rhs->arrival_city) != 0) return 0;
	if (compareTimestamps(&lhs->departure_time, &rhs->departure_time) != 1) return 0;
	if (compareTimestamps(&lhs->arrival_time, &rhs->arrival_time) != 1) return 0;
	return 1;
}

void buyTicket(struct FlightBookingService* fbs, struct DestinationPoint* dp, struct Profile* profile) {
	for (int i = 0; i < fbs->destinations_amount; ++i) {
		if (compareDestinationPoints(&fbs->destinations[i], dp) == 1) {
			if (profile->money >= dp->ticket_price) {
				profile->money -= dp->ticket_price;
				printf("Билет успешно куплен, с вашего счета списано %d рублей.\n", dp->ticket_price);
			}
			else {
				printf("На счету недостаточно средств, покупка билета отменена...\n");
			}
		}
	}
}

int main(void) {
	setlocale(LC_ALL, "ru");
	Timestamp* timestamp = createTimestamp(12, 10, 23, 9);
	Timestamp* timestamp2 = createTimestamp(18, 15, 23, 9);
	DestinationPoint* dp = createDestinationPoint(20000, "Barnaul", "Stockholm", timestamp, timestamp2);
	Profile* profile = createProfile("kava", "kava@kava.com", "1488", 18, 30000);
	FlightBookingService* fbs = createFlightBookingService(profile);
	addDestinationPoint(fbs, dp);
	buyTicket(fbs, dp, profile);
	printf("%d", profile->money);
	return 0;
}