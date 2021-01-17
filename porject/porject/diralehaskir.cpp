#define _CRT_SECURE_NO_WARNINGS
#include "structs.h"
#include "diralehaskir.h"
using namespace std;


//-------------print to file
void printToFile() {
	printLandlordToFile();//print all landlords
	printAdsToFile();//print all ads
	printTravelerToFile();//print all travelers
}

//-------------printLandlordToFile
void printLandlordToFile() {
	ofstream outFile;
	try {
		outFile.open("landlord.data");//open file in ios::out default mode
		if (!outFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	outFile << landlord_arr_size << endl;//prints size of landlord array
	int i = 0;
	for (; i < landlord_arr_size; ++i) {
		outFile << landlord_arr[i].fullName << endl
			<< landlord_arr[i].phoneNumber << endl
			<< landlord_arr[i].password << endl
			<< landlord_arr[i].id << endl
			<< landlord_arr[i].email << endl
			<< landlord_arr[i].sumOfDeals << endl
			<< landlord_arr[i].adSize << endl;//num of ads for this landlord
	}
	outFile.close();//close file
}

//-------------printAdsToFile
void printAdsToFile() {
	ofstream outFile;
	try {
		outFile.open("properties.data");//open file in ios::out default mode
		if (!outFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	outFile << numOfAds() << endl;//prints amount of all ads
	int i = 0;
	for (; i < landlord_arr_size; ++i) {
		for (int j = 0; j < landlord_arr[i].adSize; ++j) {
			outFile << landlord_arr[i].properties[j].available << endl
				<< landlord_arr[i].properties[j].description << endl
				<< landlord_arr[i].properties[j].price << endl
				<< landlord_arr[i].properties[j].discount << endl
				<< landlord_arr[i].properties[j].location << endl
				<< landlord_arr[i].properties[j].numOfPeople << endl
				<< landlord_arr[i].properties[j].numOfRooms << endl
				<< landlord_arr[i].properties[j].numOfBeds << endl;
			//print amenities
			outFile << landlord_arr[i].properties[j].ameNities.disabledAccess << endl
				<< landlord_arr[i].properties[j].ameNities.wifi << endl
				<< landlord_arr[i].properties[j].ameNities.kitchen << endl
				<< landlord_arr[i].properties[j].ameNities.tv << endl
				<< landlord_arr[i].properties[j].ameNities.balcony << endl
				<< landlord_arr[i].properties[j].ameNities.washingMachine << endl
				<< landlord_arr[i].properties[j].ameNities.airConditioning << endl
				<< landlord_arr[i].properties[j].ameNities.swimmingPool << endl
				<< landlord_arr[i].properties[j].ameNities.parkingLot << endl;
			//print rest
			outFile << landlord_arr[i].properties[j].attraction << endl
				<< landlord_arr[i].properties[j].rating << endl
				<< landlord_arr[i].properties[j].email << endl
				<< landlord_arr[i].properties[j].dateSize << endl;
			//print occupied dates
			for (int k = 0; k < landlord_arr[i].properties[j].dateSize; ++k) {
				outFile << landlord_arr[i].properties[j].occupied[k].fromDay << endl
					<< landlord_arr[i].properties[j].occupied[k].fromMonth << endl
					<< landlord_arr[i].properties[j].occupied[k].fromYear << endl
					<< landlord_arr[i].properties[j].occupied[k].toDay << endl
					<< landlord_arr[i].properties[j].occupied[k].toMonth << endl
					<< landlord_arr[i].properties[j].occupied[k].toYear << endl;
			}
		}
	}
	outFile.close();//close file
}

int numOfAds() {
	int sum = 0;
	for (int i = 0; i < landlord_arr_size; ++i)
		sum += landlord_arr[i].adSize;
	return sum;
}

//-------------printTravelerToFile
void printTravelerToFile() {
	ofstream outFile;
	try {
		outFile.open("traveler.data");//open file in ios::out default mode
		if (!outFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	outFile << travelers_arr_size << endl;//prints size of landlord array
	int i = 0;
	for (; i < travelers_arr_size; ++i) {
		outFile << travelers_arr[i].fullName << endl
			<< travelers_arr[i].phoneNumber << endl
			<< travelers_arr[i].password << endl
			<< travelers_arr[i].order.fromDay << endl
			<< travelers_arr[i].order.fromMonth << endl
			<< travelers_arr[i].order.fromYear << endl
			<< travelers_arr[i].order.toDay << endl
			<< travelers_arr[i].order.toMonth << endl
			<< travelers_arr[i].order.toYear << endl
			<< travelers_arr[i].index << endl
			<< travelers_arr[i].landlord_name << endl
			<< travelers_arr[i].rate << endl;
	}
	outFile.close();//close file
}

//-------------read from file
void readFromFile() {
	deleteAllocatedData();//without deleting ad2Arr
	//read all landlords
	readLandlordFromFile();//read all landlords
	//read all ads
	readAdsFromFile();//read all landlords
	//read all travelers
	readTravelerFromFile();
	//distribute ads to corresponding landlords
	splitAds();
}

//-------------readlandlordFromFile
void readLandlordFromFile() {//read all landlords
	ifstream inFile;
	try {
		inFile.open("landlord.data");//open in default mode
		if (!inFile)
			throw("can't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if succeeded
	inFile >> landlord_arr_size;
	if (!landlord_arr_size)
		return;
	try {
		landlord_arr = new landlord[landlord_arr_size];
		if (!landlord_arr)
			throw("allocation failed in readFromFile-landlord");
	}
	catch (const char* const x) {
		cout << x << endl;
		inFile.close();
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if succeeded
	for (int i = 0; i < landlord_arr_size; ++i)
	{
		inFile.ignore();
		getline(inFile, landlord_arr[i].fullName);
		inFile >> landlord_arr[i].phoneNumber;
		inFile >> landlord_arr[i].password;
		inFile >> landlord_arr[i].id;
		inFile >> landlord_arr[i].email;
		inFile >> landlord_arr[i].sumOfDeals;
		inFile >> landlord_arr[i].adSize;
	}
	inFile.close();//close file
}

//-------------readAdsFromFile
void readAdsFromFile() {//read ads for landlord
	ifstream inFile;
	try {
		inFile.open("properties.data");//open file in ios::out default mode
		if (!inFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	inFile >> ads_arr_size;
	if (!ads_arr_size)
		return;
	try {
		ads_arr = new ad[ads_arr_size];
		if (!ads_arr)
			throw("allocation failed in readFromFile-ads");
	}
	catch (const char* const x) {
		cout << x << endl;
		inFile.close();
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if succeeded

	for (int i = 0; i < ads_arr_size; ++i) {
		ads_arr[i].index = i;
		inFile >> ads_arr[i].available;
		inFile.ignore();
		getline(inFile, ads_arr[i].description);
		inFile >> ads_arr[i].price;
		inFile >> ads_arr[i].discount;
		inFile.ignore();
		getline(inFile, ads_arr[i].location);
		inFile >> ads_arr[i].numOfPeople;
		inFile >> ads_arr[i].numOfRooms;
		inFile >> ads_arr[i].numOfBeds;
		//print amenities
		inFile >> ads_arr[i].ameNities.disabledAccess;
		inFile >> ads_arr[i].ameNities.wifi;
		inFile >> ads_arr[i].ameNities.kitchen;
		inFile >> ads_arr[i].ameNities.tv;
		inFile >> ads_arr[i].ameNities.balcony;
		inFile >> ads_arr[i].ameNities.washingMachine;
		inFile >> ads_arr[i].ameNities.airConditioning;
		inFile >> ads_arr[i].ameNities.swimmingPool;
		inFile >> ads_arr[i].ameNities.parkingLot;
		//read rest
		inFile.ignore();
		getline(inFile, ads_arr[i].attraction);
		inFile >> ads_arr[i].rating;
		inFile >> ads_arr[i].email;
		inFile >> ads_arr[i].dateSize;
		try {
			ads_arr[i].occupied = new date[ads_arr[i].dateSize];
			if (!ads_arr[i].occupied)
				throw("allocation failed in readFromFile-dates");
		}
		catch (const char* const x) {
			cout << x << endl;
			inFile.close();
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
		//read occupied dates
		for (int j = 0; j < ads_arr[i].dateSize; ++j) {
			inFile >> ads_arr[i].occupied[j].fromDay;
			inFile >> ads_arr[i].occupied[j].fromMonth;
			inFile >> ads_arr[i].occupied[j].fromYear;
			inFile >> ads_arr[i].occupied[j].toDay;
			inFile >> ads_arr[i].occupied[j].toMonth;
			inFile >> ads_arr[i].occupied[j].toYear;
		}
	}
	inFile.close();//close file
}

//-------------readTravelerFromFile
void readTravelerFromFile() {
	ifstream inFile;
	try {
		inFile.open("traveler.data");//open file in ios::out default mode
		if (!inFile)
			throw("couldn't open file");
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if opening file succeeded
	inFile >> travelers_arr_size;//reads size of traveler array
	try {
		travelers_arr = new traveler[travelers_arr_size];
		if (!travelers_arr)
			throw("allocation failed in readFromFile-traveler");
	}
	catch (const char* const x) {
		cout << x << endl;
		inFile.close();
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//if allocation succeeded
	int i = 0;
	for (; i < travelers_arr_size; ++i) {
		inFile.ignore();
		getline(inFile, travelers_arr[i].fullName);
		inFile >> travelers_arr[i].phoneNumber;
		inFile >> travelers_arr[i].password;
		inFile >> travelers_arr[i].order.fromDay;
		inFile >> travelers_arr[i].order.fromMonth;
		inFile >> travelers_arr[i].order.fromYear;
		inFile >> travelers_arr[i].order.toDay;
		inFile >> travelers_arr[i].order.toMonth;
		inFile >> travelers_arr[i].order.toYear;
		inFile >> travelers_arr[i].index;
		inFile.ignore();
		getline(inFile, travelers_arr[i].landlord_name);
		inFile >> travelers_arr[i].rate;
	}
	inFile.close();//close file
}

void splitAds() {//assigns each landlord his ads
	allocateAdArrays();//allocates all landlords adArr and turns sizes to 0
	int k = 0;
	for (int j = 0; j < landlord_arr_size; ++j) {
		k = 0;
		for (int i = 0; i < ads_arr_size; ++i) {
			if (k < landlord_arr[j].adSize) {
				if (ads_arr[i].email == landlord_arr[j].email) {
					landlord_arr[j].properties[k] = ads_arr[i];
					++k;
				}
			}
			else
				break;	
		}
	}
}

void allocateAdArrays() {//allocates all landlords adArr and turns sizes to 0
	for (int i = 0; i < landlord_arr_size; ++i) {
		try {
			landlord_arr[i].properties = new ad[landlord_arr[i].adSize];
			if (!landlord_arr[i].properties)
				throw("allocation failed in readFromFile-allocate ads array");
		}
		catch (const char* const x) {
			cout << x << endl;
			throw;
		}
		catch (...) {
			cout << "ERROR!" << endl;
			throw;
		}
	}
}
//-------------sort(display options in loop)
//------sort by low lo high*************************************************************
bool sortByLTH(ad* ad1, ad* ad2) {
	if (ad1->price - ad1->discount > ad2->price - ad2->discount)
		return true;
	return false;
}
//------sort by high to low*************************************************************
bool sortByHTL(ad* ad1, ad* ad2) {
	if (ad1->price - ad1->discount < ad2->price - ad2->discount)
		return true;
	return false;
}
//------sort by popularity(default)*****************************************************
bool sortByPopularity(ad* ad1, ad* ad2) {
	if (ad1->rating < ad2->rating)
		return true;
	return false;
}
// An optimized version of Bubble Sort**************************************************

void bubbleSort(int mode)
{
	int i, j;
	bool swapped;
	for (i = 0; i < ad2size - 1; i++)
	{
		swapped = false;
		for (j = 0; j < ad2size - i - 1; j++)
		{
			if (mode == 0) {//popularity(default)
				if (sortByPopularity(ad2Arr[j], ad2Arr[j + 1])) {
					swap(ad2Arr[j], ad2Arr[j + 1]);
					swapped = true;
				}
			}
			else if (mode == 1) {//low to high
				if (sortByLTH(ad2Arr[j], ad2Arr[j + 1])) {
					swap(ad2Arr[j], ad2Arr[j + 1]);
					swapped = true;
				}
			}
			else {//high to low
				if (sortByHTL(ad2Arr[j], ad2Arr[j + 1])) {
					swap(ad2Arr[j], ad2Arr[j + 1]);
					swapped = true;
				}
			}
		}
		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}

//------sort by dates***************************************************************

date sortAdsByDate() {
	//get date
	date d = validDateInput();
	//if (ad2size == NOT_FOUND) {
	//	ad2size = 0;
	//	////runs over landlors arr returns all ads available at the requested dates
	//	//for (int i = 0; i < landlord_arr_size; ++i) {
	//	//	for (int j = 0; j < landlord_arr[i].adSize; ++j) {
	//	//		for (int k = 0; k < landlord_arr[i].properties[j].dateSize; ++k) {
	//	//			//check if dates in ad are available
	//	//			if (isDateAvailable(d, landlord_arr[i].properties[j].occupied[k]))
	//	//				++ads_arr_size;//counts how many ads qualify
	//	//		}
	//	//	}
	//	//}
	//	//try {
	//	//	ads_arr = new ad[ads_arr_size];
	//	//	if (!ads_arr)
	//	//		throw("allocation failed in sort ads by date");
	//	//}

	//	//runs over original adArr and counts ads that qualify
	//	for (int i = 0; i > ads_arr_size; ++i) {
	//		for (int k = 0; k < ads_arr[i].dateSize; ++k) {
	//			//check if dates in ad are available
	//			if (isDateAvailable(d, ads_arr[i].occupied[k]))
	//				++ad2size;//counts how many ads qualify
	//		}
	//	}
	//	try {
	//		ad2Arr = new ad*[ad2size];
	//		if (!ad2Arr)
	//			throw("allocation failed in filter ads");
	//	}
	//	catch (const char* const x) {
	//		cout << x << endl;
	//		throw;
	//	}
	//	catch (...) {
	//		cout << "ERROR!" << endl;
	//		throw;
	//	}
	//	//if allocation successfull
	//	//for (int i = 0; i < landlord_arr_size; ++i) {
	//	//	for (int j = 0; j < landlord_arr[i].adSize; ++j) {
	//	//		for (int k = 0; k < landlord_arr[i].properties[j].dateSize; ++k) {
	//	//			//check if dates in ad are available
	//	//			if (isDateAvailable(d, landlord_arr[i].properties[j].occupied[k]))
	//	//				ads_arr[i] = landlord_arr[i].properties[j];//add ad to adArr if dates available
	//	//		}
	//	//	}
	//	//}

	//	for (int i = 0; i > ads_arr_size; ++i) {
	//		for (int k = 0; k < ads_arr[i].dateSize; ++k) {
	//			//check if dates in ad are available
	//			if (isDateAvailable(d, ads_arr[i].occupied[k]))
	//				ad2Arr[i] = &ads_arr[i];//add ad to adArr
	//		}
	//	}
	//}
	//else {
		int tempSize = 0;
		//run over existing adArr and return matching ads
		//runs over adArr returns all ads available at the requested dates
		for (int i = 0; i < ads_arr_size; ++i) {
			for (int j = 0; j < ads_arr[i].dateSize; ++j) {
				//check if dates in ad are available
				if (isDateAvailable(d, ads_arr[i].occupied[j]))
					++tempSize;//counts how many ads qualify
			}
		}
		if (tempSize) {//found qualified ads in adArr
			int index = 0;
			for (int i = 0; i < ads_arr_size; ++i) {
				for (int j = 0; j < ads_arr[i].dateSize; ++j) {
					//check if dates in ad are available
					if (isDateAvailable(d, ads_arr[i].occupied[j])) {//if available
						ads_arr[index] = ads_arr[i];//enter to index's location in adArr
						++index;//inc index after assignment
					}
				}
			}
		}
		else cout << "No ads with the previous filters match your description." << endl
			<< "Clear all filters and try again." << endl;
		ads_arr_size = tempSize;
	//}
	return d;
}

//-------------filter(display options in loop)
void filterAds() {//***********************
	amenities filters;
	cout << "please choose the filters you wish to apply:" << endl;
	filters = amenitiesCtor();//gets amenities from user

	//if (ad2size == NOT_FOUND) {
	//	ad2size = 0;
	//	////runs over landlors arr returns all ads that has the requested filters
	//	//cout << "please choose the filters you wish to apply:" << endl;
	//	//filters = amenitiesCtor();//gets amenities from user
	//	//for (int i = 0; i < landlord_arr_size; ++i) {
	//	//	for (int j = 0; j < landlord_arr[i].adSize; ++j) {
	//	//		//check if amenities equal
	//	//		if (compareAmenities(filters, landlord_arr[i].properties[j].ameNities))
	//	//			++ad2size;//counts how many ads qualify
	//	//	}
	//	//}
	//	
	//	//runs over original adArr and counts ads that qualify
	//	for (int i = 0; i > ads_arr_size; ++i) {
	//		//check if amenities qualify
	//		if (compareAmenities(filters, ads_arr[i].ameNities))
	//			++ad2size;//counts how many ads qualify
	//	}
	//	try {
	//		ad2Arr = new ad*[ad2size];
	//		if (!ad2Arr)
	//			throw("allocation failed in filter ads");
	//	}
	//	catch (const char* const x) {
	//		cout << x << endl;
	//		throw;
	//	}
	//	catch (...) {
	//		cout << "ERROR!" << endl;
	//		throw;
	//	}
	//	//if allocation successfull collect all qualified ads
	//	for (int i = 0; i > ads_arr_size; ++i) {
	//		//check if amenities qualify
	//		if (compareAmenities(filters, ads_arr[i].ameNities))
	//			ad2Arr[i] = &ads_arr[i];//add ad to adArr if filters are matching
	//	}
	//	
	//	//for (int i = 0; i < landlord_arr_size; ++i) {
	//	//	for (int j = 0; j < landlord_arr[i].adsize; ++j) {
	//	//		//check if amenities equal
	//	//		if (compareamenities(filters, landlord_arr[i].properties[j].amenities))
	//	//			ads_arr[i] = landlord_arr[i].properties[j];//add ad to adarr if filters are matching
	//	//	}
	//	//}
	//}
	//else {
		int tempSize = 0;
		//run over existing adArr and return matching ads
		//runs over adArr returns all ads with matches
		for (int i = 0; i < ad2size; ++i) {
			//check if amenities qualify
			if (compareAmenities(filters, ad2Arr[i]->ameNities))
				++tempSize;//counts how many ads qualify
		}
		if (tempSize) {//found qualified ads in adArr
			int index = 0;
			for (int i = 0; i < ad2size; ++i) {
				//check if amenities qualify
				if (compareAmenities(filters, ad2Arr[i]->ameNities)) {//if available
					ad2Arr[index] = ad2Arr[i];//enter to index's location in adArr
					++index;//inc index after assignment
				}
			}
		}
		else cout << "No ads with the previous filters match your description." << endl
			<< "Clear all filters and try again." << endl;
		ad2size = tempSize;
	//}
}

void travelerExplore() {//**********************
	deleteAd2Arr();
	ad2size = ads_arr_size;
	//allocate
	try {
		ad2Arr = new ad*[ad2size];
		if (!ad2Arr)
			throw "exception thrown in traveler explore";
	}
	catch (const char* const x) {
		cout << x << endl;
		throw;
	}
	catch (...) {
		cout << "ERROR!" << endl;
		throw;
	}
	//copies all ads from original ad array
	for (int i = 0; i < ads_arr_size; ++i) {
		ad2Arr[i] = &ads_arr[i];
	}
	bubbleSort();
}

bool compareAmenities(amenities& filters, amenities obj)
{//true if has the filter amenities.
	if (filters.airConditioning && !obj.airConditioning)
		return false;
	if (filters.balcony && !obj.balcony)
		return false;
	if (filters.disabledAccess && !obj.disabledAccess)
		return false;
	if (filters.kitchen && !obj.kitchen)
		return false;
	if (filters.parkingLot && !obj.parkingLot)
		return false;
	if (filters.swimmingPool && !obj.swimmingPool)
		return false;
	if (filters.tv && !obj.tv)
		return false;
	if (filters.washingMachine && !obj.washingMachine)
		return false;
	if (filters.wifi && !obj.wifi)
		return false;
	return true;
}

//-------------search*********************************************************************
void searchAds() {
	cout << "please enter the required location:" << endl;
	string location = ValidLocation();//gets location from user
	//if (ad2size == NOT_FOUND) {
	//	ad2size = 0;
	//	//runs over landlors arr returns all ads that has the requested filters
	//	//for (int i = 0; i < landlord_arr_size; ++i) {
	//	//	for (int j = 0; j < landlord_arr[i].adSize; ++j) {
	//	//		//check if amenities equal
	//	//		if (iequalsContain(landlord_arr[i].properties[j].location, location))//if equal/contains
	//	//			++ads_arr_size;//counts how many ads qualify
	//	//	}
	//	//}
	//	
	//	//run over original ads array and count how many qualify
	//			//runs over original adArr and counts ads that qualify
	//	for (int i = 0; i > ads_arr_size; ++i) {
	//		//check if locations equal
	//		if (iequalsContain(ads_arr[i].location, location))
	//			++ad2size;//counts how many ads qualify
	//	}
	//	try {
	//		ad2Arr = new ad*[ad2size];
	//		if (!ad2Arr)
	//			throw("allocation failed in search ads");
	//	}
	//	catch (const char* const x) {
	//		cout << x << endl;
	//		throw;
	//	}
	//	catch (...) {
	//		cout << "ERROR!" << endl;
	//		throw;
	//	}
	//	//if allocation successfull collect all qualified ads
	//	for (int i = 0; i > ads_arr_size; ++i) {
	//		//check if locations equal
	//		if (iequalsContain(ads_arr[i].location, location))
	//			ad2Arr[i] = &ads_arr[i];//add ad to adArr if locations are matching
	//	}
	//	//try {
	//	//	ads_arr = new ad[ads_arr_size];
	//	//	if (!ads_arr)
	//	//		throw("allocation failed in search ads");
	//	//}
	//	//catch (const char* const x) {
	//	//	cout << x << endl;
	//	//	throw;
	//	//}
	//	//catch (...) {
	//	//	cout << "ERROR!" << endl;
	//	//	throw;
	//	//}
	//	//if allocation successfull
	//	//for (int i = 0; i < landlord_arr_size; ++i) {
	//	//	for (int j = 0; j < landlord_arr[i].adSize; ++j) {
	//	//		//check if amenities equal
	//	//		if (iequalsContain(landlord_arr[i].properties[j].location, location))
	//	//			ads_arr[i] = landlord_arr[i].properties[j];//add ad to adArr if locations are matching
	//	//	}
	//	//}
	//}
	//else {
		int tempSize = 0;
		//run over existing adArr and return matching ads
		//runs over adArr returns all ads with sub string location
		for (int i = 0; i < ad2size; ++i) {
			//check if ads qualify
			if (iequalsContain(location, ad2Arr[i]->location)) {
				++tempSize;//counts how many ads qualify
			}
		}
		if (tempSize) {//found qualified ads in adArr
			int index = 0;
			for (int i = 0; i < ad2size; ++i) {
				//check if ads qualify
				if (iequalsContain(location, ad2Arr[i]->location)) {//if location is equal/contained
					ad2Arr[index] = ad2Arr[i];//enter to index's location in adArr
					++index;//inc index after assignment
				}
			}
		}
		else cout << "No ads with the previous filters match your description." << endl
			<< "Clear all filters and try again." << endl;
		ad2size = tempSize;
	//}

}

bool iequals(const string& a, const string& b)//compare strings, insenstive to lower/upper case
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}
//-------------dates availability------------------------------------------------------ 
bool isDateAvailable(date d, const date& adDate)
{//doesn't check validity of dates, needs to happen prior

	//checkin= d.fromDate, checkout= d.toDate, beginning= adDate.fromDate, ending= adDate.toDate
	//(beginning >= checkin && checkout >= beginning)||(checkin >= beginning && ending >= checkin)
	if ((isDateBiggerE(adDate.fromDay, adDate.fromMonth, adDate.fromYear, d.fromDay, d.fromMonth, d.fromYear)
		&& isDateBiggerE(d.toDay, d.toMonth, d.toYear, adDate.fromDay, adDate.fromMonth, adDate.fromYear))
		|| (isDateBiggerE(d.fromDay, d.fromMonth, d.fromYear, adDate.fromDay, adDate.fromMonth, adDate.fromYear)
			&& isDateBiggerE(adDate.toDay, adDate.toMonth, adDate.toYear, d.fromDay, d.fromMonth, d.fromYear)))
		return false;
	return true;
}//checks if dated are overlapping, false if UNavailable

bool legalInput(int day, int month, int year, int mode) {//-------------------------------------------
	time_t t = time(ZERO);
	tm* now = localtime(&t);

	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (!mode) {
			return (ValidInput(day, MINinput, 31) &&
				isDateBiggerE(day, month, year, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)
				&& ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		}
		return (ValidInput(day, MINinput, 31) && ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		break;
	case 2:
		if (!mode) {
			return (ValidInput(day, MINinput, isLeap(year) ? 29 : 28) &&
				isDateBiggerE(day, month, year, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)
				&& ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		}
		return (ValidInput(day, MINinput, isLeap(year) ? 29 : 28) && ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (!mode) {
			return (ValidInput(day, MINinput, 30) &&
				isDateBiggerE(day, month, year, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)
				&& ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		}
		return (ValidInput(day, MINinput, 30) && ValidInput(year, CURRENT_YEAR, MAX_YEAR));
		break;
	default:
		return false;
	}
	return false;
}

date validDateInput() {//----------------------------------------------------------------
	bool flag = true;
	bool valid = true;
	int d, m, y, dd, mm, yy;
	int confirm = 1;
	date dt;
	system("CLS");
	do {
		cout << "Enter values according to instructions." << endl;
		do {
			cout << "please enter date: " << endl;
			cout << "*************CHECK IN**************" << endl;

			//test if legal d/m/y
			cout << "Day (from " << MINinput << " to " << MAX_DAY << "): ";
			cin >> d;
			cout << endl << "Month (from " << MINinput << " to " << MAX_MONTH << "): ";
			cin >> m;
			cout << endl << "Year (from " << CURRENT_YEAR << " to " << MAX_YEAR << "): ";
			cin >> y;
			//bigger or equal to today
			valid = legalInput(d, m, y);
			if (valid)
				flag = false;
			else {
				cout << "invalid date, please try again." << endl;
			}
			cout << "***********************************" << endl;
		} while (flag);
		flag = true;
		dt.fromDay = d;
		dt.fromMonth = m;
		dt.fromYear = y;
		//same for check out
		do {
			cout << "please enter date: " << endl;
			cout << "************CHECK OUT**************" << endl;
			//test if legal d/m/y
			cout << "Day (from " << d << " to " << MAX_DAY << "): ";
			cin >> dd;
			cout << endl << "Month (from " << MINinput << " to " << MAX_MONTH << "): ";
			cin >> mm;
			cout << endl << "Year (from " << y << " to " << MAX_YEAR << "): ";
			cin >> yy;
			//bigger or equal to today
			valid = (legalInput(d, m, y, 1) && isDateBiggerE(dd, mm, yy, d, m, y));
			if (valid)
				flag = false;
			else {
				cout << "invalid date, please try again." << endl;
			}
			cout << "***********************************" << endl;
		} while (flag);
		flag = true;
		dt.toDay = dd;
		dt.toMonth = mm;
		dt.toYear = yy;
		printDate(dt);
		cout << "enter 0 to confirm dates, else to try again." << endl;
		cin >> confirm;
	} while (confirm);
	return dt;
}//returns date with valid input from user

void printDate(date& t) {//---------------------------------------------------
	if (isDateInitialized(t)) {
		cout << "No order yet!" << endl;
		return;
	}
	cout << "CHECK IN: ";
	cout << t.fromDay << "/" << t.fromMonth << "/" << t.fromYear << endl;
	cout << "CHECK OUT: ";
	cout << t.toDay << "/" << t.toMonth << "/" << t.toYear << endl;
}

void ReallococcupyDatesArr(ad* a)
{
	date* temp = new date[a->dateSize + 1];
	for (int i = 0; i < a->dateSize; i++) temp[i] = a->occupied[i];
	a->dateSize++;
	delete[] a->occupied;
	a->occupied = temp;
}

//-------------occupy dates
void occupyDates(date d, ad* a)
{
	ReallococcupyDatesArr(a);
	a->occupied[a->dateSize - 1] = d;
	for (int i = 0; i < a->dateSize; ++i) printDate(a->occupied[i]);//---------------------
}

//-------------confirm credit card info
void validCreditCard(landlord* l, date* d, int trv_index, ad* a) {
	bool flag;
	string buffer;
	cout << endl << "---enter credit card details--- " << endl;
	//credit card number
	do {
		flag = false;
		cout << "Credit card number must be exactly  " << CREDIT_CARD << " digits, numbers only." << endl;
		cout << "Please enter your credit card number: " << endl;
		cin.ignore();
		getline(cin, buffer);
		if (!(buffer.length() == CREDIT_CARD)) flag = true;
		if (!isStringAllDig(buffer)) flag = true;
		if (flag) cout << "Incorrect input, try again." << endl;
	} while (flag);
	
	//expiary dates
	do {
		flag = false;
		cout << "please enter expiration date: " << endl;
		int d = 1;
		int m, y;
		//test if legal d/m/y
		cout << endl << "Month (from " << MINinput << " to " << MAX_MONTH << "): ";
		cin >> m;
		cout << endl << "Year (from " << CURRENT_YEAR << " to " << MAX_YEAR << "): ";
		cin >> y;
		//bigger or equal to today
		if (!legalInput(d, m, y)) {
			flag = true;
			cout << "invalid date, please try again." << endl;
		}
	} while (flag);
	
	//cvv
	do {
		flag = false;
		cout << "CVV must be exactly  " << CVV << " digits, numbers only." << endl;
		cout << "Please enter your credit card's CVV: " << endl;
		cin.ignore();
		getline(cin, buffer);
		if (!(buffer.length() == CVV)) flag = true;
		if (!isStringAllDig(buffer)) flag = true;
		if (flag) cout << "Incorrect input, try again." << endl;
	} while (flag);

	orderConfirmation(l, d, a, trv_index);
}
//bool creditCardValidation(const string cardNumber, const string expirationMonth, const string expirationYear, const string cvv, const string ownerID)
//{
//	time_t t = time(0);
//	tm* now = localtime(&t);
//
//	if (!isStringAllDig(cardNumber) || cardNumber.length() != 16) return false;//check card number
//	if (!isStringAllDig(expirationYear) || stoi(expirationYear) < (now->tm_year + 1900) || (stoi(expirationYear) + 1900) > 9999) return false;//check expiration year
//	if ((stoi(expirationYear) == now->tm_year + 1900) && (!isStringAllDig(expirationMonth) || stoi(expirationMonth) < (now->tm_mon + 1) || stoi(expirationMonth) > 12)) return false;//check expiration month if expiration year is current year
//	if (!isStringAllDig(expirationMonth) || stoi(expirationMonth) < 0 || stoi(expirationMonth) > 12) return false;//check expiration month otherwise
//	if (!isStringAllDig(cvv) || cvv.length() != 3) return false;//check cvv
//	if (!isStringAllDig(ownerID) || ownerID.length() != 9) return false;//check ID
//
//	return true;//if nothing wrong was found
//}

//-------------print deal confirmation(to screen)
void orderConfirmation(landlord* l, date* d, ad* a, int trv_index)
{
	//generate random order number
	srand(time(NULL));
	int num = rand() % 100 + 1234;     // num in the range 1234 to 1334
	int total = 0;
	a = findAdFromLandlord(a);
	if (!difference_of_days(d->fromDay, d->fromMonth, d->fromYear, d->toDay, d->toMonth, d->toYear))
		total = 1 * (a->price - a->discount);
	else 
		total = difference_of_days(d->fromDay, d->fromMonth, d->fromYear, d->toDay, d->toMonth, d->toYear) * (a->price - a->discount);

	system("CLS");
	cout << endl << " ---ORDER CONFIRMATION---" << endl
		<< "Your order is complete!" << endl;
	cout << "Payment proccess has been successful" << endl;
	cout << "Order Number: " << num << endl;
	cout << "Dates From: " << d->fromDay << "/" << d->fromMonth << "/" << d->fromYear << " To: " << d->toDay << "/" << d->toMonth << "/" << d->toYear << endl;
	cout << "Total price: " << total << " NIS" << endl;
	cout << "Landlord Details:" << endl;
	cout << "NAME: " << l->fullName << endl;
	cout << "PHONE NUMBER: " << l->phoneNumber << endl;
	cout << ADSBREAK << endl;
	occupyDates(*d, a);//occupy dates in ad
	travelers_arr[trv_index].order = *d;//occupy dates in traveler order field
	travelers_arr[trv_index].index = a->index;
	travelers_arr[trv_index].landlord_name = l->fullName;
	l->sumOfDeals += total;//update sum of deals
	printToFile();
	readFromFile();
}

ad* findAdFromLandlord(ad* a) {
	for (int i = 0; i < landlord_arr_size; ++i) {
		if (landlord_arr[i].email == a->email) {
			for (int j = 0; j < landlord_arr[i].adSize; ++j) {
				if (landlord_arr[i].properties[j].description == a->description)
					if (compareAmenities(landlord_arr[i].properties[j].ameNities, a->ameNities))
						if (landlord_arr[i].properties[j].price == a->price)
							if (landlord_arr[i].properties[j].discount == a->discount)
								if (landlord_arr[i].properties[j].rating == a->rating)
									return &landlord_arr[i].properties[j];
			}
		}
	}
	return a;
}
//-------------support(print only)
void printSupport()
{
	//generate random case number
	srand(time(NULL));
	int num = rand() % 100 + 2567;     // num in the range 2567 to 2667
	system("CLS");
	cout << endl << "--- SUPPORT ---" << endl
		<< "Your request has been sent!" << endl
		<< "Case number :" << num << endl
		<< "had been opened with your request for support" << endl << ADSBREAK << endl;
}

//-------------faq(print only)
void printFaq()
{
	system("CLS");
	cout << endl << "--- FAQ ---" << endl
		<< "THE SOFTWARE IS NOT WORKING PROPERLY, HOW DO I FIX IT?" << endl
		<< "Please try using a different device and if there is no improvement try to reset your router." << endl << endl
		<< "IS THE SITE SECURE ?" << endl
		<< "Yes, the company uses a security company in order to secure all your personal information." << endl << endl
		<< "HOW DO I RATE MY STAY ?" << endl
		<< "At the end of rent time a rating screen will be available in which you can rate your stay." << endl << ADSBREAK << endl;
}

//-------------travelers homepage
void travelerMenu(int trv_index)
{
	bool support = false;//can't request support twice
	int choice = 1;
	int res = 0;
	date chosenDates = { 0,0,0,0,0,0 };
	travelerExplore();
	while (choice)
	{
		cout << endl << "****WELCOME TRAVELER!****" << endl
			<< "Find the best place for your next vacation!" << endl
			<< "This is your basic menu-Please choose how you wish to proceed:" << endl
			<< "-------------------------------" << endl
			<< "1. Explore- displays all ads in default order." << endl
			<< "2. Enter specific dates to sort by." << endl
			<< "3. Search by location." << endl
			<< "4. Filter ads." << endl
			<< "5. Sort ads." << endl
			<< "6. Clear all my filters, searches and sorts." << endl
			<< "7. FAQ." << endl
			<< "8. Support." << endl
			<< "9. Rate." << endl
			<< "0. LOG OUT." << endl
			<< "-------------------------------" << endl;
		cout << "-> We recommend you first enter location and/or dates." << endl
			<< "-> At any stage you can return here and use different sorting/filtering options." << endl
			<< "===============================" << endl
			<< "Please enter your choice: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			travelerExplore();
			res = printAndChooseFromAdArr();//prints all ads
			if (res != NOT_FOUND)
				placeOrder(ad2Arr[res], chosenDates, trv_index);
			break;
		case 2://sort by dates.
			if (!ad2size) // no ads qualified previous filters
				cout << "No ads with the previous filters match your description." << endl
					<< "Clear all filters and try again." << endl;
			else {
				chosenDates = sortAdsByDate();
				res = printAndChooseFromAdArr();//prints all ads
				if (res != NOT_FOUND)
					placeOrder(ad2Arr[res], chosenDates, trv_index);
			}
			break;
		case 3://sort by location.
			if (!ad2size) // no ads qualified previous filters
				cout << "No ads with the previous filters match your description." << endl
					<< "Clear all filters and try again." << endl;
			else {
				searchAds();
				res = printAndChooseFromAdArr();//prints all ads
				if (res != NOT_FOUND)
					placeOrder(ad2Arr[res], chosenDates, trv_index);
			}
			break;
		case 4://filter ads.
			if (!ad2size) // no ads qualified previous filters
				cout << "No ads with the previous filters match your description." << endl
				<< "Clear all filters and try again." << endl;
			else{
				filterAds();
				res = printAndChooseFromAdArr();//prints all ads
				if (res != NOT_FOUND)
					placeOrder(ad2Arr[res], chosenDates, trv_index);
			}
			break;
		case 5://sort ads.
			if (!ad2size) // no ads qualified previous filters
				cout << "No ads with the previous filters match your description." << endl
				<< "Clear all filters and try again." << endl;
			else {
				sortMenu(chosenDates, trv_index);
			}
			break;
		case 6://clear filters. 
			deleteAd2Arr();
			ad2size = NOT_FOUND;
			chosenDates = { 0,0,0,0,0,0 };
			system("CLS");
			cout << "\nAll clear!" << endl;
			travelerExplore();
			break;
		case 7://faq.
			printFaq();
			break;
		case 8://Support.
			if (!support) 
			{
				printSupport();
				support = true;
			}
			else cout << "You can request support only once!" << endl;
			break;
		case 9://Rate.
			if (isDateInitialized(travelers_arr[trv_index].order)) {
				cout << "No order yet..." << endl;
				break;
			}
			else if (!travelers_arr[trv_index].rate) {
				rateProperty(trv_index);
			}
			else
				cout << "You can rate only ONCE." << endl;
			break;
		case 0://exit
			system("CLS");
			cout << "\nTHANK YOU! Logging out...\n" << endl;
			break;
		}
	}
}
//-------------sort menu
void sortMenu(date chosenDates, int trv_index) {
	int choice = 1;
	int res = NOT_FOUND;
	while (choice != 0)
	{
		cout << "\n***SORT ADS - MENU***:" << endl//need to be changed! add beutiful header.
			<< "1. Sort ads by DATE." << endl
			<< "2. sort ads by PRICE- low to high." << endl
			<< "3. sort ads by PRICE- high to low." << endl
			<< "4. sort ads by POPULARITY (default)." << endl
			<< "0. Back." << endl
			<< "Please enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			sortAdsByDate();
			res = printAndChooseFromAdArr();//prints all ads
			if (res != NOT_FOUND)
				placeOrder(ad2Arr[res], chosenDates, trv_index);

			break;
		case 2:
			bubbleSort(1);
			res = printAndChooseFromAdArr();//prints all ads
			if (res != NOT_FOUND)
				placeOrder(ad2Arr[res], chosenDates, trv_index);
			break;
		case 3:
			bubbleSort(2);
			res = printAndChooseFromAdArr();//prints all ads
			if (res != NOT_FOUND)
				placeOrder(ad2Arr[res], chosenDates, trv_index);
			break;
		case 4:
			res = printAndChooseFromAdArr();//prints all ads
			if (res != NOT_FOUND)
				placeOrder(ad2Arr[res], chosenDates, trv_index);
			bubbleSort();
			break;
		case 0:
			break;
		default:
			cout << "Wrong choice!! Try again: ";
			break;
		}
	}
}

//-------------place order
void placeOrder(ad* a, date& d, int trv_index) {
	if (!isDateInitialized(travelers_arr[trv_index].order)) {
		cout << "You can have only one order at a time." << endl;
		return;
	}
	if (isDateInitialized(d)) //if date was not set
		d = validDateInput(); //set date
	
	for (int i = 0; i < a->dateSize; ++i) {//if dates unavilable
		if (!isDateAvailable(d, a->occupied[i])) {
			cout << "these dates are occupied, please try again." << endl;
			return;
		}
	}
	//if dates available
	landlord* l = findLandlordByEmail(a);//find landlord address
	if (!l) {
		cout << "unknown error! please try again." << endl;
		return;
	}
	int total = 0;
	if (!difference_of_days(d.fromDay, d.fromMonth, d.fromYear, d.toDay, d.toMonth, d.toYear))
		total = 1 * (a->price - a->discount);
	else
		total = difference_of_days(d.fromDay, d.fromMonth, d.fromYear, d.toDay, d.toMonth, d.toYear) * (a->price - a->discount);
	cout << "The total price is: " << total << " NIS" << endl
		<< "procceding to payment..." << endl;
	validCreditCard(l, &d, trv_index, a);//gets credit card details
}

landlord* findLandlordByEmail(ad* a) {
	for (int i = 0; i < landlord_arr_size; ++i) {
		if (a->email == landlord_arr[i].email)
			return &landlord_arr[i];
	}
	return NULL;
}

bool isDateInitialized(date& d) {//if date has zeros
	if (!d.fromDay || !d.fromMonth || !d.fromYear || !d.toDay || !d.toMonth || !d.toYear)
		return true;
	return false;
}//true if no set date

ad* findAdByOccupiedDates(date& d) {
	for (int i = 0; i < landlord_arr_size; ++i) {
		for (int j = 0; j < landlord_arr[i].adSize; ++j) {
			for (int k = 0; k < landlord_arr[i].properties[j].dateSize; ++k) {
				if (isDateEqual(d, landlord_arr[i].properties[j].occupied[k]))
					return &landlord_arr[i].properties[j];//if found return ad
			}
		}
	}
	return NULL;
}
//-------------rate property(on last rent day)
//-------------calculate and update rates
void rateProperty(int trv_index)
{
	system("CLS");
	//ad* a = findAdByOccupiedDates(travelers_arr[trv_index].order);
	landlord* l = findLandlordByName(travelers_arr[trv_index].landlord_name);
	if (!landlord_arr) {
		cout << "sorry! we couldn't find your order..." << endl;
		return;
	}
	if(l->adSize < travelers_arr[trv_index].index){///
		cout << "sorry! we couldn't find your order..." << endl;
		return;
	}
	ad* a = &(l->properties[travelers_arr[trv_index].index]);
	//a = findAdFromLandlord(a);
	time_t t = time(ZERO);
	tm* now = localtime(&t);//checks if date is right
	traveler* trv = &travelers_arr[trv_index];
	if (!isDateSmallerE(trv->order.toDay, trv->order.toMonth, trv->order.toYear, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900)) {
		cout << "\nRating is available only from the last day of your stay..." << endl
			<< "We appreciate your opinion, try again when the time is right." << endl;
		return;
	}
	int temp;
	cout << "--- RATE ---" << endl;
	do
	{
		cout << "Please rate the experience on a property by entering 1-5 " << endl
			<< "1 being the lowest and 5 the highest, 0 to go back" << endl;
		cin >> temp;
	} while ((temp < 1 || temp > 5) && temp);//updates ad rating
	if (!temp)
		return;
	a->rating = (a->rating + temp) / 2;
	cout << "New ad rating: " << a->rating << endl;
	cout << "Thank you!" << endl;
	trv->rate = true;
}

//-------------prints ad for traveler(to screen)
int printAndChooseFromAdArr() {//*********************************************
	//print for TRAVELER to choose from
	if (!ad2size) {
		cout << "\nNo ads matched your requirements..." << endl;
		return NOT_FOUND;
	}
	cout << endl;
	for (int i = 0; i < ad2size; ++i) {
		cout << "  \tAD NUMBER " << i + 1 << " :" << endl
			<< "**==============================**" << endl;
		cout << "Ad description: " << ad2Arr[i]->description << endl;
		cout << "Price before discount: " << ad2Arr[i]->price << endl;
		cout << "Price after discount:  " << ad2Arr[i]->price - ad2Arr[i]->discount << endl;
		cout << "Discount: " << "-" << ad2Arr[i]->discount << " NIS" << endl;
		cout << "Location: " << ad2Arr[i]->location << endl;
		cout << "Number of People: " << ad2Arr[i]->numOfPeople << endl
			<< "Number of Rooms: " << ad2Arr[i]->numOfRooms << endl
			<< "Number of Beds: " << ad2Arr[i]->numOfBeds << endl;
		PrintAmenities(ad2Arr[i]->ameNities);
		cout << "Atractions: " << ad2Arr[i]->attraction << endl;
		cout << "Landlord Email: " << ad2Arr[i]->email << endl;
		cout << "Rating: " << ad2Arr[i]->rating << endl;
		cout << "**==============================**" << endl;
	}
	cout << "To choose an ad press the ad number" << endl
		<< "To Exit press 0" << endl;
	cout << "enter your choice: " << endl;
	int choice = 0;
	cin >> choice;
	if (choice < 0 || choice > ad2size) {
		choice = 0;
		cout << "\n No such ad..." << endl;
	}
	if (!choice)
		return NOT_FOUND;//doesn't want to order yet
	return choice - 1;
}
//-------------3 funcs: isLeap, DaysCountFrom1900, DateDaysCount calculates the days from start date to end date.
bool isLeap(int Y)
{
	if (Y % 400 == 0) return true;
	else if (Y % 100 == 0) return false;
	else if (Y % 4 == 0) return true;
	else return false;
}
int DaysCountFrom1900(int year, int month, int day)
{
	int ans = 0;
	for (int i = 1900; i < year; ++i)
		if (isLeap(i))ans += 366;
		else ans += 365;
	for (int i = 1; i < month; ++i) {
		switch (i) {
		case 1: ans += 31; break;
		case 2: ans += isLeap(year) ? 29 : 28; break;
		case 3: ans += 31; break;
		case 4: ans += 30; break;
		case 5: ans += 31; break;
		case 6: ans += 30; break;
		case 7: ans += 31; break;
		case 8: ans += 31; break;
		case 9: ans += 30; break;
		case 10: ans += 31; break;
		case 11: ans += 30; break;
		case 12: ans += 31; break;
		}
	}
	return ans += day - 1;
}
int difference_of_days(int day1, int month1, int year1, int day2, int month2, int year2)
{
	return abs(DaysCountFrom1900(year1, month1, day1) - DaysCountFrom1900(year2, month2, day2));
}

//-------------Landlords menu : sub fuction- realloc the the ads array and adds 1 more ad.
//-------------landlord homescreen
//-------------Landlords menu : prints list of ads for landlord(to screen)

landlord* findLandlordByName(string name) {
	if (!isStringAllLetters(name))
		return NULL;
	for (int i = 0; i < landlord_arr_size; ++i) {
		if (landlord_arr[i].fullName == name)
			return &landlord_arr[i];
	}
	return NULL;
}

bool isDateBiggerE(int d, int m, int y, int dd, int mm, int yy) {//--------------------------
	//gets two dates checks if the 1st is bigger or equal
	if (y == yy && m == mm && d == dd)
		return true;
	if (y > yy)
		return true;
	else if (y == yy) {
		if (m > mm)
			return true;
		else if (m == mm) {
			if (d > dd)
				return true;
		}
	}
	return false;//first date is not bigger or equal
}

bool isDateSmallerE(int d, int m, int y, int dd, int mm, int yy) {//--------------------------
	//gets two dates checks if the 1st is equal
	if (y == yy && m == mm && d == dd)
		return true;
	if (y < yy)
		return true;
	else if (y == yy) {
		if (m < mm)
			return true;
		else if (m == mm) {
			if (d < dd)
				return true;
		}
	}
	return false;//first date is not equal
}

bool isDateEqual(date& d, date& adDate) {//--------------------------
	//gets two dates checks if the 1st is bigger or equal
	if (d.fromDay == adDate.fromDay && d.fromMonth == adDate.fromMonth && d.fromYear == adDate.fromYear
		&& d.toDay == adDate.toDay && d.toMonth == adDate.toMonth && d.toYear == adDate.toYear)
		return true;
	return false;//dates aren't equal
}

string strToLower(string a) 
{	//converts entire string to lowerCase
	for (int i = 0; i < a.length(); ++i)
		a[i] = tolower(a[i]);
	return a;
}

bool iequalsContain(const string& a, const string& b)//*************************************
{//compare strings, insenstive to lower/upper case

	//a bigger
	//firstly check if equal
	if (iequals(a, b))
		return true;
	//else create new lowercase strings
	string a1, b1;
	a1 = strToLower(a);
	b1 = strToLower(b);
	//check if b1 is subtring of a1
	for (int i = 0; i < a1.length() && b1.length(); ++i)
		if (a1[i] != b1[i])
			return false;
	return true;
}

void swap(ad** ad1, ad** ad2)//***********************************************************
{
	//swap ads in ad2Arr
	ad** temp = ad1;
	ad1 = ad2;
	ad2 = temp;
}


//---------------------Checked and Works-------------------------
void deleteAllocatedData()
{
	for (int i = 0; i < landlord_arr_size; i++)
	delete[] landlord_arr[i].properties;//free each landlord's ad array
	delete[] landlord_arr;//free landlord array
	delete[] travelers_arr;//free traveler array
	delete[] ads_arr;
	landlord_arr = NULL;
	landlord_arr_size = 0;
	travelers_arr = NULL;
	travelers_arr_size = 0;
	ads_arr = NULL;
	ads_arr_size = 0;
}

void deleteAd2Arr() {
	delete[] ad2Arr;
	ad2Arr = NULL;
	ad2size = NOT_FOUND;
}

//Register:
//void Register()
//{
//	system("CLS");
//	int choise = 1;
//	bool flag = true;
//	cout << "***REGISTER - MENU***" << endl
//		<< "1) Landlord." << endl
//		<< "2) Traveler." << endl
//		<< "3) Back." << endl
//		<< "Please enter your choice: ";
//	cin >> choise;
//	if (choise == 1)
//	{
//		RegisterLandlord();
//		//update db
//		system("CLS");
//		cout << "Landlord successfuly added!" << endl;
//	}
//	else if (choise == 2)
//	{
//		RegisterTraveler();
//		//update db
//		system("CLS");
//		cout << "Traveler added successfuly!" << endl;
//	}
//	else if (choise == 3) return;
//	else cout << "Wrong choice!!" << endl;
//}

//Register:
void Register()
{
	system("CLS");
	int choise = 1;
	bool flag = true;
	cout << "\n***REGISTER - MENU***" << endl
		<< "1) Landlord." << endl
		<< "2) Traveler." << endl
		<< "3) Back." << endl
		<< "Please enter your choice: ";
	cin >> choise;
	if (choise == 1)
	{
		RegisterLandlord();
		//update db
		system("CLS");
		cout << "Landlord added successfuly !" << endl;
		printToFile();
		readFromFile();
	}
	else if (choise == 2)
	{
		RegisterTraveler();
		//update db
		system("CLS");
		cout << "Traveler added successfuly!" << endl;
		printToFile();
		readFromFile();
	}
	else if (choise == 3) return;
	else cout << "Wrong choice!!" << endl;
}

traveler NewTraveler()
{
	traveler trv;
	trv.fullName = NameInput();
	trv.phoneNumber = PhoneInput();
	trv.password = PasswordInput();
	//cout << "NewTraveler: " << trv.fullName << endl;
	//cout << "NewTraveler: " << trv.phoneNumber << endl;
	//cout << "NewTraveler: " << trv.password << endl;;
	return trv;
}

void RegisterTraveler()
{
	RealloctravelersArr();
	travelers_arr[travelers_arr_size - 1] = NewTraveler();
	//cout <<endl<<"dd: "<< trv->password;
	//cout << travelersArr[size - 1].phoneNumber;
}

void RegisterLandlord()
{
	RegisterTraveler();
	landlord newLandlord;
	newLandlord.fullName = travelers_arr[travelers_arr_size - 1].fullName;
	newLandlord.phoneNumber = travelers_arr[travelers_arr_size - 1].phoneNumber;
	newLandlord.password = travelers_arr[travelers_arr_size - 1].password;
	newLandlord.id = ValidId();
	newLandlord.email = ValidEmail();
	newLandlord.sumOfDeals = 0;
	newLandlord.adSize = 0;
	ReallocLandlordsArr();
	landlord_arr[landlord_arr_size - 1] = newLandlord;
}

//Sign-in funcs:
int landlordSignIn() {//returns true if login successful
	string tempId, tempPass;
	cout << "\n***LANDLORD - LOG IN***" << endl << "Please enter details according to instructions" << endl;
	//get id input
	cout << "ID must be exactly " << MAX_ID << " digits, numbers only." << endl;
	cout << "Please enter your ID: " << endl;
	cin >> tempId;
	//check length and input correctness
	if (tempId.length() != MAX_ID) {
		cout << "No such ID..." << endl;
		return NOT_FOUND;
	}
	//find index for landlord in array by id- assuming no two identical id's
	int index = findLandlordById(tempId);
	if (index == NOT_FOUND) {//landlord not found
		cout << "No such ID..." << endl;
		return NOT_FOUND;
	}

	//get password
	cout << "\nPlease enter your password- " << MIN_PASSWORD << " to " << MAX_PASSWORD << " characters." << endl;
	cout << "PASSWORD: ";
	cin >> tempPass;
	//check length and input correctness
	if (tempPass.length() > MAX_PASSWORD || tempPass.length() < MIN_PASSWORD) {
		cout << "Incorrect password...try again." << endl;
		return NOT_FOUND;
	}
	if (tempPass != landlord_arr[index].password) {//password equal
		cout << "Incorrect password...try again." << endl;
		return NOT_FOUND;
	}
	return index;
}

int findLandlordById(string id) {
	for (int i = 0; i < landlord_arr_size; ++i) {
		if (landlord_arr[i].id == id)//if equal
			return i;
	}
	return NOT_FOUND;
}

int travelerSignIn() {
	string tempName, tempPass;
	cout << endl << "\n***TRAVELER - LOG IN***" << endl
		<< "-------------------------" << endl;
	//get name input
	cout << "Please enter your full name- " << MAX_NAME << " letters MAX." << endl;
	cout << "FULL NAME: ";

	//cin >> tempName;
	cin.ignore();
	getline(cin, tempName);
	//check length and input correctness
	if (tempName.length() > MAX_NAME) {
		cout << "\nNo such user..." << endl;
		return NOT_FOUND;
	}
	//find index for traveler in array by name- assuming no two identical names
	int index = findTravelerByName(tempName);
	if (index == NOT_FOUND) {//traveler not found
		cout << "\nNo such user..." << endl;
		return NOT_FOUND;
	}

	//get password
	cout << "\nPlease enter your password- " << MIN_PASSWORD << " to " << MAX_PASSWORD << " characters." << endl;
	cout << "PASSWORD: ";
	cin >> tempPass;
	//check length and input correctness
	if (tempPass.length() > MAX_PASSWORD || tempPass.length() < MIN_PASSWORD) {
		cout << "\nIncorrect password...try again." << endl;
		return NOT_FOUND;
	}
	if (tempPass != travelers_arr[index].password) {//password equal
		cout << "\nIncorrect password...try again." << endl;
		return NOT_FOUND;
	}
	return index;
}

int findTravelerByName(string name)
{
	for (int i = 0; i < travelers_arr_size; ++i) {
		if (travelers_arr[i].fullName == name)//traveler found
			return i;
	}
	return NOT_FOUND;
}

//input validation:
bool isStringAllDig(string str) {//check id the string is all digits
	for (int i = 0; i < str.length(); ++i) {
		if (!isdigit(str[i]))//if false
			return false;
	}
	return true;
}

bool isStringAllLetters(string str)
{
	for (int i = 0; i < str.length(); ++i)
		if (!isalpha(str[i]) && str[i] != ' ')
			return false;
	return true;
}

string ValidLocation()
{
	//Location format <city>, <street> st.
	string location = "";
	string tmp;
	char answer;
	cout << "Please enter city: ";
	cin.ignore();
	getline(cin, tmp);
	location += tmp;
	cout << "Do you want to enter address?" << endl << "'y' for yes, else for no: ";
	cin >> answer;
	if (answer == 'y')
	{
		cout << "Please enter street name: ";
		cin.ignore();
		getline(cin, tmp);
		location += ", " + tmp + " st.";
	}
	else location += ".";
	return location;
}
int ValidInput()
{
	char x;
	cin >> x;
	return int(x) - 48;
}

int ValidInput(int min, int max)
{
	//gets int as input from user: (min <= USER_INPUT <= max)
	//if wrong gets another one and prints error message.
	//int num = ValidInput();---------------makes problem with filling ad
	int num;
	cin >> num;
	while (num < min || num >max)
	{
		cout << "Wrong number!\n Must be: " << min << " <= YOUR_NUMBER <= " << max << ": " << endl;
		cin >> num;
	}
	return num;
}

bool ValidInput(char truevaluechar)
{//returns true for 'truevaluechar' else return false.
	char tmp;
	cin >> tmp;
	if (tmp == truevaluechar) return true;
	else return false;
}

bool ValidInput(int num, int min, int max)//--------------------------------------------
{
	//gets int as input from user: (min <= USER_INPUT <= max)
	if (num < min || num >max) {
		cout << "Wrong input!\n Must be: " << min << " <= YOUR_INPUT <= " << max << ". " << endl;
		return false;
	}
	return true;
}

string NameInput()
{
	bool flag;
	string buffer;
	do {
		flag = false;
		cout << "Name must be up to  " << MAX_NAME << " letters only." << endl;
		cout << "Please enter your full name: " << endl;
		cin.ignore();
		getline(cin, buffer);
		if (!(buffer.length() <= MAX_NAME && buffer.length() > 0)) flag = true;
		if (!isStringAllLetters(buffer)) flag = true;
		if (flag) cout << "Incorrect input, try again." << endl;
	} while (flag);
	return buffer;
}

string PhoneInput()
{
	bool flag;
	string buffer;
	do {
		flag = false;
		cout << "Phone number must be exactly " << MAX_PHONE << " digits, no spaces, numbers only." << endl;
		cout << "Please enter your phone number: " << endl;
		getline(cin, buffer);
		if (buffer.length() != MAX_PHONE) flag = true;
		if (!isStringAllDig(buffer)) flag = true;
		if (flag) cout << "Incorrect length, try again." << endl;
	} while (flag);
	return buffer;
}

string PasswordInput()
{
	bool flag;
	string buffer;
	do {
		flag = false;
		cout << "Password can be minimum: " << MIN_PASSWORD
			<< " characters and maximum: " << MAX_PASSWORD << " characters," << endl
			<< "Can contain any characters you wish except 'enter'." << endl;
		cout << "Please enter your password: " << endl;
		getline(cin, buffer);
		//check length and input correctness
		if (buffer.length() < MIN_PASSWORD || buffer.length() > MAX_PASSWORD) flag = true;
		if (flag) cout << "Incorrect length, try again." << endl;
	} while (flag);
	return buffer;
}

//string ValidId()
//{
//	string id;
//	bool has_only_digits = false;
//	while (!has_only_digits)
//	{
//		cout << "Please enter id(9 digits): ";
//		cin >> id;
//		has_only_digits = true;
//		for (int i = 0; i < id.length(); i++)
//			if (!isdigit(id[i])) has_only_digits = false;
//		if (!has_only_digits) cout << "Wrong id! Please try again!" << endl;
//	}
//	return id;
//}

string ValidId()
{
	string id;
	bool has_only_digits = false;
	while (!has_only_digits)
	{
		cout << "Please enter id(9 digits): ";
		cin >> id;
		if (id.length() != MAX_ID) cout << "Wrong id! Please try again!" << endl;
		else
		{
			has_only_digits = true;
			for (int i = 0; i < id.length(); i++)
				if (!isdigit(id[i])) has_only_digits = false;
			if (!has_only_digits) cout << "Wrong id! Please try again!" << endl;
		}
	}
	return id;
}

string ValidEmail()
{
	/// gets a valid email form from user.
	string email;
	bool at = false, dot = false;
	while (!at || !dot)
	{
		at = false;
		dot = false;
		cout << "Please enter email: ";
		cin >> email;
		for (int i = 0; i < email.length(); i++)
		{
			if (email[i] == '@') at = true;
			if (at && email[i] == '.') dot = true;
		}
		if (!at || !dot) cout << "Wrong email! Please try again!" << endl;
	}
	return email;
}

amenities amenitiesCtor()
{//User input for each amenity.
	amenities obj;
	cout << "enter 'y' for yes, other for no" << endl;
	cout << AMENITIES_NAMES[0] << ": ";
	obj.disabledAccess = ValidInput('y');
	cout << AMENITIES_NAMES[1] << ": ";
	obj.wifi = ValidInput('y');
	cout << AMENITIES_NAMES[2] << ": ";
	obj.kitchen = ValidInput('y');
	cout << AMENITIES_NAMES[3] << ": ";
	obj.tv = ValidInput('y');
	cout << AMENITIES_NAMES[4] << ": ";
	obj.balcony = ValidInput('y');
	cout << AMENITIES_NAMES[5] << ": ";
	obj.washingMachine = ValidInput('y');
	cout << AMENITIES_NAMES[6] << ": ";
	obj.airConditioning = ValidInput('y');
	cout << AMENITIES_NAMES[7] << ": ";
	obj.swimmingPool = ValidInput('y');
	cout << AMENITIES_NAMES[8] << ": ";
	obj.parkingLot = ValidInput('y');
	return obj;
}

////***************also looped menus and instructions in each screen***************

//Menus:
void MainPage()
{
	//system("CLS");
	int landlord_index = NOT_FOUND;
	int traveler_index = NOT_FOUND;
	int choise = 1;
	while (choise != 0)
	{
		cout << "\n***MAIN - MENU***:" << endl//need to be changed! add beutiful header.
			<< "1) Log in as traveler." << endl
			<< "2) Log in as landlord." << endl
			<< "3) Register." << endl
			<< "0) Exit." << endl
			<< "Please enter your choice: ";
		cin >> choise;
		switch (choise)
		{
		case 1:
			traveler_index = travelerSignIn();
			if(traveler_index!=NOT_FOUND)
				travelerMenu(traveler_index);
			break;
		case 2:
			landlord_index = landlordSignIn();
			if (landlord_index == NOT_FOUND)
				break;
			
			traveler_index = findTravelerByName(travelers_arr[landlord_index].fullName);/////
			if (traveler_index == NOT_FOUND)	
				break;
			LandlordsLoginMenu(landlord_index, traveler_index);
			break;
		case 3:
			Register();
			break;
		case 0:
			system("CLS");
			cout << "\nGood bye!\n";
			break;
		default:
			cout << "Wrong choice!!\nTry again: ";
			break;
		}

	}
}

void LandlordsLoginMenu(int ll_index, int trv_index)
{
	int choise = 1;
	while (choise != 0)
	{
		cout << "Please select user type:" << endl
			<< "1) Landlord." << endl
			<< "2) Traveler." << endl
			<< "0) LOG OUT." << endl
			<< "Please enter your choice:" << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			LandlordsMenu(ll_index);
			break;
		case 2:
			travelerMenu(trv_index);
			break;
		case 0:
			system("CLS");
			cout << "\nTHANK YOU! Logging out...\n" << endl;
			break;
		default:
			cout << "Wrong choice!!\nTry again: ";
			break;
		}

	}
}

//void LandlordsMenu(int index)
//{
//	int choise = 1;
//	int input;
//	while (choise != 4)
//	{
//		system("CLS");
//		cout << "****LANDLORD - MENU****" << endl;
//		cout << "Total profit: " << landlord_arr[index].sumOfDeals << endl;
//		if (landlord_arr[index].adSize)
//			for (int i = 0; i < landlord_arr[index].adSize; i++)
//			{
//				cout << ADSBREAK << endl << "\tAd no: " << i + 1 << endl;
//				PrintAd(landlord_arr[index].properties[i]);
//			}
//		cout << ADSBREAK << endl;
//
//		cout << "Please select an option:" << endl
//			<< "1) Edit an ad." << endl
//			<< "2) Add new ad." << endl
//			<< "3) Delete an ad." << endl
//			<< "4) Back." << endl
//			<< "enter your choice: ";
//		cin >> choise;
//		switch (choise)
//		{
//		case 1:
//			cout << "Please enter ad number: ";
//			input = ValidInput(1, landlord_arr[index].adSize) - 1;
//			EditAdMenu(index, input);
//			//update db
//			break;
//		case 2:
//			RealocateAdsPointer(index);
//			landlord_arr[index].properties[landlord_arr[index].adSize - 1] = NewAd();
//			landlord_arr[index].properties[landlord_arr[index].adSize - 1].email = landlord_arr[index].email;
//			//update db
//			break;
//		case 3:
//			cout << "Please enter ad number: ";
//			input = ValidInput(1, landlord_arr[index].adSize) - 1;
//			DeleteAd(index, input);
//			//update db
//			break;
//		case 4:
//			//exit
//			system("CLS");
//			break;
//		default:
//			cout << "Wrong choice!!\nTry again!\n ";
//			break;
//		}
//	}
//
//
//}

void LandlordsMenu(int index)
{
	int choise = 1;
	int input;
	while (choise != 0)
	{
		readFromFile();
		cout << "\n***LANDLORD - MENU***" << endl;
		cout << "Total profit: " << landlord_arr[index].sumOfDeals << endl;
		if (landlord_arr[index].adSize)
			for (int i = 0; i < landlord_arr[index].adSize; i++)
			{
				cout << ADSBREAK << endl << "\tAd no: " << i + 1 << endl;
				PrintAd(landlord_arr[index].properties[i]);
			}
		cout << ADSBREAK << endl;
		cout << "Please select an option:" << endl
			<< "1) Edit an ad." << endl
			<< "2) Add new ad." << endl
			<< "3) Delete an ad." << endl
			<< "0) Back." << endl
			<< "enter your choice: ";
		cin >> choise;
		switch (choise)
		{
		case 1:
			if (!landlord_arr[index].adSize) {
				cout << "No ads yet..." << endl;
				break;
			}
			cout << "Please enter ad number: ";
			input = ValidInput(1, landlord_arr[index].adSize) - 1;
			EditAdMenu(index, input);
			//update db
			printToFile();
			readFromFile();
			break;
		case 2:
			RealocateAdsPointer(index);
			landlord_arr[index].properties[landlord_arr[index].adSize - 1] = NewAd();
			landlord_arr[index].properties[landlord_arr[index].adSize - 1].email = landlord_arr[index].email;
			//update db
			printToFile();
			readFromFile();
			break;
		case 3:
			if (!landlord_arr[index].adSize) {
				cout << "No ads yet..." << endl;
				break;
			}
			cout << "Please enter ad number: ";
			input = ValidInput(1, landlord_arr[index].adSize) - 1;
			DeleteAd(index, input);
			//update db
			printToFile();
			readFromFile();
			break;
		case 0:
			//exit
			system("CLS");
			break;
		default:
			cout << "Wrong choice!! Try again!\n ";
			break;
		}
	}
}

void EditAdMenu(int ll_index, int ad_index)
{
	int choose = 1;
	while (choose)
	{
		system("CLS");
		cout << "---EDIT AD MENU--- \nYour ad:" << endl;
		PrintAd(landlord_arr[ll_index].properties[ad_index]);
		cout << ADSBREAK << endl;
		cout << "What do you want to edit?" << endl;
		cout << "1) Change avilability (now: " << landlord_arr[ll_index].properties[ad_index].available << ")." << endl
			<< "2) Change Description." << endl
			<< "3) Change Price." << endl
			<< "4) Change Discount." << endl
			<< "5) Change num of people." << endl
			<< "6) Change num of rooms." << endl
			<< "7) Change num of beds." << endl
			<< "8) Edit amenities." << endl
			<< "9) Change attractions." << endl
			<< "0) Back." << endl
			<< "Please enter your choice: ";
		choose = ValidInput();
		switch (choose)
		{
		case 1:
			landlord_arr[ll_index].properties[ad_index].available = !landlord_arr[ll_index].properties[ad_index].available;
			break;
		case 2:
			cout << "Enter new description: ";
			cin.ignore();
			getline(cin, landlord_arr[ll_index].properties[ad_index].description);
			break;
		case 3:
			cout << "Enter new price: ";
			landlord_arr[ll_index].properties[ad_index].price = ValidInput(ZERO, INT_MAX);
			break;
		case 4:
			cout << "Enter new discount: ";
			landlord_arr[ll_index].properties[ad_index].discount = ValidInput(ZERO, landlord_arr[ll_index].properties[ad_index].price);
			break;
		case 5:
			cout << "Number of people(up to 30): ";
			landlord_arr[ll_index].properties[ad_index].numOfPeople = ValidInput(1, 30);
			break;
		case 6:
			cout << "Number of rooms(up to 15): ";
			landlord_arr[ll_index].properties[ad_index].numOfRooms = ValidInput(1, 15);
			break;
		case 7:
			cout << "Number of beds(up to 30): ";
			landlord_arr[ll_index].properties[ad_index].numOfBeds = ValidInput(1, 30);
			break;
		case 8:
			cout << "Select amenities: ";
			landlord_arr[ll_index].properties[ad_index].ameNities = amenitiesCtor();
			break;
		case 9:
			cout << "Enter a new attraction:";
			cin.ignore();
			getline(cin, landlord_arr[ll_index].properties[ad_index].attraction);
			break;
		case 0:
			return;
			break;
		default:
			cout << "You entered a wrong choice!!\n Try again: ";
			choose = ValidInput();
			break;
		}
	}
}

//Ads manipulations:
void DeleteAd(int landlord_index, int ad_index)
{
	//delete the ad at [index] location.
	if (!landlord_arr[landlord_index].adSize) cout << "No ads to delete!!!" << endl;
	else
	{
		ad* tmp = new ad[landlord_arr[landlord_index].adSize - 1];
		for (int i = 0, j = 0; i < landlord_arr[landlord_index].adSize - 1; j++, i++)
		{
			if (i == ad_index) j++;
			tmp[i] = landlord_arr[landlord_index].properties[j];
		}
		delete[] landlord_arr[landlord_index].properties;
		landlord_arr[landlord_index].properties = tmp;
		landlord_arr[landlord_index].adSize--;
	}
}


ad NewAd()
{//User input for new ad.
	ad newAd;
	newAd.available = true;
	cout << "\n---NEW AD--- " << endl;
	cout << "Ad description: ";
	cin.ignore();
	getline(cin, newAd.description);
	cout << "Price: ";
	newAd.price = ValidInput(ZERO, INT_MAX);
	cout << "Discount(0 ~ Price): ";
	newAd.discount = ValidInput(ZERO, newAd.price);
	newAd.location = ValidLocation();
	cout << "Number of people(up to 30): ";
	newAd.numOfPeople = ValidInput(1, 30);
	cout << "Number of rooms(up to 15): ";
	newAd.numOfRooms = ValidInput(1, 15);
	cout << "Number of beds(up to 30): ";
	newAd.numOfBeds = ValidInput(1, 30);
	cout << "Atraction: ";
	cin.ignore();
	getline(cin, newAd.attraction);
	cout << "Select amenities: ";
	newAd.ameNities = amenitiesCtor();
	newAd.rating = 5;
	return newAd;
}

//Realloc:
void RealloctravelersArr()
{
	travelers_arr_size++;
	traveler* tmp = new traveler[travelers_arr_size];
	if (!tmp) cout << "Memory allocation failed!" << endl;
	for (int i = 0; i < travelers_arr_size - 1; i++) tmp[i] = travelers_arr[i];
	if (travelers_arr) delete[] travelers_arr;
	travelers_arr = tmp;
}

void ReallocLandlordsArr()
{
	landlord_arr_size++;
	landlord* tmp = new landlord[landlord_arr_size];
	if (!tmp) cout << "Memory allocation failed!" << endl;
	for (int i = 0; i < landlord_arr_size - 1; i++) tmp[i] = landlord_arr[i];
	if (landlord_arr) delete[] landlord_arr;
	landlord_arr = tmp;
}

void RealocateAdsPointer(int landlord_index)
{
	//reallocates the pointer and changes the size:
	ad* tmp;
	tmp = new ad[landlord_arr[landlord_index].adSize + 1];
	for (int i = 0; i < landlord_arr[landlord_index].adSize; i++)
		tmp[i] = landlord_arr[landlord_index].properties[i];
	landlord_arr[landlord_index].adSize++;
	if (landlord_arr[landlord_index].properties) delete[] landlord_arr[landlord_index].properties;
	landlord_arr[landlord_index].properties = tmp;
}

//Output:
void PrintLandlordsAds(landlord ll)
{
	if (!ll.adSize)
	{
		cout << "No ads!" << endl;
		return;
	}
	for (int i = 0; i = ll.adSize; i++)
	{
		PrintAd(ll.properties[i]);
	}
	cout << ADSBREAK << endl;
}

void PrintAmenities(amenities obj)
{
	string str = "Amenities:";
	if (obj.disabledAccess) str += AMENITIES_NAMES[0] + ", ";
	if (obj.wifi) str += AMENITIES_NAMES[1] + ", ";
	if (obj.kitchen) str += AMENITIES_NAMES[2] + ", ";
	if (obj.tv) str += AMENITIES_NAMES[3] + ", ";
	if (obj.balcony) str += AMENITIES_NAMES[4] + ", ";
	if (obj.washingMachine) str += AMENITIES_NAMES[5] + ", ";
	if (obj.airConditioning) str += AMENITIES_NAMES[6] + ", ";
	if (obj.swimmingPool) str += AMENITIES_NAMES[7] + ", ";
	if (obj.parkingLot) str += AMENITIES_NAMES[8] + ", ";
	cout << str << endl;
}

void PrintAd(ad obj)
{
	cout << ADSBREAK << endl;
	cout << "Location: " << obj.location << endl;
	cout << "Ad description: " << obj.description << endl;
	cout << "Price before discount: " << obj.price << endl;
	cout << "Price after discount:  " << obj.price - obj.discount << endl;
	cout << "Discount: " << "-" << obj.discount << " NIS" << endl;
	cout << "Number of people: " << obj.numOfPeople << endl;
	cout << "Number of rooms: " << obj.numOfRooms << endl;
	cout << "Number of beds: " << obj.numOfBeds << endl;
	cout << "Atraction: " << obj.attraction << endl;
	PrintAmenities(obj.ameNities);
}


//void PrintTraveler(traveler trv)
//{
//	cout << ADSBREAK << endl;
//	cout << "fullName: " << trv.fullName << "." << endl
//		<< "phoneNumber: " << trv.phoneNumber << "." << endl
//		<< "password: " << trv.password << "." << endl
//		<< "order: ";
//	printDate(trv.order);
//	cout << ADSBREAK << endl;
//}
//void PrintLandlord(landlord ll)
//{
//	cout << ADSBREAK << endl;
//	cout << "fullName: " << ll.fullName << "." << endl
//		<< "phoneNumber: " << ll.phoneNumber << "." << endl
//		<< "password: " << ll.password << "." << endl
//		<< "id: " << ll.id << "." << endl
//		<< "email: " << ll.email << "." << endl
//		<< "sumOfDeals: " << ll.sumOfDeals << "." << endl
//		<< "adSize: " << ll.adSize << "." << endl;
//	for (int i = 0; i < ll.adSize; i++)
//		PrintAd(ll.properties[i]);
//	cout << ADSBREAK << endl;
//}
//void FilesCheck()
//{
//	cout << ADSBREAK << endl << "\tLandlords:" << endl << ADSBREAK << endl;
//	for (int i = 0; i < landlord_arr_size; i++)
//		PrintLandlord(landlord_arr[i]);
//	cout << ADSBREAK << endl << "\tTravelers:" << endl << ADSBREAK << endl;
//	for (int i = 0; i < travelers_arr_size; i++)
//		PrintTraveler(travelers_arr[i]);
//}

int main()
{
	try {
		readFromFile();//read from file.
		MainPage();
	}
	catch (...) {
		cout << "exception caught in main" << endl;
		printToFile();//push to file.
	}
	printToFile();//push to file.
	deleteAllocatedData();
	deleteAd2Arr();
	return 0;
}

