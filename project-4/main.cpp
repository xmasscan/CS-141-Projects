#include <ostream>
#include <fstream>
#include <string>
#include "Utils.h"

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
	// I'm used to them being referred to this way, but you are free to rename these for clarity.
	double lat;
        double lon;
}

int main() 
{
    int choice;
    cout << "Select a menu option: " << endl;
    cout << "   1. Display general grocery stores information" << endl;
    cout << "   2. Display neighborhood charts" << endl;
    cout << "   3. Find closest stores" << endl;
    cout << "   4. Search for store by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: ";
    
}

