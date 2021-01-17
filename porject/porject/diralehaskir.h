#ifndef DIRALEHASKIR_H
#define DIRALEHASKIR_H
#include <iostream>
#include <stdlib.h>
//#include <cstdlib>
#include <stdio.h>
//#include <cstring>
#include <string>
//#include <string.h>
#include <fstream>
#include <ctime>
#include <ctype.h>

#define ADSBREAK "========================================="
#define ZERO 0
#define MAX_EMAIL 8 
#define MAX_ID 9
#define MAX_PHONE 10
#define MAX_NAME 15 //enough???
#define MAX_PASSWORD 10 //less???
#define MIN_PASSWORD 4
#define BUFFER 20
#define AMENITIES 9
#define NOT_FOUND -1
#define MINinput 1
#define MAX_DAY 31
#define MAX_MONTH 12
#define CURRENT_YEAR 2020
#define MAX_YEAR 2030
#define CREDIT_CARD 16
#define CVV 3

const string AMENITIES_NAMES[AMENITIES] = { "disabledAccess", "wifi", "kitchen", "tv", "balcony", "washingMachine", "airConditioning", "swimmingPool", "parkingLot" };


using namespace std;
//--------------------------------------------------------------
//---------------------Checked and Works-------------------------
//--------------------------------------------------------------
//Fields:
landlord* landlord_arr = NULL;
int landlord_arr_size = 0;
traveler* travelers_arr = NULL;
int travelers_arr_size = 0;
ad* ads_arr = NULL;
int ads_arr_size = 0;
ad** ad2Arr = NULL;//ad array for filters and sorts
int ad2size = 0;//ad array size
//Register:
void Register();
traveler NewTraveler();
void RegisterTraveler();
void RegisterLandlord();
//Sign-in funcs:
int landlordSignIn();
int findLandlordById(string id);
int travelerSignIn();
int findTravelerByName(string name);
landlord* findLandlordByName(string name);
//input validation:
bool isStringAllDig(string str);
bool isStringAllLetters(string str);
string ValidLocation();
int ValidInput();
int ValidInput(int min, int max);
bool ValidInput(char truevaluechar);
bool ValidInput(int num, int min, int max);
string NameInput();
string PhoneInput();
string PasswordInput();
string ValidId();
string ValidEmail();
amenities amenitiesCtor();
//Menus:
void MainPage();
void LandlordsLoginMenu(int ll_index, int trv_index);
void LandlordsMenu(int index);
void PrintAd(ad obj);
void EditAdMenu(int ll_index, int ad_index);
//Ads manipulations:
void DeleteAd(int landlord_index, int ad_index);
ad NewAd();
//Realloc:
void RealloctravelersArr();
void ReallocLandlordsArr();
void RealocateAdsPointer(int landlord_index);
//Output:
void PrintLandlordsAds(landlord ll);
void PrintAmenities(amenities obj);
//delete allocated data:
void deleteAllocatedData();
void deleteAd2Arr();
//extra
bool isLeap(int Y);

//--------------------------------------------------------------

void printToFile();
void printLandlordToFile();
void printAdsToFile();
void printTravelerToFile();
void readFromFile();
void readLandlordFromFile();
void readAdsFromFile();
void readTravelerFromFile();
int numOfAds();
void splitAds();
void allocateAdArrays();

int difference_of_days(int day1, int month1, int year1, int day2, int month2, int year2);
bool compareAmenities(amenities& filters, amenities obj);//true if equal
void filterAds();
bool iequals(const string& a, const string& b);//compare strings, insenstive to lower/upper case
bool ValidInput(int num, int min, int max);//check
bool isDateBiggerE(int d, int m, int y, int dd, int mm, int yy);
bool isDateAvailable(date d, const date& adDate);
bool legalInput(int day, int month, int year, int mode = 0);
date validDateInput();
void printDate(date& t);
string strToLower(string a);
bool iequalsContain(const string& a, const string& b);
void swap(ad** ad1, ad** ad2);//----------------------------------
bool sortByLTH(ad* ad1, ad* ad2);
bool sortByHTL(ad* ad1, ad* ad2);
bool sortByPopularity(ad* ad1, ad* ad2);
void searchAds();
void bubbleSort(int mode = 0);
date sortAdsByDate();
void travelerExplore();
int printAndChooseFromAdArr();
void travelerMenu(int trv_index);
//bool creditCardValidation(const string cardNumber, const string expirationMonth, const string expirationYear, const string cvv, const string ownerID);//confirm credit card details
void rateProperty(int trv_index);
bool isDateInitialized(date& d);
void occupyDates(date d, ad* a);
void validCreditCard(landlord* l, date* d, int trv_index, ad* a);
void ReallococcupyDatesArr(ad* a);
bool isDateEqual(date& d, date& adDate);
bool isDateSmallerE(int d, int m, int y, int dd, int mm, int yy);
ad* findAdByOccupiedDates(date& d);
void orderConfirmation(landlord* l, date* d, ad* a, int trv_index);
void placeOrder(ad* a, date& d, int trv_index);
void sortMenu(date chosenDates, int trv_index);
landlord* findLandlordByEmail(ad* a);
ad* findAdFromLandlord(ad* a);

//Check
//void PrintTraveler(traveler trv);
//void PrintLandlord(landlord ll);
//void FilesCheck();
#endif // !DIRALEHASKIR_H
