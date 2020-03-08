/**
 * File: vampire-numbers.cpp
 * -------------------------
 * Provides a program that repeatedly prompts the user for positive
 * numbers with an even number of digits and informs them
 * whether the number is a Vampire number or not.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h" 
#include "simpio.h" // for getInteger
#include "strlib.h" // for stringToInteger, integerToString

static bool recIsVampireNumber(int& number, int& first, int& second, std::string& numString, std::string soFar);


static int getPossibleVampireNumber() {
    while (true) {
        int response = getInteger("Enter a positive integer [or 0 to quit]: ");
        if (response >= 0) return response;
        cout << "Ah, sorry.  I need a nonnegative response.  Try again... " << endl;
    }
}

static bool isVampireNumber(int number, int& first, int& second) {
    std::string numString = integerToString(number);
    return recIsVampireNumber(number, first, second, numString, "");
}

static bool recIsVampireNumber(int& number, int& first, int& second, std::string& numString, std::string soFar)
{
    if (numString == "")
    {
        first = stringToInteger(soFar.substr(0, soFar.length() / 2));
        second = stringToInteger(soFar.substr(soFar.length() / 2));
        if (first * second == number)
        {
            return true;
        }
    }
    else
    {
        char ch;
        for (int i = 0; i < numString.length(); i++)
        {
            ch = numString[i];
            std::string rest = numString.substr(0,i) + numString.substr(i + 1);
            if (recIsVampireNumber(number, first, second, rest, soFar + ch))
            {
                return true;
            }
        }
    }
    return false;
}

int main() {
    cout << "Here's a program that tells you whether or not a "
         << "number you enter is Vampire." << endl << endl;
    while (true) {
        int number = getPossibleVampireNumber();
        if (number == 0) break;
        int first, second;
        if (isVampireNumber(number, first, second)) {
            cout << "Woo! " << number << " is a Vampire number, and "
                 << first << " and " << second << " are its fangs." << endl << endl;
        } else {
            cout << "Nope! The number " << number << " isn't Vampire." << endl << endl;
            cout << first << endl << second << endl;
        }
    }
    cout << endl;
    cout << "All done!" << endl;
    return 0;
}
