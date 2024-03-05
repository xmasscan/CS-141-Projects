#include "encryption.h"

using namespace std;

// Encrypts a given message with the 141 Cipher outlined in the readme.
// Takes the given message as a string, the initial shift of the message as an integer value, and the direction which to encrypt the message as a char.
string encrypt(string message, int constantShift, char direction)
{
	string encryptedMessage = "";
	char currentChar;
	int lastCharVal;
	int shift;
	
	//Ascii value of '[', our placeholder for ' '.
	const int UPPERBOUND = 91;

	// Reversing string for backwards encryption
	if (direction == 'b')
	{
		string reverseMessage = "";
		for(int i = message.size() - 1; i >= 0; i--)
		{
			reverseMessage += message.at(i);
		}
		message = reverseMessage;
	}

	shift = constantShift;
	for(int i = 0; i < message.size(); ++i)
	{
		// If the shift is greater than 26, we must convert it into its offset from 0 on the cyclic domain 0-26.
		if(shift > 26)
		{
			shift = shift % 27;
		}
		
		currentChar = message[i];
		
		// For this encryption method, we simply just assume that the ascii value for space is that of the left bracket.
		if(currentChar == ' ')
			currentChar = '[';
		// Capitalizes all characters.
		if(isalpha(currentChar)) currentChar = char(toupper(currentChar));

		// If a character isn't in the set of characters we care about encrypting, {A,B,C...Y,Z, }, then we ignore it and don't decrypt it.
		if(int(currentChar) >= 65 && int(currentChar) <= 91)
		{
			lastCharVal = int(currentChar) - 64;
			//If the current shift would set the current character to a value outside of our acceptable range of ascii characters, we readjust.
			if(currentChar + shift > UPPERBOUND)
			{
				// Adding to 64 instead of 65 because the minimum value over 91 is 92. 92 % 91 = 1, which would otherwise fasely produce an encrypted character 'B' instead of 'A'.
				currentChar = char(64 + ((currentChar + shift) % 91));
			}
			else
				currentChar+= shift;

			shift += constantShift + lastCharVal;
		}
		// Brackets are converted back into spaces for encrypted message. :)
		if(currentChar == '[') currentChar = ' ';

		encryptedMessage += currentChar;
	}
	return encryptedMessage;
}

string decrypt(string message, int constantShift, char direction){
	string decryptedMessage = "";
	int shift;
	char currentChar;
	int lastCharVal;
	const int LOWERBOUND = 65;
	int difference;

	// The initial value of the shift is the constant shift input into the function that is added to the shift for every character.
	shift = constantShift;
	for(int i = 0; i < message.size(); ++i){
		// Shift check from earlier :), could be implemented as a function, but not really that important to implement for the scope of this project
		if(shift > 26)
		{
			shift = shift % 27;
		}
		currentChar = message[i];
		if(currentChar == ' ')
				currentChar = '[';
		if(int(currentChar) >= 65 && currentChar <= 91)
		{	
			if(currentChar - shift < LOWERBOUND)
			{
				// 1. Find the difference between the lower bound and the value of currentChar. (currentChar - shift) - 65
				// 2. Find the index of the decrypted value of currentChar within our range of 26 values. (difference + 27)
				// 3. Add this index to 65 for the appropriate ASCII value of currentChar.
				// 4. Since we add 27 and 65 in succession, we can simply just add their sum to the difference.
				// 	a. ( (currentChar - shift) - 65) + 27 ) + 65 ) = currentChar - shift + 27
				currentChar = currentChar - shift + 27;
			}	
			else
				currentChar -= shift;

			lastCharVal = int(currentChar) - 65;	
			shift += constantShift + lastCharVal;
		}
		if(currentChar == '[')
			currentChar = ' ';
		if(direction == 'b')
			decryptedMessage = currentChar + decryptedMessage;
		else
			decryptedMessage += currentChar;
	}

	return decryptedMessage;
}
