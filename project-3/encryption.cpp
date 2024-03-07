#include "encryption.h"

using namespace std;

// Simple string reversal function.
// using the built in algorithm for string reversal would be faster, but in all honesty it is just not important at this stage
string reverseMsg(string message)
{
	string reversed = "";
	for(int i = message.size() - 1; i >= 0; i--)
	{
		reversed += message[i];
	}
	return reversed;
}

string encrypt(string message, int shift, char direction)
{
    // Stands for "current Shift."
    // shift is the shift value input by the user, whilst currShift is the partial sum S_n of the sequence a_n = (shift*n) + a_(n-1)
    // *probably
	int currShift = 0;
	char currChar;
	int lastCharVal = 0;
	int currPos = 0;

	string encryptedMessage = "";

	
	for(int i = 0; i < message.size(); i++)
	{
		currChar = message[i];

		if(currChar == ' ')
			currChar = '[';

		currChar = toupper(currChar);
		

		if(int(currChar) >= 65 && int(currChar) <= 91)
		{
			currShift += shift + lastCharVal;
			lastCharVal = int(currChar) - 65;
			// Shifts value from ascii to distance from 65
			currPos = int(currChar) - 65;
			// Shifts value forward in range based off of shift value
			currPos += currShift;
			// adjusts position to remain in range
			currPos = currPos % 27;
			// assigns currentChar with matching ascii value
			currChar = 65 + currPos;
		}
		if(currChar == '[')
			currChar = ' ';

			encryptedMessage += currChar;
	}
	if(direction == 'b')
		encryptedMessage = reverseMsg(encryptedMessage);
	return encryptedMessage;
}

string decrypt(string message, int shift, char direction)
{
	int currShift = 0;
	int currPos = 0;
	int lastCharVal = 0;
	char currChar;

	string decryptedMessage = "";
	if(direction == 'b')
		message = reverseMsg(message);
	for(int i = 0; i < message.size(); i++)
	{
		currChar = message[i];

		if(currChar == ' ')
			currChar = '[';

		currChar = toupper(currChar);

		if(int(currChar) >= 65 && int(currChar) <= 91)
		{
			currShift += shift + lastCharVal;
			currPos = int(currChar) - 65;
			// If the shift would lead the current character out of our predefined range, calculate the "wrap around".
			// The new position value should be equal to (currPos - currShift) % 27.
			// 	0 <= (currPos - currShift) % 27 <= 26.
			// This makes sense, because if the difference would be -1, the position would be updated to 26, the index of the last character
			// And if the difference was -27 (a full shift), the position would be set to zero, which makes sense.
			
			currShift = currShift % 27;
			currPos = (currPos - currShift) % 27;
			if(currPos < 0)
				currPos = 27 + currPos;
			currChar = char(65 + currPos);
			
			lastCharVal = int(currChar) - 65;
		}
			if(currChar == '[')
				currChar = ' ';
			decryptedMessage += currChar;
	}

	return decryptedMessage;
}
