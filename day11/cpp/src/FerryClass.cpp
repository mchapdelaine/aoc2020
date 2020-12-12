#include "FerryClass.h"

#include <iostream>

using namespace std;

constexpr char FLOOR_CHAR = '.';
constexpr char EMPTY_SEAT = 'L';
constexpr char OCCUPIED_SEAT = '#';
constexpr unsigned int MAX_LOOPS = 1000000;

//#define DEBUG

FerryClass::FerryClass(const string& pFerryString, unsigned int pRows, unsigned int pSeatsPerRow) :
aFerry(pFerryString),
aRows(pRows),
aSeatsPerRow(pSeatsPerRow)
{
}

void FerryClass::displayFerry(const string& pFerryString, unsigned int pRows, unsigned int pSeatsPerRow)
{
    if (pFerryString.length() < pRows * pSeatsPerRow)
    {
        cout << "Missing data in string\n";
    }

    for (unsigned int i = 0; i < pRows; i++)
    {
        for (unsigned int j = 0; j < pSeatsPerRow; j++)
        {
            cout << pFerryString[(i * pSeatsPerRow) + j];
        }

        cout << endl;
    }
}

unsigned int FerryClass::countOccupiedSeats(const std::string& pFerryString) const
{
    unsigned int lOccupied = 0;
    for (unsigned int i = 0; i < pFerryString.length(); i++)
    {
        if (pFerryString[i] == OCCUPIED_SEAT)
        {
            lOccupied++;
        }
    }

    return lOccupied;
}

unsigned int FerryClass::part1(unsigned int pMaxLoops) const
{
    constexpr unsigned int OCCUPIED_TO_EMPTY = 4;
    constexpr unsigned int EMPTY_TO_OCCUPIED = 0;

    string lPrevious = aFerry;
    string lNext = string(aFerry.size(), ' ');

    bool lDone = false;
    

#ifdef DEBUG
    unsigned int lArraySize = aFerry.size();
    cout << "Array size " << lArraySize << endl;
#endif

    for (unsigned int lMaxLoop = 0; lMaxLoop < pMaxLoops; lMaxLoop++)
    {
#ifdef DEBUG
        cout << " == Ocupied around == \n";
#endif
        for (unsigned int i = 0; i < aRows; i++)
        {
#ifdef DEBUG
            printf("%02u ", i + 1);
#endif
            for (unsigned int j = 0; j < aSeatsPerRow; j++)
            {
                unsigned int lX = i * aSeatsPerRow;
                unsigned int lPreviousPosition = (i * aSeatsPerRow) + j;

                char lCurrentSeat = lPrevious[lPreviousPosition];
                // In the case of a floor tile, just copy the tile
                if (lCurrentSeat == FLOOR_CHAR)
                {
                    lNext[(i * aSeatsPerRow) + j] = FLOOR_CHAR;
#ifdef DEBUG
                    cout << ".";
#endif
                }
                else if (lCurrentSeat == OCCUPIED_SEAT)
                {
                    // Count the number of occupied seats around
                    unsigned int lOccupiedAround = countOccupiedAround(lPrevious, i, j);
#ifdef DEBUG
                    cout << lOccupiedAround;
#endif
                    if (lOccupiedAround >= OCCUPIED_TO_EMPTY)
                    {
                        lNext[(i * aSeatsPerRow) + j] = EMPTY_SEAT;
                    }
                    else
                    {
                        lNext[(i * aSeatsPerRow) + j] = OCCUPIED_SEAT;
                    }
                }
                else if (lCurrentSeat == EMPTY_SEAT)
                {
                    // Count the number of occupied seats around
                    unsigned int lOccupiedAround = countOccupiedAround(lPrevious, i, j);
#ifdef DEBUG
                    cout << lOccupiedAround;
#endif
                    if (countOccupiedAround(lPrevious, i, j) == EMPTY_TO_OCCUPIED)
                    {
                        lNext[(i * aSeatsPerRow) + j] = OCCUPIED_SEAT;
                    }
                    else
                    {
                        lNext[(i * aSeatsPerRow) + j] = EMPTY_SEAT;
                    }
                    
                }
            }
#ifdef DEBUG
            cout << "\n";
#endif
        }

#ifdef DEBUG
        cout << " === Loop " << lMaxLoop << " ===\n";
        displayFerry(lNext, aRows, aSeatsPerRow);
        cout << "\n\n";
#endif

        if (lNext == lPrevious)
        {
            lDone = true;
            break;
        }

        lPrevious = lNext;
        lMaxLoop++;
    }

#ifdef DEBUG
        cout << "Done in " << lMaxLoop << " loops\n";
#endif

    if (lDone)
    {
        return countOccupiedSeats(lNext);
    }
    
    return 0;
}

unsigned int FerryClass::countOccupiedAround(const std::string& pFerryString, unsigned int pRow, unsigned int pSeat) const
{
    // Do not check if the Row or seat are sanitized... This code will work ;)

    unsigned int lOccupied = 0;

    // Checks the seats around
    // 123
    // 4 5
    // 678

    unsigned int lSeatPosition;

    if (pRow != 0)
    {
        // Check seat 1
        if (pSeat != 0)
        {
            lSeatPosition = ((pRow - 1) * aSeatsPerRow) + pSeat - 1;
            if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
            {
                lOccupied++;
            }
        }

        // Check seat 2
        lSeatPosition = ((pRow - 1) * aSeatsPerRow) + pSeat;
        if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
        {
            lOccupied++;
        }

        // Check seat 3
        if (pSeat != aSeatsPerRow - 1)
        {
            lSeatPosition = ((pRow - 1) * aSeatsPerRow) + pSeat + 1;
            if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
            {
                lOccupied++;
            }
        }
    }

    // Check seat 4
    if (pSeat != 0)
    {
        lSeatPosition = (pRow * aSeatsPerRow) + pSeat - 1;
        if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
        {
            lOccupied++;
        }
    }

    // Check seat 5
    if (pSeat != aSeatsPerRow - 1)
    {
        lSeatPosition = (pRow * aSeatsPerRow) + pSeat + 1;
        if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
        {
            lOccupied++;
        }
    }

    if (pRow != aRows - 1)
    {
        // Check seat 6
        if (pSeat != 0)
        {
            lSeatPosition = ((pRow + 1) * aSeatsPerRow) + pSeat - 1;
            if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
            {
                lOccupied++;
            }
        }

        // Check seat 7
        lSeatPosition = ((pRow + 1) * aSeatsPerRow) + pSeat;
        if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
        {
            lOccupied++;
        }

        // Check seat 8
        if (pSeat != aSeatsPerRow - 1)
        {
            lSeatPosition = ((pRow + 1) * aSeatsPerRow) + pSeat + 1;
            if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
            {
                lOccupied++;
            }
        }
    }

    return lOccupied;
}