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
	int shift = 0;
	char currentChar;
	int lastCharVal = 0;
	const int LOWERBOUND = 65;
	int difference;
	
	if(direction == 'b')
	{
		string reverseMessage = "";
		for(int i = message.size() - 1; i >= 0; i--)
		{
			reverseMessage += message.at(i);
		}
		message = reverseMessage;
	}

	for(int i = 0; i < message.size(); ++i){
		currentChar = message[i];
		if(currentChar == ' ')
				currentChar = '[';
		if(int(currentChar) >= 65 && int(currentChar) <= 91)
		{
		// If this is a legal character for shifting, we need just undo the encryption.
		// Therefore, the shift should equal that of the shift in the encryption algorithm, but this time be subtracted from the current character.
		
		// First, we must calculate the shift itself.
		 shift += constantShift + lastCharVal;
			if(shift > 26)
			{
				shift = shift % 27;
			}
			if((currentChar - 65) - shift < 0)
			{
				int newShift = shift - (currentChar - 65);
				newShift = 27 - newShift;
				currentChar = 65 + newShift;
			}	
			else
				currentChar -= shift;

			lastCharVal = int(currentChar) - 65;	
		}

		if(currentChar == '[')
			currentChar = ' ';
		decryptedMessage += currentChar;
	}

	return decryptedMessage;
}
