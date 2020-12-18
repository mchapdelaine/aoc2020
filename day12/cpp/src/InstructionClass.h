#pragma once

#include <string>
#include <vector>

class InstructionClass
{
    enum class DirectionEnum
    {
        NORTH,
        SOUTH,
        EAST,
        WEST,
    };

public:
    InstructionClass() = default;
    InstructionClass(const std::vector<std::string>& pInstructions);
    virtual ~InstructionClass() = default;

    unsigned int part1ManhattanSum() const;

    static DirectionEnum getDirectionRight(DirectionEnum pStart, unsigned int pDegrees);
    static DirectionEnum getDirectionLeft(DirectionEnum pStart, unsigned int pDegrees);

private:
    std::vector<std::string> aInstructions;
};