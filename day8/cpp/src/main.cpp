#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "InstructionClass.h"

using namespace std;

bool executeOnce(const vector<InstructionClass>& pInstructions, int& pAcc)
{
    unsigned int lProgramCounter = 0;
    pAcc = 0;
    unsigned short lExecutionCount[pInstructions.size()] = { 0 };

    while (lProgramCounter < pInstructions.size())
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
            pAcc += pInstructions[lProgramCounter].getValue();
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

    return lProgramCounter == pInstructions.size();
}

bool modifyProgram(const vector<InstructionClass>& pInstructions, int& pAcc)
{
    // Try to loop and change each JMP and NOP to see what happen

    for (unsigned int lCurrentTry = 0; lCurrentTry < pInstructions.size(); lCurrentTry++)
    {
        if (pInstructions[lCurrentTry].getInstuction() == InstructionClass::InstructionEnum::ACC)
        {
            continue;
        }
        else if (pInstructions[lCurrentTry].getInstuction() == InstructionClass::InstructionEnum::JMP)
        {
            vector<InstructionClass> lNewInstructions = pInstructions;
            lNewInstructions[lCurrentTry].setInstruction(InstructionClass::InstructionEnum::NOP);
            if (executeOnce(lNewInstructions, pAcc))
            {
                cout << "Gotcha (JMP to NOP) at line " << lCurrentTry << endl;
                return true;
            }
        }
        else if (pInstructions[lCurrentTry].getInstuction() == InstructionClass::InstructionEnum::NOP)
        {
            vector<InstructionClass> lNewInstructions = pInstructions;
            lNewInstructions[lCurrentTry].setInstruction(InstructionClass::InstructionEnum::JMP);
            if (executeOnce(lNewInstructions, pAcc))
            {
                cout << "Gotcha (NOP to JMP) at line " << lCurrentTry << endl;
                return true;
            }
        }
    }

    return false;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 8\n";
    
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

    
    int lAcc = 0;
    executeOnce(lInstructions, lAcc);
    cout << "For part 1, the accumulator is " << lAcc << endl;

    cout << "Find line to change " << endl;
    if (modifyProgram(lInstructions, lAcc))
    {
        cout << "Complete " << endl;
    }
    else
    {
        cout << "No solution" << endl;
    }
    
    cout << "Accumulator is " << lAcc << endl;

    return EXIT_SUCCESS;
}
