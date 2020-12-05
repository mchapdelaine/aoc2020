#include "BoardingPassClass.h"

#include <iostream>
#include <stdexcept>

using namespace std;

BoardingPassClass::BoardingPassClass(const std::string& pBoardingPassString)
{
    unsigned int lAdder = 64;
    aRow = 0;
    aColumn = 0;

    if (pBoardingPassString.length() < 10)
    {
        cout << "The string does not have seven characters\n";
        cout << "Wrong string : " << pBoardingPassString << endl;
        throw runtime_error("Invalid string for boarding pass");
    }
    
    for (unsigned int i = 0; i < 7; i++)
    {
        if (pBoardingPassString[i] == 'B')
        {
            aRow += lAdder;
        }
        lAdder = lAdder >> 1;
    }

    lAdder = 4;
    for (unsigned int i = 7; i < 10; i++)
    {
        if (pBoardingPassString[i] == 'R')
        {
            aColumn += lAdder;
        }
        lAdder = lAdder >> 1;
    }
}

unsigned int BoardingPassClass::getId() const noexcept
{
    return aRow * 8 + aColumn;
}