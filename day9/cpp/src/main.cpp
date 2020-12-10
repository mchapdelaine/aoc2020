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

int main(int pArgc, char** pArgv) 
{
    cout << "Day 9\n";
    
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
    vector<uint64_t> lValues;
    
    while (getline(lInputFile, lTemp))
    {
        lValues.emplace_back(stoull(lTemp));
    }

    cout << "Part 1 : the invalid value is " << findInvalidValue(lValues, 25) << endl;

    return EXIT_SUCCESS;
}
