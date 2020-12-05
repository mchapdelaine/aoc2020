#pragma once

#include <string>

class BoardingPassClass
{
    public:

    BoardingPassClass(const std::string& pBoardingPassString);
    virtual ~BoardingPassClass() = default;
    BoardingPassClass(const BoardingPassClass& pCopy) = default;
    BoardingPassClass(BoardingPassClass&& pMove) = default;

    unsigned int getId() const noexcept;

    unsigned int getRow() const noexcept { return aRow; }
    unsigned int getColumn() const noexcept { return aColumn; }

    private:

    std::string aCharacters;
    unsigned int aRow;
    unsigned int aColumn;
};