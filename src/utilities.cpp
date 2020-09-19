/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile

//Vector suggested by utilities.h, maybe should be std::vector?
vector <process_stats> mainVector;

int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {

	ifstream dataFile;
	dataFile.open(filename);

	string currentLine;
	vector<string> currentData;

	mainVector.clear();

	if (dataFile.is_open()){
		while (getline (dataFile, currentLine)) {

			string nextLine;
			currentData.clear();
			stringstream divide(currentLine);

			//push next line of file into vector
			while (getline (divide, nextLine)) {
				currentData.push_back(nextLine);
			}

			process_stats statsToAdd;

			if (currentData.size() == 4) {
				statsToAdd.cpu_time = stoi(currentData[0]);
				statsToAdd.process_number = stoi(currentData[1]);
				statsToAdd.start_time = stoi(currentData[2]);
				statsToAdd.io_time = stoi(currentData[3]);

				mainVector.push_back(statsToAdd);
			}

		}
	}
	else {
		return COULD_NOT_OPEN_FILE;
	}

	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	//Doing this using a bubble sort, learned this in CPSC 420 yesterday
	//Maybe find a way to avoid all the if/else statements

	process_stats valuePlaceholder;

	if (mySortOrder == CPU_TIME) {
		//for (int i = 0; i < mainVector.size() - 1; i++) {
			//for (int j = 0; j < mainVector.size() - i - 1; j++) {
				//if (mainVector[j].cpu_time > mainVector[j + 1].cpu_time) {
					//swap(&mainVector[j], &mainVector[j + 1])
				//}
			//}
		//}
		for (int i = 0; i < mainVector.size(); i++) {
			for (int j = i + 1; j < mainVector.size(); j++) {
				if (mainVector[i].cpu_time > mainVector[j].cpu_time) {
					swap(mainVector[i], mainVector[j]);
				}
			}
		}
	}
	else if (mySortOrder == PROCESS_NUMBER) {
		for (int i = 0; i < mainVector.size(); i++) {
			for (int j = i + 1; j < mainVector.size(); j++) {
				if (mainVector[i].process_number > mainVector[j].process_number) {
					swap(mainVector[i], mainVector[j]);
				}
			}
		}
	}
	else if (mySortOrder == START_TIME) {
		for (int i = 0; i < mainVector.size(); i++) {
			for (int j = i + 1; j < mainVector.size(); j++) {
				if (mainVector[i].start_time > mainVector[j].start_time) {
					swap(mainVector[i], mainVector[j]);
				}
			}
		}
	}
	//IO_TIME, assuming there is no bad data being passed to the method
	else {
		for (int i = 0; i < mainVector.size(); i++) {
			for (int j = i + 1; j < mainVector.size(); j++) {
				if (mainVector[i].io_time > mainVector[j].io_time) {
					swap(mainVector[i], mainVector[j]);
				}
			}
		}
	}
}

process_stats getNext() {
	process_stats myFirst;

	myFirst = mainVector[0];
	mainVector.erase(mainVector.begin());

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return mainVector.size();
}


