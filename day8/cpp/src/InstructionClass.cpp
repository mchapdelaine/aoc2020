
#include "InstructionClass.h"

#include <sstream>
#include <stdexcept>
#include <iostream>
using namespace std;

InstructionClass::InstructionClass(const std::string& pInstructionString)
{
    istringstream lInstructionStream(pInstructionString);

    string lWord;
    lInstructionStream >> lWord;

    if (lWord == "nop")
    {
        aInstruction = InstructionEnum::NOP;
    }
    else if (lWord == "acc")
    {
        aInstruction = InstructionEnum::ACC;
    }
    else if (lWord == "jmp")
    {
        aInstruction = InstructionEnum::JMP;
    }
    else
    {
        stringstream lMessage;
        lMessage << "Wrong instruction type " << lWord;

        throw runtime_error(lMessage.str().c_str());
    }

    lInstructionStream >> lWord;
    aValue = stoi(lWord);
}