#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct amenities {
	bool disabledAccess,
		wifi,
		kitchen,
		tv,
		balcony,
		washingMachine,
		airConditioning,
		swimmingPool,
		parkingLot;
}amenities;

typedef struct date {
	//start rent:
	int fromDay,
		fromMonth,
		fromYear,
		//end rent:
		toDay,
		toMonth,
		toYear;
}date;

typedef struct ad
{
	int index = -1;
	bool available;
	string description;
	int price;
	int discount = 0;
	string location;
	int numOfPeople;
	int numOfRooms;
	int numOfBeds;
	amenities ameNities;
	string attraction;
	float rating = 5;
	int dateSize = 0;
	date* occupied = NULL; //contains occupied dates.
	string email; //pointer to landlord's email.
}ad;

typedef struct traveler {
	string fullName;
	string phoneNumber;
	string password;
	date order = { 0,0,0,0,0,0 };
	int index = -1;
	string landlord_name;
	bool rate = false;
}traveler;

typedef struct landlord {
	string fullName;
	string phoneNumber;
	string password;
	string id;
	string email;
	int sumOfDeals = 0;
	int adSize = 0;
	ad* properties = NULL;
}landlord;


#endif // !STRUCTS_H