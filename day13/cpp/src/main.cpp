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

    if (pValues.size() == 0)
    {
        return 0;
    }

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

// Brute force part 2. Works with example, not with dataset
uint64_t part2(const vector<pair<unsigned int, unsigned int>>& pValues)
{
    uint64_t lTimeStamp = 0;
    const unsigned int lNumberValues = pValues.size();

    if (lNumberValues == 0)
    {
        return 0;
    }

    // Initialize all timestamps to 0
    uint64_t lCurrentTimeStamps[lNumberValues] = { 0 };

    // There is not too many values, cache, will be faster than using vector
    unsigned int lOffsetsCache[lNumberValues];
    unsigned int lValuesCache[lNumberValues];
    for (unsigned int i = 0; i < lNumberValues; i++)
    {
        lValuesCache[i] = pValues[i].first;
        lOffsetsCache[i] = pValues[i].second;
    }

    bool lFound = false;

    uint64_t lLoopNumber = 1;

    while (!lFound)
    {
        lTimeStamp = lValuesCache[0] * lLoopNumber;

        lFound = true;

        for (unsigned i = 1; i < lNumberValues; i++)
        {
            if (lCurrentTimeStamps[i] < lTimeStamp)
            {
                uint64_t lDiv = lTimeStamp / lValuesCache[i];
                lDiv++;

                lCurrentTimeStamps[i] = lValuesCache[i] * lDiv;
            }

            if (lCurrentTimeStamps[i] - lOffsetsCache[i] != lTimeStamp)
            {
                lFound = false;
                break;
            }
        }

        lLoopNumber++;
    }

    return lTimeStamp;
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

    vector<pair<unsigned int, unsigned int>> lPart2Values;
    
    getline(lInputFile, lTimestamp);
    getline(lInputFile, lIdsString);

    stringstream lIdsStream(lIdsString);

    string lTemp;
    for (unsigned int i = 0; getline(lIdsStream, lTemp, ',');i++)
    {
        if (lTemp != "x")
        {
            lIds.emplace_back(stoul(lTemp));
            lPart2Values.emplace_back(stoul(lTemp), i);
            cout << "Got value " << stoul(lTemp) << " with offset " << i << endl;
        }
    }


    // unsigned int lPart1 = part1(stoul(lTimestamp), lIds);
    // cout << "Part 1 is : " << lPart1 << endl;

    uint64_t lPart2 = part2(lPart2Values);
    cout << "Part 2 is : " << lPart2 << endl;

    return EXIT_SUCCESS;
}
