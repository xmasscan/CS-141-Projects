# CS 141 Project 3: Encryption

This project tasked me with creating a program which implements the '141 Cipher'.


## Values to Deal With

The '141 Cipher' is an encryption method derivative of the Caesar Cipher.

Each *capital* English character is assigned a value from 1-25, equivalent to its position in the alphabet. A space is assigned a value of 26, as if it were the character after 'Z'.

The actual character after 'Z' is '['. For encryption, values of ' ' will be replaced with '[', and vice versa for decryption.

## Encryption Vectors

### Shift
The "Shift" is an integer value representing where in our list of values the letter will be "shifted" to.

It is important to note that this list is cyclical. If applying shift to the value of a character will result in a value greater than 26, the difference of the value and 26 will be treated as the shift from 'A'.

#### Examples:

- Regular Shifts
- - Applying a shift of '2' upon 'A' is effectively adding '2' to '1'. This returns a value of '3', which is encrypted as 'C'.
- Shifting over 26
- - Applying a shift of '10' upon 'X' is equivalent to 10 + 24, which equals 34. 34 - 26 = 8. 8 is encrypted as 'H', the eighth letter of the alphabet.


### Shifting in Application
Each message begins encryption with a random shift value. This means that there are 26 seperate possible variations of a given message, as only values from 0-25 will produce a unique initial shift. (Shifting by 26 is equivalent to shifting by 0, 27 to 1, etc.)

From there on, each character's shift will be equal to the value of the previous character in the unshifted message plus the current shift value:

**shift += charValue;**

### Direction

A direction of 'f' will append each encrypted character to the end of the message, encrypting it "forwards".

A direction of 'b' will append each encrypted character to the beginning of the message, encrypting it "backwards".