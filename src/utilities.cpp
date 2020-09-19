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

}

process_stats getNext() {
	process_stats myFirst;

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return mainVector.size();
}


