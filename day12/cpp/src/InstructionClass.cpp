#include "InstructionClass.h"

#include <stdexcept>
#include <iostream>

using namespace std;

InstructionClass::InstructionClass(const std::vector<std::string>& pInstructions) :
aInstructions(pInstructions)
{
}

InstructionClass::DirectionEnum InstructionClass::getDirectionRight(DirectionEnum pStart, unsigned int pDegrees)
{
    if (pDegrees == 90)
    {
        switch (pStart)
        {
        case DirectionEnum::EAST:
            return DirectionEnum::SOUTH;
        case DirectionEnum::SOUTH:
            return DirectionEnum::WEST;
        case DirectionEnum::WEST:
            return DirectionEnum::NORTH;
        case DirectionEnum::NORTH:
            return DirectionEnum::EAST;
        }
    }
    else if (pDegrees == 180)
    {
        switch (pStart)
        {
        case DirectionEnum::EAST:
            return DirectionEnum::WEST;
        case DirectionEnum::SOUTH:
            return DirectionEnum::NORTH;
        case DirectionEnum::WEST:
            return DirectionEnum::EAST;
        case DirectionEnum::NORTH:
            return DirectionEnum::SOUTH;
        }
    }
    else if (pDegrees == 270)
    {
        switch (pStart)
        {
        case DirectionEnum::EAST:
            return DirectionEnum::NORTH;
        case DirectionEnum::SOUTH:
            return DirectionEnum::EAST;
        case DirectionEnum::WEST:
            return DirectionEnum::SOUTH;
        case DirectionEnum::NORTH:
            return DirectionEnum::WEST;
        }
    }

    // If here, throw error
    throw runtime_error("Wrong number of degrees");
}

InstructionClass::DirectionEnum InstructionClass::getDirectionLeft(DirectionEnum pStart, unsigned int pDegrees)
{
    if (pDegrees == 90)
    {
        switch (pStart)
        {
        case DirectionEnum::EAST:
            return DirectionEnum::NORTH;
        case DirectionEnum::SOUTH:
            return DirectionEnum::EAST;
        case DirectionEnum::WEST:
            return DirectionEnum::SOUTH;
        case DirectionEnum::NORTH:
            return DirectionEnum::WEST;
        }
    }
    else if (pDegrees == 180)
    {
        switch (pStart)
        {
        case DirectionEnum::EAST:
            return DirectionEnum::WEST;
        case DirectionEnum::SOUTH:
            return DirectionEnum::NORTH;
        case DirectionEnum::WEST:
            return DirectionEnum::EAST;
        case DirectionEnum::NORTH:
            return DirectionEnum::SOUTH;
        }
    }
    else if (pDegrees == 270)
    {
        switch (pStart)
        {
        case DirectionEnum::EAST:
            return DirectionEnum::SOUTH;
        case DirectionEnum::SOUTH:
            return DirectionEnum::WEST;
        case DirectionEnum::WEST:
            return DirectionEnum::NORTH;
        case DirectionEnum::NORTH:
            return DirectionEnum::EAST;
        }
    }

    // If here, throw error
    throw runtime_error("Wrong number of degrees");
}

void InstructionClass::processWaypointRight(unsigned int pDegrees, int& pSouthNorth, int& pWestEast)
{
    // Copy values
    const int lSouthNorth = pSouthNorth;
    const int lWestEast = pWestEast;

    if (pDegrees == 90)
    {
        // North ==> East
        // South ==> West
        pWestEast = lSouthNorth;
        
        // East ==> South
        // West ==> North 
        pSouthNorth = -lWestEast;
    }
    else if (pDegrees == 180)
    {
        pSouthNorth = -lSouthNorth;
        pWestEast = -lWestEast;
    }
    else if (pDegrees == 270)
    {
        // North ==> West
        // South ==> East
        pWestEast = -lSouthNorth;
        
        // East ==> North
        // West ==> South 
        pSouthNorth = lWestEast;
    }
}


