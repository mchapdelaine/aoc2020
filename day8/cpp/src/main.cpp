#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "InstructionClass.h"

using namespace std;

int executeOnce(const vector<InstructionClass>& pInstructions)
{
    unsigned int lProgramCounter = 0;
    int lAcc = 0;

    unsigned short lExecutionCount[pInstructions.size()] = { 0 };

    while (true)
    {
        if (lExecutionCount[lProgramCounter] == 1)
        {
            break;
        }

        lExecutionCount[lProgramCounter] += 1;

        if (pInstructions[lProgramCounter].getInstuction() == InstructionClass::InstructionEnum::NOP)
        {
            lProgramCounter++;
        }
        else if (pInstructions[lProgramCounter].getInstuction() == InstructionClass::InstructionEnum::ACC)
        {
            lAcc += pInstructions[lProgramCounter].getValue();
            lProgramCounter++;
        }
        else if (pInstructions[lProgramCounter].getInstuction() == InstructionClass::InstructionEnum::JMP)
        {
            lProgramCounter += pInstructions[lProgramCounter].getValue();
        }
        else
        {
            cout << "SHOULD NEVER HAPPEN\n";
        }
    }

    return lAcc;
}


int main(int pArgc, char** pArgv) 
{
    cout << "Day 3\n";
    
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
    vector<InstructionClass> lInstructions;
    
    while (getline(lInputFile, lTemp))
    {
        lInstructions.emplace_back(InstructionClass(lTemp));
    }

    cout << "For part 1, the accumulator is " << executeOnce(lInstructions) << endl;

    return EXIT_SUCCESS;
}
