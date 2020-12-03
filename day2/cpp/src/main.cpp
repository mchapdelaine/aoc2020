#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "PasswordClass.h"

using namespace std;

unsigned int numberTestValids(const vector<PasswordClass>& pTests)
{
    unsigned int lCount = 0;
    for (const auto lTest : pTests)
    {
        if (lTest.isValid())
        {
            lCount++;
        }
    }
    
    return lCount;
}

unsigned int numberTestValids2(const vector<PasswordClass>& pTests)
{
    unsigned int lCount = 0;
    for (const auto lTest : pTests)
    {
        if (lTest.isValid2())
        {
            lCount++;
        }
    }
    
    return lCount;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 2\n";
    
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
    vector<PasswordClass> lTests;
    
    while (getline(lInputFile, lTemp))
    {
        lTests.emplace_back(PasswordClass(lTemp));
    }
    
    cout << "There is " << numberTestValids(lTests) << " test valids\n";
    cout << "There is " << numberTestValids2(lTests) << " test valids for critera 2\n";
    
    return EXIT_SUCCESS;
}

