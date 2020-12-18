#include "FerryClass.h"

#include <iostream>

using namespace std;

constexpr char FLOOR_CHAR = '.';
constexpr char EMPTY_SEAT = 'L';
constexpr char OCCUPIED_SEAT = '#';
constexpr unsigned int MAX_LOOPS = 1000000;

//#define DEBUG
//#define DEBUG2

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
    unsigned int lMaxLoop = 0;
    for (; lMaxLoop < pMaxLoops; lMaxLoop++)
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

unsigned int FerryClass::part2(unsigned int pMaxLoops) const
{
    constexpr unsigned int OCCUPIED_TO_EMPTY = 5;
    constexpr unsigned int EMPTY_TO_OCCUPIED = 0;
    string lPrevious = aFerry;
    string lNext = string(aFerry.size(), ' ');

    bool lDone = false;
    

#ifdef DEBUG2
    unsigned int lArraySize = aFerry.size();
    cout << "Array size " << lArraySize << endl;
#endif
    unsigned int lMaxLoop = 0;
    for (; lMaxLoop < pMaxLoops; lMaxLoop++)
    {
#ifdef DEBUG2
        cout << " == Ocupied around == \n";
#endif
        for (unsigned int i = 0; i < aRows; i++)
        {
#ifdef DEBUG2
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
#ifdef DEBUG2
                    cout << ".";
#endif
                }
                else if (lCurrentSeat == OCCUPIED_SEAT)
                {
                    // Count the number of occupied seats around
                    unsigned int lOccupiedAround = countOccupiedAround2(lPrevious, i, j);
#ifdef DEBUG2
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
                    unsigned int lOccupiedAround = countOccupiedAround2(lPrevious, i, j);
#ifdef DEBUG2
                    cout << lOccupiedAround;
#endif
                    if (lOccupiedAround == EMPTY_TO_OCCUPIED)
                    {
                        lNext[(i * aSeatsPerRow) + j] = OCCUPIED_SEAT;
                    }
                    else
                    {
                        lNext[(i * aSeatsPerRow) + j] = EMPTY_SEAT;
                    }
                    
                }
            }
#ifdef DEBUG2
            cout << "\n";
#endif
        }

#ifdef DEBUG2
        cout << " === Part 2 Loop " << lMaxLoop << " ===\n";
        displayFerry(lNext, aRows, aSeatsPerRow);
        cout << "\n\n";
#endif

        if (lNext == lPrevious)
        {
            lDone = true;
            break;
        }

        lPrevious = lNext;
    }

#ifdef DEBUG2
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


//#define INTENSIVE_DEBUG_2
unsigned int FerryClass::countOccupiedAround2(const std::string& pFerryString, unsigned int pRow, unsigned int pSeat) const
{
    // Do not check if the Row or seat are sanitized... This code will work ;)

    unsigned int lOccupied = 0;

    // Checks the seats around (directions)
    // 123
    // 4 5
    // 678

#ifdef INTENSIVE_DEBUG_2
    bool lIntenseDebug = false;

    if (pRow == 0 && pSeat == 2)
    {
        lIntenseDebug = true;
    }
#endif

    unsigned int lSeatPosition;
    bool lSeatFound;

    if (pRow != 0)
    {
        // Check seat direction 1
        if (pSeat != 0)
        {
            lSeatFound = false;
            int i = pRow - 1;
            int j = pSeat - 1;

#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "SEAT 1:\n";
            }
#endif

            do
            {
                lSeatPosition = (i * aSeatsPerRow) + j;

#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "  Testing seat 1 @ " << i << ", " << j << endl;
                }
#endif
                if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
                {
                    lOccupied++;
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found seat 1 @ " << i << ", " << j << endl;
                    }
#endif
                }
                else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
                {
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Empty seat 1 @ " << i << ", " << j << endl;
                    }
#endif
                }
                i--;
                j--;
            }
            while ((i >= 0) && (j >= 0) && !lSeatFound);

        }

        // Check seat direction 2
        {
            lSeatFound = false;
            int i = pRow - 1;

#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "SEAT 2:\n";
            }
#endif

            do
            {
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "  Testing seat 2 @ " << i << ", " << pSeat << endl;
                }
#endif
                lSeatPosition = (i * aSeatsPerRow) + pSeat;
                if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
                {
                    lOccupied++;
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found seat 2 @ " << i << ", " << pSeat << endl;
                    }
#endif
                }
                else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
                {
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found empty seat 2 @ " << i << ", " << pSeat << endl;
                    }
#endif
                }
                i--;
            }
            while ((i >= 0) && !lSeatFound);
        }

        // Check seat direction 3
        if (pSeat != aSeatsPerRow - 1)
        {
            lSeatFound = false;
            int i = pRow - 1;
            int j = pSeat + 1;

#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "SEAT 3:\n";
            }
#endif

            do
            {
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "  Testing seat 3 @ " << i << ", " << j << endl;
                }
