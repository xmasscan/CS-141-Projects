#include <iostream> // cout & cin
#include <fstream> // file reading lib
#include <string>
#include <vector>
#include "Utils.h" // custom distance function

using namespace std;

/*
Author: Michael Hanif Khan
Date: 4/1/24

This program sorts through preformatted text files to display and calculate information about grocery stores.
It utilizes public data from a project studying food deserts in Chicago from here: https://github.com/Chicago/food-deserts.
The header file was provided by Professor Mark Hodges for use in CS 141. It contains one function which calculates the distance from the user to any given store, with the relevant credits within.
*/

class Store{
    public:
	string name;
	int squareFeet;
	string size;
	string address;
	string neighborhood;
	// Latitude and Longitude
	// Brief, but similiar to naming convention in Utils.H and common nomenclature.
	double lat;
        double lon;

    // Store constructor. Variable names are self-explanitory.
    Store(string name, int squareFeet, string size, string address, string neighborhood, double lat, double lon){
        // this->variableName = variableName
        // "new" operand allocates required memory for data and returns a pointer, so our objects in code will be pointers.
        this->name = name;
        this->squareFeet = squareFeet;
        this->size = size;
        this->address = address;
        this->neighborhood = neighborhood;
        this->lat = lat;
        this->lon = lon;
    }

    // Getter Functions
    string getName(){ return this->name; }
    int getSquareFeet(){ return this->squareFeet; }
    string getSize(){ return this->size; }
    string getAddress(){ return this->address; }
    string getNeighborhood(){ return this->neighborhood; }
    double getLat(){ return this->lat; }
    double getLon(){ return this->lon; }

};

// File Reading Functions
/*
 * Gets each line of the file and creates a new store with the data.
 * Each line of data can be assumed to be reliably structured similiarly to the Store constructor.
 * That is, the order of data is as follows:
 *  Name, Square Footage, 'Size' (is SF 10,000+?), Address, Neighborhood, Latitude, Longitude.
 */
// Example Line: OLD WORLD MARKET,10001,Large,5129 N BROADWAY,UPTOWN,41.9754754,-87.65969701


// Takes current line of data within file, creates new Store object, returns pointer to new object.
Store* getStores(string filename)
{
    ifstream fileIn;
    fileIn.open(filename);
    
    Store* currentStore = nullptr;

    // Store Object Data
    string storeName;
    string stringFeet; // getline input is string, gets converted afterwards
    string storeSize;
    string storeAddress;
    string storeArea;
    // temp string values of lat and lon bcs of getline input.
    string stringLat;
    string stringLon;

    double storeLat;
    double storeLon;
    int storeFeet;

    // Collecting data from a single line

    getline(fileIn, storeName, ','); // gets store name
    getline(fileIn, stringFeet, ','); // gets square feet
    getline(fileIn, storeSize, ','); // gets store 'size'
    getline(fileIn, storeAddress, ','); // '' address
    getline(fileIn, storeArea, ','); // '' Area
    getline(fileIn, stringLat, ','); // lat
    getline(fileIn, stringLon, ','); // lon

    // converts non-strings from strings
    storeFeet = stoi(stringFeet);
    storeLat = stod(stringLat);
    storeLon = stod(stringLon);

    // Data collection complete!
    // Time to make some objects...
    
    currentStore = new Store(storeName, storeFeet, storeSize, storeAddress, storeArea, storeLat, storeLon);
    return currentStore;
}

// Reads every line in the file, calls getStores() on each line to create a new Store object for every line in a given file.
// Returns a vector of pointers to these Store objects.

vector<Store*> readFile(string filename)
{
	string currentLine = "";
	Store* currentStore = nullptr;
	vector<Store*> storeList;

	ifstream fileIn;
	fileIn.open(filename);
	// Runs while the current file is open; formatted this way so we can neatly close the file when we are done.
	// You gotta clean up after yourself!!!
	if(fileIn.is_open())
	{
		// Reads until the end of the current line, saves current line to 
		while(getline(fileIn, currentLine))
		{
			// the current line of the text file is stored within currentLine.
			// getStores returns a pointer to a new store object created with the appropriate data.
			currentStore = getStores(currentLine);
			// adds the pointer to the current store to a vector containing all stores.
			storeList.push_back(currentStore);
		}
		// Closes the file when we're done :)
		fileIn.close();
	}
        return storeList;
}

int main() 
{
    string filename;
    int choice;
    vector<Store*> storeList;
    
    cout << "Enter filename: " << endl;
    cin >> filename;
    
    // Reads file and compiles information into a vector of Store objects.
    // readFile returns a vector of pointers to Store objects. We will use these 
    storeList = readFile(filename);

    cout << "Select a menu option: " << endl;
    cout << "   1. Display general grocery stores information" << endl;
    cout << "   2. Display neighborhood charts" << endl;
    cout << "   3. Find closest stores" << endl;
    cout << "   4. Search for store by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: ";
 
    cin >> choice;

    switch(choice){
        case 1:

            break;
    }

}

