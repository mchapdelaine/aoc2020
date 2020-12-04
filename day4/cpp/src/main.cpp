#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "PassportClass.h"


using namespace std;

unsigned int getNumberPassportsValidsPart1(const vector<PassportClass>& pPassports)
{
    unsigned int lCount = 0;

    for (const auto lPassport : pPassports)
    {
        if (lPassport.isValidPart1())
        {
            lCount++;
        }
    }

    return lCount;
}

unsigned int getNumberPassportsValidsPart2(const vector<PassportClass>& pPassports)
{
    unsigned int lCount = 0;

    for (const auto lPassport : pPassports)
    {
        if (lPassport.isValidPart2())
        {
            lCount++;
        }
    }

    return lCount;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 4\n";
    
    if (pArgc < 2)
    {
        cout << "Missing input file name\n";
        return EXIT_FAILURE;
    }
    
    ifstream lInputFile(pArgv[1], std::ifstream::in);

    if (!lInputFile.is_open())
    {
        cout << "Could not open " << pArgv[1] << ", exit\n";
        return EXIT_FAILURE;
    }
    
    string lTemp;
    string lPassportString;
    vector<PassportClass> lPassports;
    
    while (getline(lInputFile, lTemp))
    {
        if (lTemp.length() != 0)
        {
            lPassportString += lTemp;
            lPassportString += " ";
        }
        else
        {
            stringstream lStream;
            lStream << lPassportString;

            // Add passport
            PassportClass lPassport(lStream);
            lPassports.emplace_back(lPassport);

            // Clean passport string
            lPassportString = "";
        }
    }

    // Add the last passport if the file does not end with an empty line
    if (lPassportString.length() != 0)
    {
        stringstream lStream;
        lStream << lPassportString;
        PassportClass lPassport(lStream);
        lPassports.emplace_back(lPassport);
    }

    cout << "Part 1 : number passports valids : " << getNumberPassportsValidsPart1(lPassports) << endl;
    cout << "Part 2 : number passports valids : " << getNumberPassportsValidsPart2(lPassports) << endl;
    
    return EXIT_SUCCESS;
}

