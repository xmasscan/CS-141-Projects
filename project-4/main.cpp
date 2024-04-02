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

};

// File Reading Function
/*
 * Gets each line of the file and creates a new store with the data.
 * Each line of data can be assumed to be reliably structured similiarly to the Store constructor.
 * That is, the order of data is as follows:
 *  Name, Square Footage, 'Size' (is SF 10,000+?), Address, Neighborhood, Latitude, Longitude.
 */

void textToData(string filename)
{
    // We will be storing pointers to Store objects, rather than the objects themselves.
    vector<Store*> storeList;
    // Initializes first Store object as a null pointer, then assigns it the pointer of each new Store object.
    Store* currStore = nullptr;

}

int main() 
{
    string filename;
    int choice;
    ifstream fileIn;
    
    cout << "Enter filename: " << endl;
    cin >> filename;
    
    // Reads file and compiles information into a vector of Store objects.
    

    cout << "Select a menu option: " << endl;
    cout << "   1. Display general grocery stores information" << endl;
    cout << "   2. Display neighborhood charts" << endl;
    cout << "   3. Find closest stores" << endl;
    cout << "   4. Search for store by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: ";
    
    cin >> choice;
    switch(choice){
	case(1):
	    cout << "Choice One" << endl;
	    break;
	case(2):
	    cout << "Choice Two" << endl;
	    break;
	case(3):
        cout << "three" <<endl;
	    break;
    default:
        break;
    }

}

