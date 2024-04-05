#include <iostream> // cout & cin
#include <iomanip> // setprecision and setw :)
#include <fstream> // file reading lib
#include <string>
#include <vector>
#include "Utils.h" // custom distance function

using namespace std;

/*
Author: Michael Hanif Khan
Date: 4/3/24

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

// Neighborhood Class
/*
 * Each Neighborhood has the following traits:
 *      How many stores are in it:
 *              How many LARGE stores are in it.
 *              How many SMALL stores are in it.
 *      Its name.
 */

// NOTE
class Neighborhood
{
    public:
        string name;
        int largeCount;
        int smallCount;
        int totalStores;
    Neighborhood(string name)
    {
        this->name = name;
        this->largeCount = 0;
        this->smallCount = 0;
        this->totalStores = 0;
    }
    // Getters
    string getName(){ return this->name; }
    int getLargeCount(){ return this->largeCount; }
    int getSmallCount(){ return this->smallCount; }
    int getTotalCount(){ return this->totalStores; }
    // Mutators
    void addLarge()
    { 
        this->largeCount = this->largeCount + 1;
        // If you're adding a large store to a neighborhood, you're also just adding a store in general.
        this->totalStores = this->totalStores + 1;
    }
    void addSmall()
    {
        this->smallCount = this->smallCount + 1;
        this->totalStores = this->totalStores + 1;
    }

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
Store* getStores(string currentLine)
{
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
    // This function deals with the current line which is assumed to contain all the data to make ONE Store object.
    // This means a couple of things:
    //  1: We know how many points of data there are, and by extension how many commas
    //  2: We know each point is comma seperated.
    //
    // To get to each point of data, we can take the substring from the start of our currentString to the next comma. Because it is the last data point, we can just take the rest of the string for longitutde.
    // For every data point except longitude, currentString becomes itself after the leading comma.

    // storeName
    storeName = currentLine.substr(0, currentLine.find(','));
    currentLine = currentLine.substr(currentLine.find(',') + 1);
    // squareFeet
    stringFeet = currentLine.substr(0, currentLine.find(','));
    storeFeet = stoi(stringFeet);
    currentLine = currentLine.substr(currentLine.find(',') + 1);
    // storeSize
    storeSize = currentLine.substr(0, currentLine.find(','));
    currentLine = currentLine.substr(currentLine.find(',') + 1);
    // storeAddress
    storeAddress = currentLine.substr(0, currentLine.find(','));
    currentLine = currentLine.substr(currentLine.find(',') + 1);
    // storeArea
    storeArea = currentLine.substr(0, currentLine.find(','));
    currentLine = currentLine.substr(currentLine.find(',') + 1);
    // storeLat
    stringLat = currentLine.substr(0, currentLine.find(','));
    storeLat = stod(stringLat);
    currentLine = currentLine.substr(currentLine.find(',') + 1);
    // storeLon
    stringLon = currentLine;
    storeLon = stod(stringLon);
    
    // Data collection complete!
    // Time to make some objects...
    
    currentStore = new Store(storeName, storeFeet, storeSize, storeAddress, storeArea, storeLat, storeLon);
    return currentStore;
}

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

// Creates a Vector of Neighborhood pointers so that we can do cool statistic stuff to all the neighborhoods :)
vector<Neighborhood*> getNeighborhoods(vector<Store*> storeList)
{
    bool isUnique;
    string currentArea = "";
    vector<Neighborhood*> neighborhoodList;
    Neighborhood* currentNeighborhood = nullptr;
    
    for(int i = 0; i < storeList.size(); ++i)
    {
        // The list will always start blank, so the first store will have a unique neighborhood.
        if(neighborhoodList.size() == 0)
        {
            currentNeighborhood = new Neighborhood(storeList.at(i)->neighborhood);
            neighborhoodList.push_back(currentNeighborhood);
        }
        else
        {
            isUnique = true;
            for(int j = 0; j < neighborhoodList.size(); ++j)
            {
                // if the current neighborhood name is equal to any of the neighborhoods in the list, this isn't a unique neighborhood :)
                if(storeList.at(i)->neighborhood == neighborhoodList.at(j)->name)
                    isUnique = false;
            }
            // i.e. if we have a new, unique neighborhood on our hands, mark that down!!! otherwise who cares
            if(isUnique)
            {
                currentNeighborhood = new Neighborhood(storeList.at(i)->neighborhood);
                neighborhoodList.push_back(currentNeighborhood);
            }
        }
    }

    return neighborhoodList;
}

/*
 * Statistic functions!!!
 */

// First Menu Option
// "Display general grocery stores information"
// Displays the:
// 	Number of stores in the file
// 	Number of stores with the "Large" size in the file.
// 	Average size of "Large" grocery stores.

void storesInfo(vector<Store*> storeList)
{
    int largeStores = 0;
    double sumLarge = 0.0;
    double avgLarge;
    
    // The vector only holds pointers to existing Store objects.
    // Therefore, the number of elements in the vector is equal to the number of pointers, which is equal to the number of stores.
    cout << "Number of grocery stores: " << storeList.size() << endl;
    for(int i = 0; i < storeList.size(); ++i)
    {
        // We only care about collecting data on Large stores.
        if(storeList.at(i)->size == "Large")
        {
            largeStores++; // large store count
            // If the square footage of the store is actually known i.e. != 0, we add it to the sum of square feet.
            if(storeList.at(i)->squareFeet > 0)
            {
                sumLarge += storeList.at(i)->squareFeet;
            }
        }
    }
    
    // We already know the number of large stores at this point, so we can just output it now.
    cout << "Number of large grocery stores: " << largeStores << endl;

    // Now we have the sum of known square feet, we can calculate the average.
    avgLarge = double(sumLarge) / double(largeStores); // have to cast to doubles otherwise our division gets rounded bcs integers :)

    cout << fixed; // cplusplus.com says that this puts my doubles/floats into 'fixed' mode (presumably no rounding silliness)
    cout << "Average size of large grocery stores: " << setprecision(1) << avgLarge << endl;
}

// Sorts any given Vector of Neighborhood Object Pointers from most stores to least.
vector<Neighborhood*> sortNeighborhood(vector<Neighborhood*> unsortedVector)
{
	bool isSmallest;
	
	vector<Neighborhood*> sortedVector;
	// Lazy Sorting Algo
	// 1. Simply add first value to vector
	// 2. If current value is less than current value iterated in vector, continue iteration
	// 3. Else insert value at current position
	
	// Step 1.
	sortedVector.push_back(unsortedVector.at(0));
	// Step 2.
	for(int i = 1; i < unsortedVector.size(); ++i)
	{
		isSmallest = true;
		for(int j = 0; j < sortedVector.size(); ++j)
		{
			// We only care if the current value is greater than another, otherwise it will make its way toward the back eventuallyi
			// Step 2 implictly, Step 3 explicitly
			if(unsortedVector.at(i)->totalStores == sortedVector.at(j)->totalStores)
			{
                            if(unsortedVector.at(i)->name < sortedVector.at(j)->name)
                                sortedVector.insert((sortedVector.begin() + j), unsortedVector.at(i));
                            else
                                sortedVector.insert(sortedVector.begin() + (j+1) , unsortedVector.at(i));

                            isSmallest = false;
                            j = sortedVector.size();
			}
			else if(unsortedVector.at(i)->totalStores > sortedVector.at(j)->totalStores)
			{
				// C++ nonsense with how iterators specifically work mean I must specify the beginning of the vector for this function.
				sortedVector.insert( (sortedVector.begin() + j), unsortedVector.at(i) );
				isSmallest = false;
				j = sortedVector.size();
			}
		}
		if(isSmallest)
			sortedVector.push_back(unsortedVector.at(i));
	}
	return sortedVector;
}

// Given an input of all stores and all neighborhoods, find how many large and small stores are in each. 
// NOTE: I refer to the local neighborhood variable as area bcs its less to type.
void neighborhoodSizes(vector<Store*> storeList, vector<Neighborhood*> areaList)
{
    bool isMatch = false;
    int j;
    vector<Neighborhood*> neighborhoodList;

    for(int i = 0; i < storeList.size(); ++i)
    {
        // For this project, not many neighborhoods are present for any given file, so we can just cycle through every single one until we find a match.
        j = 0;
	isMatch = false;
        while(!isMatch)
        {
            if(storeList.at(i)->neighborhood == areaList.at(j)->name)
            {
                if(storeList.at(i)->size == "Large")
                {
                    areaList.at(j)->addLarge();
                    isMatch = true;
                }
                else if(storeList.at(i)->size == "Small")
                {
                    areaList.at(j)->addSmall();
                    isMatch = true;
                }
            }
            j++;
        }
    }

    // Sorts areaList so that data is output in order from most stores to least.
    neighborhoodList = sortNeighborhood(areaList);

    // At this point, the for loop has terminated, that is every store has been accounted for :)
    // setw(24) seems to be the magic number for formatting :)
    // TODO: ADD SORTING BY MOST STORES
    // Loops through every Neighborhood object in the vector
    for(int i = 0; i < neighborhoodList.size(); ++i)
    {	
        cout << neighborhoodList.at(i)->name << setw(24 - (neighborhoodList.at(i)->name.size())) << "";
        // Large Stores output :)
	for(int j = 0; j < neighborhoodList.at(i)->largeCount; ++j)
	{
		cout << "L";
	}
        // Small Stores output :D
	for(int j = 0; j < neighborhoodList.at(i)->smallCount; ++j)
	{
		cout << "S";
	}
        cout << endl;
    }
}

// THIRD MENU OPTION
// Closest Store
/*
 * Really simple function: Simply just cycles through every Store in memory and runs the predefined distance function in Utils.h.
 * We care about two datapoints specifically:
 * 	- The closest store out of all the stores
 * 	- The closest Large Store
 * 	* NOTE: They may be the same store.
 * We can save the stores which fit these criteria for printing later.
 * "  location is not a food desert if it is within half a mile of any store, or within one mile of a large store. It is a food desert if neither of those applies. "
 * Therefore, it can be said that if totalStoresDistance > 0.5 && largeStoresDistance > 1, then we additionally output the line "This location is a food desert."
 *
 * For my reference and anyone who wishes to edit this code, the distance function is defined as such:
 * 	double distance(double lat1, double lon1, double lat2, double lon2)
 * Wherein lat1 and lon1 belong to the user input lat and lon, whilst the second pair of lat/lon values belongs to that of the current store.
 */

// Also atp I am aware I could be passing these vectors by reference, but I don't think it is the end of the world to create a temporary variable vector full of pointers as opposed to if I was using objects :)
void closestStore(vector<Store*> storeList, double userLat, double userLon)
{
	// variables are named like xStoresDistance for brevity and sanity but its the minimum distance. I just thought it would be too much to call them something like minTotalStoresDistance! Large enough as is imo
	// For these "find the minimum/maximum" type problems I always set the initial values as the first element in the list.
	Store* totalStoresDistance = storeList.at(0);
	Store* largeStoresDistance = storeList.at(0);
	// At this point the ...StoresDistance values are just the first terms, so we can use them as shorthand :)
        // Premptively rounding our minimums to avoid future issues, see comments below for a little more info
	double totalMin = /*floor(*/distance(userLat, userLon, totalStoresDistance->lat, totalStoresDistance->lon)/* * 10) / 10*/;
	double largeMin = /*floor(*/distance(userLat, userLon, largeStoresDistance->lat, largeStoresDistance->lon)/* * 10) / 10*/;	
        // holds distance between current store in vector and the user's lat/lon values. here for brevity and readability. :D
        double currentDistance;

        // Minimum Distance Finding Algo
	for(int i = 1; i < storeList.size(); ++i)
	{
            currentDistance = distance(userLat, userLon, storeList.at(i)->lat, storeList.at(i)->lon);
            // Notoriously, Double/Float comparison requires you sell your mortal soul to achieve somewhat consistently.
            // Therefore, I'm just going to premptively round the distance to the nearest tenth. 
            // Utils.h includes <math.h> so we can just use ceil()
            // currentDistance = floor(10 * currentDistance) / 10;
            // Checker for all stores
            if(currentDistance < totalMin)
            {
                totalStoresDistance = storeList.at(i);
                totalMin = currentDistance;
            }
            // Checker for large stores
            if(storeList.at(i)->size == "Large")
            {
                if(currentDistance < largeMin)
                {
                    largeStoresDistance = storeList.at(i);
                    largeMin = currentDistance;
                }
            }
	}
        
	// Output
        cout << "The closest store is " << fixed << setprecision(1) << totalMin << " miles away." << endl;
        cout << "\t" << totalStoresDistance->name << " is at " << totalStoresDistance->address << endl;
	if(totalStoresDistance == largeStoresDistance)
	{
	    cout << "That is a large store." << endl;
	}
	else
	{
            cout << "The closest large store is " << fixed << setprecision(1) << largeMin << " miles away." << endl;
            cout << "\t" << largeStoresDistance->name << " is at " << largeStoresDistance->address << endl;
	}
	if(totalMin > 0.5 && largeMin > 1.0)
            cout << "This location is a food desert." << endl;
}

// FOURTH MENU OPTION
// Search Function
void storeSearch(const vector<Store*>& storeList, string toFind)
{
    bool foundFlag = false;
    Store* storeMatch = nullptr;
    vector<Store*> storeMatches;

    int i = 0;
    // Capitalizes string to match text file convention
    while(toFind[i])
    {
        toFind[i] = toupper(toFind[i]);
        i++;
    }

    // Linear Search
    for(int i = 0; i < storeList.size(); ++i)
    {
        if(storeList.at(i)->name.find(toFind) != string::npos)
        {
            foundFlag = true;
            storeMatch = storeList.at(i);
            storeMatches.push_back(storeMatch);
        }
    }

    if(foundFlag)
    {
        for(int i = 0; i < storeMatches.size(); ++i)
        {
            cout << "Store: " << storeMatches.at(i)->name << endl;
            cout << "Address: " << storeMatches.at(i)->address << endl;
            cout << "Community: " << storeMatches.at(i)->neighborhood << endl;
            cout << "Size: " << storeMatches.at(i)->size << endl;
            cout << "Square Feet: " << storeMatches.at(i)->squareFeet << endl;
	    cout << endl;
        }
    }
    else
        cout << "No stores found." << endl;
}

int main() 
{
    string filename;
    int choice;
    vector<Store*> storeList;
    vector<Neighborhood*> neighborhoodList;
    bool inMenu = true;
    string toFind;
    double userLat;
    double userLon;
    
    cout << "Enter filename: ";
    cin >> filename;
    cout << endl;
    // Reads file and compiles information into a vector of Store objects.
    // readFile returns a vector of pointers to Store objects. We will use these 
    storeList = readFile(filename);

    while(inMenu)
    {
    cout << "Select a menu option:" << endl;
    cout << "   1. Display general grocery stores information" << endl;
    cout << "   2. Display neighborhood charts" << endl;
    cout << "   3. Find closest stores" << endl;
    cout << "   4. Search for store by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: ";
 
    cin >> choice;
	
    switch(choice)
        {
            case 1:
                storesInfo(storeList);	
                break;
            case 2:
                // Goes through all Store Objects and create Neighborhood Objects. Put objects into list.
                neighborhoodList = getNeighborhoods(storeList);
                // TODO: Goes through all eighborhoods and prints neighborhoods and their sizes.
		neighborhoodSizes(storeList,neighborhoodList);	                
                break;
            case 3:
                // user input
                cout << "Enter latitude: ";
                cin >> userLat;

                cout << "Enter longitude: ";
                cin >> userLon;

                // function call
                closestStore(storeList, userLat, userLon);
                break;
            case 4:
		cout << "Enter store to search for: ";
                cin >> toFind;
		cout << endl;
                storeSearch(storeList, toFind);
                break;
            case 5:
                inMenu = false;
                break;
        }
    }
}
