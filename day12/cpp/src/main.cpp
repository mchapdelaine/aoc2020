#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "InstructionClass.h"

using namespace std;


int main(int pArgc, char** pArgv) 
{
    cout << "Day 12\n";
    
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
    vector<string> lCommands;
    
    while (getline(lInputFile, lTemp))
    {
        lCommands.emplace_back(lTemp);
    }

    InstructionClass lDay(lCommands);

    unsigned int lPart1Sum = lDay.part1ManhattanSum();
    cout << "For part 1, the sum is " << lPart1Sum << endl;

    unsigned int lPart2Sum = lDay.part2ManhattanSum();
    cout << "For part 2, the sum is " << lPart2Sum << endl;

    return EXIT_SUCCESS;
}
