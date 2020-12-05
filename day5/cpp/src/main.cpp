#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "BoardingPassClass.h"

using namespace std;

unsigned int findMax(const vector<BoardingPassClass>& pPasses)
{
    unsigned int lMax = 0;

    for (const auto lPass : pPasses)
    {
        if (lPass.getId() > lMax)
        {
            lMax = lPass.getId();
        }
    }

    return lMax;
}

unsigned int findMin(const vector<BoardingPassClass>& pPasses)
{
    // Invalid ID (too high), to start
    unsigned int lMin = 128 * 8 + 8 + 1;

    for (const auto lPass : pPasses)
    {
        if (lPass.getId() < lMin)
        {
            lMin = lPass.getId();
        }
    }

    return lMin;
}

bool isIdExist(unsigned int lId, const vector<BoardingPassClass>& pPasses)
{
    bool lExist = false;
    for (const auto lPass : pPasses)
    {
        if (lPass.getId() == lId)
        {
            lExist = true;
            break;
        }
    }

    return lExist;
}

unsigned int isMissingBetween(const vector<BoardingPassClass>& pPasses)
{
    unsigned int lMin = findMin(pPasses);
    unsigned int lMax = findMax(pPasses);

    unsigned int lIsMissing = 0;

    for (unsigned i = lMin; i < lMax; i++)
    {
        if (!isIdExist(i, pPasses))
        {
            lIsMissing = i;
            break;
        }
    }

    return lIsMissing;
}


// Fillseats and displayPlane are bonuses .. display like the boarding machine at airports ;)
void fillSeats(std::string& pSeats, const vector<BoardingPassClass>& pPasses)
{
    for (const auto lPass : pPasses)
    {
        pSeats[lPass.getId()] = 'X';
    }
}

void displayPlane(const std::string& pSeats)
{
    for (unsigned lRow = 0; lRow < 128; lRow++)
    {
        cout << " Row " << lRow << "   ";
        for (unsigned lColumn = 0; lColumn < 7; lColumn++)
        {
            cout << pSeats[lRow * 8 + lColumn];
            if (lColumn == 3)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}


int main(int pArgc, char** pArgv) 
{
    cout << "Day 5\n";
    
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

    vector<BoardingPassClass> lPasses;
    
    while (getline(lInputFile, lTemp))
    {
        lPasses.emplace_back(BoardingPassClass(lTemp));
    }

    cout << "For part 1, the max is : " << findMax(lPasses) << endl; 
    cout << "For part 2, Missing ID : " << isMissingBetween(lPasses) << endl;

    // Bonus for fun
    string lSeatPositions = "";

    for (unsigned int i = 0; i < 127 * 8 + 7; i++)
    {
        lSeatPositions += "O";
    }
    fillSeats(lSeatPositions, lPasses);
    displayPlane(lSeatPositions);
    

    
    return EXIT_SUCCESS;
}

