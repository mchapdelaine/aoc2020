#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

pair<unsigned int, string> getMem(const string& pMem)
{
    unsigned int lAddress;

    auto lAddressEnd = pMem.find("]");
    lAddress = stoul(pMem.substr(4, lAddressEnd));

    return pair<unsigned int, string>(lAddress, pMem.substr(lAddressEnd + 4));
}

string getMask(const string& pMask)
{
    return pMask.substr(7);
}

uint64_t applyMask(const std::string& pMask, const std::string& pValue)
{
    if (pMask.length() != 36)
    {
        throw runtime_error("Wrong mask size");
    }

    uint64_t lValue = stoull(pValue);

    for (unsigned int i = 0; i < 36; i++)
    {
        if (pMask[35 - i] == '0')
        {
            lValue &= ~(1ULL << i);
        }
        else if (pMask[35 - i] == '1')
        {
            lValue |= 1ULL << i;
        }
    }

    return lValue;
}

uint64_t getPart1(const vector<string>& pInput)
{
    map<unsigned int, uint64_t> lMemory;
    string lCurrentMask;

    for (const auto lLine : pInput)
    {
        if (lLine.substr(0,2) == "ma")
        {
            lCurrentMask = getMask(lLine);
        }
        else if (lLine.substr(0,2) == "me")
        {
            auto lResult = getMem(lLine);
            lMemory[lResult.first] = applyMask(lCurrentMask, lResult.second);
        }
    }

    uint64_t lValue = 0;

    for (const auto lCurrentMapValue : lMemory)
    {
        lValue += lCurrentMapValue.second;
    }

    return lValue;
}


int main(int pArgc, char** pArgv) 
{
    cout << "Day 14\n";

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
    vector<string> lInput;
    
    while (getline(lInputFile, lTemp))
    {
        lInput.emplace_back(lTemp);
    }

    uint64_t lPart1Value = getPart1(lInput);

    cout << "Part 1 : " << lPart1Value << endl;


    return EXIT_SUCCESS;
}
