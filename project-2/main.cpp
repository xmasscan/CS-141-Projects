#include <iostream>

// Author: Michael Hanif Khan
// Class: CS 141
// Section: 2-3pm, Hodges

using namespace std;

bool codeValidator(int tempCode[],bool isLegal){
    int i;
    int j;
    const int CODE_LENGTH = 4;
    
    isLegal = true;

    for(i = 0; i < CODE_LENGTH; ++i){
        for(j = 0; j < i; ++j){
            if(tempCode[j] == tempCode[i])
                return false;
        }
        if(!(tempCode[i] > -1 && tempCode[i] < 10))
            return false;
    }
    return true;
}


int main() 
{
    int i;
    int j;
    int secretCode[4];
    int currentGuess[4];
    const int CODE_LENGTH = 4;
    bool isLegal = false;
    const int NUM_OF_GUESSES = 10;
    bool winCase = false;

    int bulls;
    int cows;
    
    while(!isLegal){
    cout << "Enter the solution to use: ";
    for(i = 0; i < CODE_LENGTH; ++i){
        cin >> secretCode[i];
        }
    isLegal = codeValidator(secretCode, isLegal);
    if(!isLegal)
        cout << "Invalid code. Try again." << endl;
    }

    for(i = 1; i <= NUM_OF_GUESSES; ++i){

        isLegal = false;
        while(!isLegal){
            cout << "Turn " << i << ". Enter a guess: ";
            for(int k = 0; k < CODE_LENGTH; ++k){
                cin >> currentGuess[k];
            }
            isLegal = codeValidator(currentGuess, isLegal);
            if(!isLegal)
                cout << "Invalid code. Try again." << endl;
        }

        cows = 0;
        bulls = 0;

        for(j = 0; j < CODE_LENGTH; ++j){
            if(secretCode[j] == currentGuess[j])
                ++bulls;
            for(int k = 0; k < CODE_LENGTH; ++k){
                if(secretCode[j] == currentGuess[k])
                    ++cows;
            }
        }

        cows -= bulls;

        if(bulls == 4){
            cout << "Congratulations! You win!";
            winCase = true;
            i = 11;
        }
        else
            cout << "There are " << bulls << " bulls and " << cows << " cows." << endl;

    }

    if(!winCase){
        cout << "You lose. The correct answer is: ";
        for(j = 0; j < CODE_LENGTH - 1; ++j){
            cout << secretCode[j] << " ";
        }
        cout << secretCode[CODE_LENGTH - 1];
    }

    return 0;
}