#include "PasswordClass.h"
#include <iostream>

using namespace std;

PasswordClass::PasswordClass(const string& pPasswordLine) 
{
    // Parse string in format <min>-<max> <letter>: <password>
    aMin = stoi(pPasswordLine.substr(0, pPasswordLine.find("-", 0)));
    aMax = stoi(pPasswordLine.substr(pPasswordLine.find("-", 0) + 1, pPasswordLine.find(" ", 0)));
    aLetter = pPasswordLine.substr(pPasswordLine.find(":", 0) - 1, pPasswordLine.find(":", 0) - 1)[0];
    
    // Note : Leave space as first character, for 2nd part
    aCharacters = pPasswordLine.substr(pPasswordLine.find(": ", 0) + 1, pPasswordLine.npos);
}

bool PasswordClass::isValid() const 
{
    int lCount = 0;
    
    for (unsigned int i = 0; i < aCharacters.length(); i++)
    {
        if (aCharacters[i] == aLetter)
        {
            lCount++;
        }
    }
    
    if (lCount >= aMin && lCount <= aMax)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PasswordClass::isValid2() const 
{
    
    if (aMin <= aCharacters.length() && aMax < aCharacters.length())
    {
        int lCount = 0;
        if (aCharacters[aMin] == aLetter)
        {
            lCount++;
        }
        if (aCharacters[aMax] == aLetter)
        {
            lCount++;
        }
        
        if (lCount == 1)
        {
            return true;
        }
    }
    
    return false;
}



