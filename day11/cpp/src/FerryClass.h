#pragma once

#include <string>

class FerryClass
{
public:
    FerryClass(const std::string& pFerryString, unsigned int pRows, unsigned int pSeatsPerRow);
    virtual ~FerryClass() = default;
    FerryClass(const FerryClass& pCopy) = default;
    FerryClass(FerryClass&& pMove) = default;

    unsigned int part1(unsigned int pMaxLoops) const;
    unsigned int part2(unsigned int pMaxLoops) const;

    static void displayFerry(const std::string& pFerryString, unsigned int pRows, unsigned int pSeatsPerRow);
    inline void displayFerry() const { displayFerry(aFerry, aRows, aSeatsPerRow); } 

private:
    unsigned int countOccupiedAround(const std::string& pFerryString, unsigned int pRow, unsigned int pSeat) const;
    unsigned int countOccupiedAround2(const std::string& pFerryString, unsigned int pRow, unsigned int pSeat) const;

    unsigned int countOccupiedSeats(const std::string& pFerryString) const;

    std::string aFerry;
    unsigned int aRows;
    unsigned int aSeatsPerRow;
};