#endif
                lSeatPosition = (i * aSeatsPerRow) + j;
                if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
                {
                    lOccupied++;
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found seat 3 @ " << i << ", " << j << endl;
                    }
#endif
                }
                else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
                {
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found empty seat 3 @ " << i << ", " << j << endl;
                    }
#endif
                }
                i--;
                j++;
            }
            while ((i >= 0) && (j < aSeatsPerRow) && !lSeatFound);
        }
    }

    // Check seat 4
    if (pSeat != 0)
    {
        lSeatFound = false;
        int j = pSeat - 1;

#ifdef INTENSIVE_DEBUG_2
        if (lIntenseDebug)
        {
            cout << "SEAT 4:\n";
        }
#endif

        do
        {
#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "  Testing seat 4 @ " << pRow << ", " << j << endl;
            }
#endif
            lSeatPosition = (pRow * aSeatsPerRow) + j;
            if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
            {
                lOccupied++;
                lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "    Found seat 4 @ " << pRow << ", " << j << endl;
                }
#endif
            }
            else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
            {
                lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "    Found empty seat 4 @ " << pRow << ", " << j << endl;
                }
#endif
            }
            j--;
        }
        while ((j >= 0) && !lSeatFound);

    }

    // Check seat 5
    if (pSeat != aSeatsPerRow - 1)
    {
        lSeatFound = false;
        int j = pSeat + 1;

#ifdef INTENSIVE_DEBUG_2
        if (lIntenseDebug)
        {
            cout << "SEAT 5:\n";
        }
#endif

        do
        {
#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "  Testing seat 5 @ " << pRow << ", " << j << endl;
            }
#endif
            lSeatPosition = (pRow * aSeatsPerRow) + j;
            if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
            {
                lOccupied++;
                lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "    Found seat 5 @ " << pRow << ", " << j << endl;
                }
#endif
            }
            else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
            {
                lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "    Found empty seat 5 @ " << pRow << ", " << j << endl;
                }
#endif
            }
            j++;
        }
        while ((j < aSeatsPerRow) && !lSeatFound);
    }

    if (pRow != aRows - 1)
    {
        // Check seat 6
        if (pSeat != 0)
        {
            lSeatFound = false;
            int i = pRow + 1;
            int j = pSeat - 1;

#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "SEAT 6:\n";
            }
#endif

            do
            {
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "  Testing seat 6 @ " << i << ", " << j << endl;
                }
#endif
                lSeatPosition = (i * aSeatsPerRow) + j;
                if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
                {
                    lOccupied++;
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found seat 6 @ " << i << ", " << j << endl;
                    }
#endif
                }
                else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
                {
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found empty seat 6 @ " << i << ", " << j << endl;
                    }
#endif
                }
                i++;
                j--;
            }
            while ((i < aRows) && (j >= 0) && !lSeatFound);

        }

        // Check seat 7
        {
            lSeatFound = false;
            int i = pRow + 1;

#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "SEAT 7:\n";
            }
#endif

            do
            {
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "  Testing seat 7 @ " << i << ", " << pSeat << endl;
                }
#endif
                lSeatPosition = (i * aSeatsPerRow) + pSeat;
                if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
                {
                    lOccupied++;
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found seat 7 @ " << i << ", " << pSeat << endl;
                    }
#endif
                }
                else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
                {
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found empty seat 7 @ " << i << ", " << pSeat << endl;
                    }
#endif
                }
                i++;
            }
            while ((i < aRows) && !lSeatFound);
        }

        // Check seat 8
        if (pSeat != aSeatsPerRow - 1)
        {
            lSeatFound = false;
            int i = pRow + 1;
            int j = pSeat + 1;

#ifdef INTENSIVE_DEBUG_2
            if (lIntenseDebug)
            {
                cout << "SEAT 8:\n";
            }
#endif

            do
            {
#ifdef INTENSIVE_DEBUG_2
                if (lIntenseDebug)
                {
                    cout << "  Testing seat 8 @ " << i << ", " << j << endl;
                }
#endif
                lSeatPosition = (i * aSeatsPerRow) + j;
                if (pFerryString[lSeatPosition] == OCCUPIED_SEAT)
                {
                    lOccupied++;
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found seat 8 @ " << i << ", " << j << endl;
                    }
#endif
                }
                else if (pFerryString[lSeatPosition] == EMPTY_SEAT)
                {
                    lSeatFound = true;
#ifdef INTENSIVE_DEBUG_2
                    if (lIntenseDebug)
                    {
                        cout << "    Found empty seat 8 @ " << i << ", " << j << endl;
                    }
#endif
                }
                i++;
                j++;
            }
            while ((i < aRows) && (j < aSeatsPerRow) && !lSeatFound);
        }
    }

#ifdef INTENSIVE_DEBUG_2
    if (lIntenseDebug)
    {
        cout << "Got " << lOccupied << " Occupied seats\n";
    }
#endif

    return lOccupied;
}