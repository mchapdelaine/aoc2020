#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

unsigned int part1(unsigned int pTimeStamp, const vector<unsigned int>& pValues)
{
    unsigned int lIdMin = pTimeStamp;
    unsigned int lDifferenceMin = pTimeStamp;

    for (const auto lValue : pValues)
    {
        unsigned int lDiv = pTimeStamp / lValue;
        
        // Check the next bus
        lDiv++;

        // Calc difference
        unsigned int lDifference = (lDiv * lValue) - pTimeStamp;

        if (lDifference < lDifferenceMin)
        {
            lDifferenceMin = lDifference;
            lIdMin = lValue;
        }
    }

    return lIdMin * lDifferenceMin;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 13\n";
    
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
    
    string lTimestamp;
    string lIdsString;
    vector<unsigned int> lIds;
    
    getline(lInputFile, lTimestamp);
    getline(lInputFile, lIdsString);

    stringstream lIdsStream(lIdsString);

    string lTemp;
    for (unsigned int i; getline(lIdsStream, lTemp, ',');)
    {
        if (lTemp != "x")
        {
            lIds.emplace_back(stoul(lTemp));
        }
    }

    unsigned int lPart1 = part1(stoul(lTimestamp), lIds);
    cout << "Part 1 is : " << lPart1 << endl;

    return EXIT_SUCCESS;
}
