#include "encryption.cpp"
#include <iostream>
// #pragma once

using namespace std;

int main(){

	int menuChoice;
	int shift;
	char direction;

	string message;
	string encryptedMessage;
	string decryptedMessage;

	cout << "1. Encrypt message" << endl;
	cout << "2. Decrypt message" << endl;
	cout << "3. Show decrypted possibilties" << endl;
	cout << "4. Break code" << endl;
	cout << "Enter choice: ";
	
	cin >> menuChoice;
	
	switch(menuChoice)
	{
		case(1):
			cout << "Enter shift (1-26): ";
			cin >> shift;
			cout << "Enter direction (f or b): ";
			cin >> direction;
			cout << "Enter message: ";
			//flushes out newline
			cin.ignore();
			getline(cin, message);
			
			encryptedMessage = encrypt(message,shift,direction);
			cout << "Encrypted message: " << encryptedMessage;
			break;
		case(2):
			cout << "Enter shift (1-26): ";
			cin >> shift;
			cout << "Enter direction (f or b): ";
			cin >> direction;
			cout << "Enter message: ";
			cin.ignore();
			getline(cin, message);

			decryptedMessage = decrypt(message,shift,direction);
			cout << "Decrypted message: " << decryptedMessage;	
			break;
		case(3):
			cout << "Enter Message: ";
			cin.ignore();
			getline(cin, message);
			for(int i = 1; i < 27; ++i)
			{	
				decryptedMessage = decrypt(message,i,'f');
				cout << i << "f: " << decryptedMessage << endl;
				decryptedMessage = decrypt(message,i,'b');
				cout << i << "b: " << decryptedMessage << endl;
			}
			break;
		case(4):
			cout << "Enter message: ";
			int dummy;
			cin.ignore();
			getline(cin, dummy);
			cout << "Unable to find a decrypted message.";
			break;
		default:
			cout << "Not an option. Choose again.";
			cin >> menuChoice;
			break;
	}
	return 0;
}

