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
	// I'm used to them being referred to this way, but you are free to rename these for clarity.
	double lat;
    double lon;

    Store(string name, int squareFeet, string size, string address, string neighborhood, double lat, double lon){
        this->name = name;
        squareFeet = squareFeet;
        size = size;
        address = address;
        neighborhood = neighborhood;
        lat = lat;
        lon = lon;
    }

};

//


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

