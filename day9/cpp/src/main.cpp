#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

uint64_t findInvalidValue(vector<uint64_t> pValues, unsigned int pFirstNumbers)
{
    if (pValues.size() < pFirstNumbers + 1)
    {
        throw runtime_error("Not enough elements");
    }

    for (unsigned int lCurrentNumber = pFirstNumbers; lCurrentNumber < pValues.size(); lCurrentNumber++ )
    {
        bool lFound = false;
        for (unsigned int lX = lCurrentNumber - pFirstNumbers; lX < lCurrentNumber; lX++)
        {
            for (unsigned int lY = lCurrentNumber - pFirstNumbers; lY < lCurrentNumber; lY++)
            {
                if (lX == lY)
                {
                    continue;
                }

                if (pValues[lCurrentNumber] == pValues[lX] + pValues[lY])
                {
                    lFound = true;
                    break;
                }
            }

            if (lFound)
            {
                break;
            }
        }

        if (!lFound)
        {
            return pValues[lCurrentNumber];
        }
    }

    return 0;
}

uint64_t resultFindRange(vector<uint64_t> pValues, uint64_t pValueToSearch)
{
    // Erase the value we search and all values that are over the limit
    vector<uint64_t> lValues;
    for (const auto lValue : pValues)
    {
        if (lValue < pValueToSearch)
        {
            lValues.emplace_back(lValue);
        }
    }

    if (lValues.size() < 2)
    {
        throw std::runtime_error("Invalid number of entries");
    }

    for (unsigned int lNumberNumbers = 2; lNumberNumbers < lValues.size() - 2; lNumberNumbers++)
    {
        for (unsigned int i = 0; i < lValues.size() - lNumberNumbers; i++)
        {
            uint64_t lSum = 0;
            for (unsigned int j = i; j < i + lNumberNumbers; j++)
            {
                lSum += lValues[j];
            }

            if (lSum == pValueToSearch)
            {
                uint64_t lMin = lValues[i];
                uint64_t lMax = lValues[i];

                for (unsigned int j = i; j < i + lNumberNumbers; j++)
                {
                    if (lValues[j] > lMax)
                    {
                        lMax = lValues[j];
                    }

                    if (lValues[j] < lMin)
                    {
                        lMin = lValues[j];
                    }
                }
                return lMax + lMin;
            }
        }
    }

    return 0;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 9\n";
    
    if (pArgc < 3)
    {
        cout << "Missing input file name or number to check\n";
        return EXIT_FAILURE;
    }

    unsigned int lNumbers = stoul(pArgv[2]);
    
    ifstream lInputFile(pArgv[1], std::ifstream::in);

    if (!lInputFile.is_open())
    {
        cout << "Could not open " << pArgv[1] << ", exit\n";
        return EXIT_FAILURE;
    }
    
    string lTemp;
    vector<uint64_t> lValues;
    
    while (getline(lInputFile, lTemp))
    {
        lValues.emplace_back(stoull(lTemp));
    }

    cout << "There is " << lValues.size() << " values\n";

    uint64_t lPart1 = findInvalidValue(lValues, lNumbers);
    cout << "Part 1 : the invalid value is : " << lPart1 << endl;

    uint64_t lPart2 = resultFindRange(lValues, lPart1);
    cout << "Part 2 : the sum is           : " << lPart2 << endl;

    return EXIT_SUCCESS;
}
