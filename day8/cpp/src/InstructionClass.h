#pragma once

#include <string>

class InstructionClass
{
public:
    enum class InstructionEnum
    {
        NOP,
        ACC,
        JMP,
    };

    InstructionClass(const std::string& pInstructionString);
    virtual ~InstructionClass() = default;
    InstructionClass(const InstructionClass& pCopy) = default;
    InstructionClass(InstructionClass&& pMove) = default;

    inline InstructionEnum getInstuction() const noexcept { return aInstruction; }
    inline int getValue() const noexcept { return aValue; }

private:
    int aValue;
    InstructionEnum aInstruction;
};