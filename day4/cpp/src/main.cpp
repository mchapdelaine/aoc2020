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
            //cout << "Passport is valid\n";
        }
        // else
        // {
        //     cout << "Passport is invalid\n";
        // }
    }

    return lCount;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 4\n";

    // Test birth Year
    stringstream lNull;
    PassportClass lTest(lNull);
    lTest.setByr("2002");
    
    cout << "Birth Year valid " << lTest.isBirthYearValid() << endl;


    //return 0;
    
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
        //cout << "Got line " << lTemp << "    length " << lTemp.length() <<  endl;
        if (lTemp.length() != 0)
        {
            lPassportString += lTemp;
            lPassportString += " ";
        }
        else
        {
            // Got complete passport
            //cout << "Got passport loop : " << lPassportString << endl;

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
        //cout << "Got passport (outside loop) : " << lPassportString << endl;
        stringstream lStream;
        lStream << lPassportString;
        PassportClass lPassport(lStream);
        lPassports.emplace_back(lPassport);
    }

    //cout << "There is " << getNumberPassportsValidsPart1(lPassports) << endl;

    cout << "Part 1 : number passports valids : " << getNumberPassportsValidsPart1(lPassports) << endl;
    
    return EXIT_SUCCESS;
}

