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
		// encrypt spaces as left brackets (ascii code of 91, which is equal to 65 + 26, which makes it the last character in the range 0 - 26.
		if(currChar == ' ')
			currChar = '[';
		// make the letters big if they're small :)
		currChar = toupper(currChar);
		
		// we only care about encrypting if the current character is a capital english character or '['
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
		// now to pretend as if we didn't just encrypt left brackets isntead of spaces because it was mathematically more convenient :)
		if(currChar == '[')
			currChar = ' ';

			encryptedMessage += currChar;
	}
	// We DO NOT reverse the plaintext, we just reverse the ciphertext. :D
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
	// cipher text gets reversed, but plaintext has to be in its correct orientation.
	// decrypting backwards basically just tells us that the ciphertext is backwards and we should account for tha
	// // cipher text gets reversed, but plaintext has to be in its correct orientation.
	// decrypting backwards basically just tells us that the ciphertext is backwards and we should account for that.
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
			// Calculates shift as applied to current position in range 0-26, rather than directly unto the ascii value.
			// We % 27 this shifted value so that it remains in range
			currPos = (currPos - currShift) % 27;
			// C++ kind of cheats when it does the modulo operation
			// Because it just does some weird bit shifting nonsense, it is likely that the answer is negative. This is extremeeely easy to account for thankfully :)
			// For all possible negative values this may produce, we can just add the value to 27 to get the current position within our range.
			if(currPos < 0)
				currPos = 27 + currPos;
			// Is it inefficient to not just save lastCharVal as int(currChar) at this point? Yes. Will I change my code? No. The last time I tried this, I encountered an error with git that led to this entire project mysteriously breaking despite no substantial change in code.
			// Perhpaps there are spirits within my CPU, or I just don't know how git works. Clearly, it is the former.
			currChar = char(65 + currPos);
			
			lastCharVal = int(currChar) - 65;
		}
			// We set all spaces to left brackets on the way in, so that we may decrypt spaces as if they were left brackets. Now we undo this.
			if(currChar == '[')
				currChar = ' ';
			decryptedMessage += currChar;
	}

	return decryptedMessage;
}
