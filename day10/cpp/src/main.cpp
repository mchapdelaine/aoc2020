#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

unsigned int calc1and3Jolts(const vector<unsigned int>& pValues, unsigned int& pNumber1Jolt,  unsigned int& pNumber3Jolt)
{
    if (pValues.size() < 2)
    {
        return 0;
    }

    unsigned int lSteps = 1;

    for (; lSteps < pValues.size(); lSteps++)
    {
        if (pValues[lSteps] == pValues[lSteps - 1] + 1)
        {
            pNumber1Jolt++;
        }
        else if (pValues[lSteps] == pValues[lSteps - 1] + 3)
        {
            pNumber3Jolt++;
        }
        else if (pValues[lSteps] >= pValues[lSteps - 1] + 3)
        {
            return lSteps;
        }
    }

    return lSteps;
}

// Not Efficient
uint64_t calcArangments(const vector<unsigned int>& pValues, unsigned int pIndex)
{
    uint64_t lArrangment = 0;

    if (pValues.size() - 1 == pIndex)
    {
        return 1;
    }

    unsigned int i = pIndex + 1;
    for (; i < pValues.size(); i++)
    {
        // Valid, continue
        if (pValues[pIndex] + 3 >= pValues[i])
        {
            lArrangment += calcArangments(pValues, i);
        }
        else
        {
            // Not valid anymore, break;
            break;
        }
    }

    return lArrangment;
}

// Not Efficient, faster structures
uint64_t calcArangments2(const unsigned short* pValues, unsigned int pSize, unsigned int pIndex)
{
    uint64_t lArrangment = 0;

    if (pSize - 1 == pIndex)
    {
        return 1;
    }

    unsigned int i = pIndex + 1;
    for (; i < pSize; i++)
    {
        // Valid, continue
        if (pValues[pIndex] + 3 >= pValues[i])
        {
            lArrangment += calcArangments2(pValues, pSize, i);
        }
        else
        {
            // Not valid anymore, break;
            break;
        }
    }

    return lArrangment;
}

// Seach from the end first. Same result.
// "Bruteforcing" is working for the examples, but the input is too large.
// We need to split the workload in multiple sections
uint64_t calcArangments4(const unsigned short* pValues, unsigned int pSize, unsigned int pIndex)
{
    uint64_t lArrangment = 0;

    if (pSize - 1 == pIndex)
    {
        return 1;
    }

    unsigned int i = pIndex + 1;
    for (; i < pSize; i++)
    {
        // Valid, continue
        if (pValues[pIndex] <= pValues[i] + 3)
        {
            lArrangment += calcArangments4(pValues, pSize, i);
        }
        else
        {
            // Not valid anymore, break;
            break;
        }
    }

    return lArrangment;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 10\n";
    
    if (pArgc < 2)
    {
        cout << "Missing input file name or number to check\n";
        return EXIT_FAILURE;
    }
    
    ifstream lInputFile(pArgv[1], std::ifstream::in);

    if (!lInputFile.is_open())
    {
        cout << "Could not open " << pArgv[1] << ", exit\n";
        return EXIT_FAILURE;
    }
    
    string lTemp;
    vector<unsigned int> lValues;
    
    while (getline(lInputFile, lTemp))
    {
        lValues.emplace_back(stoul(lTemp));
    }

    // Insert outlet of 0 Jolts
    lValues.emplace_back(0);

    sort(lValues.begin(), lValues.end());

    // Insert the device 3 Jolts difference
    lValues.emplace_back(lValues[lValues.size() - 1] + 3);

    unsigned int lNumber1jolt = 0;
    unsigned int lNumber3jolt = 0;

    calc1and3Jolts(lValues, lNumber1jolt, lNumber3jolt);

    cout << "For part 1, there is 1 Jolts steps " << lNumber1jolt << " and 3 Jolts steps " <<  lNumber3jolt << " and the answer is " << lNumber1jolt * lNumber3jolt << endl;

    unsigned short lValuesShort[lValues.size()];

    auto lValues2 = lValues;
    sort(lValues2.begin(), lValues2.end(), [] (unsigned int& a, unsigned int& b) { return a > b; });

    for (unsigned int i = 0; i < lValues2.size() ;i++)
    {
        lValuesShort[i] = static_cast<unsigned short>(lValues2[i]);
    }


    uint64_t lNumberArrangment = calcArangments4(lValuesShort, lValues.size(), 0);

    cout << "For part 2, there is " << lNumberArrangment << " arrangments\n";

    return EXIT_SUCCESS;
}