void InstructionClass::processWaypointLeft(unsigned int pDegrees, int& pSouthNorth, int& pWestEast)
{
    // Copy values
    const int lSouthNorth = pSouthNorth;
    const int lWestEast = pWestEast;

    if (pDegrees == 90)
    {
        // North ==> West
        // South ==> East
        pWestEast = -lSouthNorth;
        
        // East ==> North
        // West ==> South 
        pSouthNorth = lWestEast;
    }
    else if (pDegrees == 180)
    {
        pSouthNorth = -lSouthNorth;
        pWestEast = -lWestEast;
    }
    else if (pDegrees == 270)
    {
        // North ==> East
        // South ==> West
        pWestEast = lSouthNorth;
        
        // East ==> South
        // West ==> North 
        pSouthNorth = -lWestEast;
    }

}

constexpr char NORTH_LETTER = 'N';
constexpr char SOUTH_LETTER = 'S';
constexpr char EAST_LETTER = 'E';
constexpr char WEST_LETTER = 'W';
constexpr char LEFT_LETTER = 'L';
constexpr char RIGHT_LETTER = 'R';
constexpr char FORWARD_LETTER = 'F';

unsigned int InstructionClass::part1ManhattanSum() const
{
    int lSouthNorth = 0; // Negative value means south, positive value means north
    int lWestEast = 0; // Negative value means west, positive value means east
    DirectionEnum lCurrentDirection = DirectionEnum::EAST;

    // Process all instructions
    for (const auto lInstruction : aInstructions)
    {
        // Should not exist, throw error
        if (lInstruction.size() < 2)
        {
            throw runtime_error("Invalid instruction");
        }

        unsigned int lValue = stoul(lInstruction.substr(1));

        if (lInstruction[0] == NORTH_LETTER)
        {
            lSouthNorth += lValue;
        }
        else if (lInstruction[0] == SOUTH_LETTER)
        {
            lSouthNorth -= lValue;
        }
        else if (lInstruction[0] == EAST_LETTER)
        {
            lWestEast += lValue;
        }
        else if (lInstruction[0] == WEST_LETTER)
        {
            lWestEast -= lValue;
        }
        else if (lInstruction[0] == LEFT_LETTER)
        {
            lCurrentDirection = getDirectionLeft(lCurrentDirection, lValue);
        }
        else if (lInstruction[0] == RIGHT_LETTER)
        {
            lCurrentDirection = getDirectionRight(lCurrentDirection, lValue);
        }
        else if (lInstruction[0] == FORWARD_LETTER)
        {
            switch (lCurrentDirection)
            {
            case DirectionEnum::EAST:
                lWestEast += lValue;
                break;
            case DirectionEnum::WEST:
                lWestEast -= lValue;
                break;
            case DirectionEnum::NORTH:
                lSouthNorth += lValue;
                break;
            case DirectionEnum::SOUTH:
                lSouthNorth -= lValue;
                break;
            }
        }
    }

    return abs(lSouthNorth) + abs(lWestEast);
}


unsigned int InstructionClass::part2ManhattanSum() const
{
    int lSouthNorth = 0; // Negative value means south, positive value means north
    int lWestEast = 0; // Negative value means west, positive value means east

    int lWaypointSouthNorth = 1; // Negative value means south, positive value means north
    int lWaypointWestEast = 10; // Negative value means west, positive value means east


    // Process all instructions
    for (const auto lInstruction : aInstructions)
    {
        // Should not exist, throw error
        if (lInstruction.size() < 2)
        {
            throw runtime_error("Invalid instruction");
        }

        unsigned int lValue = stoul(lInstruction.substr(1));

        if (lInstruction[0] == NORTH_LETTER)
        {
            lWaypointSouthNorth += lValue;
        }
        else if (lInstruction[0] == SOUTH_LETTER)
        {
            lWaypointSouthNorth -= lValue;
        }
        else if (lInstruction[0] == EAST_LETTER)
        {
            lWaypointWestEast += lValue;
        }
        else if (lInstruction[0] == WEST_LETTER)
        {
            lWaypointWestEast -= lValue;
        }
        else if (lInstruction[0] == LEFT_LETTER)
        {
            processWaypointLeft(lValue, lWaypointSouthNorth, lWaypointWestEast);
        }
        else if (lInstruction[0] == RIGHT_LETTER)
        {
            processWaypointRight(lValue, lWaypointSouthNorth, lWaypointWestEast);
        }
        else if (lInstruction[0] == FORWARD_LETTER)
        {
            lSouthNorth += lValue * lWaypointSouthNorth;
            lWestEast += lValue * lWaypointWestEast;
        }

    }

    return abs(lSouthNorth) + abs(lWestEast);
}