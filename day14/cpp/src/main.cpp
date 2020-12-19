#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

pair<uint64_t, string> getMem(const string& pMem)
{
    uint64_t lAddress;

    auto lAddressEnd = pMem.find("]");
    lAddress = stoull(pMem.substr(4, lAddressEnd));

    return pair<uint64_t, string>(lAddress, pMem.substr(lAddressEnd + 4));
}

string getMask(const string& pMask)
{
    return pMask.substr(7);
}

uint64_t applyMask(const std::string& pMask, uint64_t pValue)
{
    if (pMask.length() != 36)
    {
        throw runtime_error("Wrong mask size");
    }
    uint64_t lValue = pValue;

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

uint64_t applyMask(const std::string& pMask, const std::string& pValue)
{
    uint64_t lValue = stoull(pValue);
    return applyMask(pMask, lValue);
}

uint64_t sumMemory(const map<uint64_t, uint64_t>& pMemory)
{
    uint64_t lValue = 0;

    for (const auto lCurrentMapValue : pMemory)
    {
        lValue += lCurrentMapValue.second;
    }

    return lValue;
}

uint64_t getPart1(const vector<string>& pInput)
{
    map<uint64_t, uint64_t> lMemory;
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

    return sumMemory(lMemory);
}

void addValues(unsigned int lLevel, const std::string& pMask, const vector<uint64_t>& pPositionValues, vector<string>& pAllMasks)
{
    string lLevelMask = pMask; 

    if (lLevel == pPositionValues.size() - 1)
    {
        pAllMasks.emplace_back(lLevelMask);
        lLevelMask[pPositionValues[lLevel]] = '1';
        pAllMasks.emplace_back(lLevelMask);
    }
    else
    {
        addValues(lLevel + 1, lLevelMask, pPositionValues, pAllMasks);
        lLevelMask[pPositionValues[lLevel]] = '1';
        addValues(lLevel + 1, lLevelMask, pPositionValues, pAllMasks);
    }
}

string memoryToString(uint64_t pMemory)
{
    string lResult;

    for (unsigned int i = 0; i < 36; i++)
    {
        uint64_t lA = (1ULL << (35 - i));
        uint64_t lB = pMemory & (1ULL << (35 - i));
        if (lB == 0)
        {
            lResult += "0";
        }
        else
        {
            lResult += "1";
        }
    }

    return lResult;
}

uint64_t stringToMemory(const std::string& pValue)
{
    if (pValue.size() != 36)
    {
        throw runtime_error("Memory string length");
    }

    uint64_t lValue = 0;

    for (unsigned int i = 0; i < 36; i++)
    {
        if (pValue[35 - i] == '1')
        {
            lValue += (1ULL << i);
        }
    }

    return lValue;
}

string setMaskToMemory(const std::string& pMask, const std::string& pMemory)
{
    if (pMask.size() != 36 || pMemory.size() != 36)
    {
        throw runtime_error("Wrong mask length or memory string length");
    }

    string lResult;
    for (unsigned int i = 0; i < 36; i++)
    {
        if (pMask[i] == 'X')
        {
            lResult += "X";
        }
        else if (pMask[i] == '0')
        {
            lResult += pMemory[i];
        }
        else if (pMask[i] == '1')
        {
            lResult += "1";
        }
    }

    return lResult;
}

vector<uint64_t> getAllAddresses(const std::string& pMask, uint64_t pMemory)
{
    vector<uint64_t> lAllXPositions;
    vector<string> lAllMasks;

    string lNewMaskWith0 = setMaskToMemory(pMask, memoryToString(pMemory));

    if (pMask.length() != 36)
    {
        throw runtime_error("Wrong mask size");
    }

    for (unsigned int i = 0; i < 36; i++)
    {
        if (pMask[i] == 'X')
        {
            lAllXPositions.emplace_back(i);
            lNewMaskWith0[i] = '0';
        }
    }

    // Get all masks
    addValues(0, lNewMaskWith0, lAllXPositions, lAllMasks);

    vector<uint64_t> lAllValues;
    for (const auto lMask : lAllMasks)
    {
        lAllValues.emplace_back(stringToMemory(lMask));
    }

    return lAllValues;
}

uint64_t getPart2(const vector<string>& pInput)
{
    map<uint64_t, uint64_t> lMemory;
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
            auto lAllAddresses = getAllAddresses(lCurrentMask, lResult.first);

            for (const auto lAllAddress : lAllAddresses)
            {
                lMemory[lAllAddress] = stoull(lResult.second);
            }
        }
    }

    return sumMemory(lMemory);
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

    uint64_t lPart2Value = getPart2(lInput);
    cout << "Part 2 : " << lPart2Value << endl;

    return EXIT_SUCCESS;
}
