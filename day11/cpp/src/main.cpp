#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "FerryClass.h"

using namespace std;

int main(int pArgc, char** pArgv) 
{
    cout << "Day 11\n";

    string lFile;
    
    if (pArgc < 2)
    {
        cout << "Missing input file name\n";
        return EXIT_FAILURE;
    }
    else
    {
        lFile = pArgv[1];
    }
    
    
    ifstream lInputFile(lFile.c_str(), std::ifstream::in);

    if (!lInputFile.is_open())
    {
        cout << "Could not open " << pArgv[1] << ", exit\n";
        return EXIT_FAILURE;
    }
    
    string lTemp;
    string lFerryString;
    unsigned int lSeatsPerRow = 0;
    unsigned int lRows = 0;
    
    while (getline(lInputFile, lTemp))
    {
        if (lSeatsPerRow == 0)
        {
            lSeatsPerRow = lTemp.size();
        }

        lFerryString += lTemp;
        lRows++;
    }

    FerryClass lFerry(lFerryString, lRows, lSeatsPerRow);

    //lFerry.displayFerry();

    unsigned int lPart1 = lFerry.part1(1000000);
    cout << "For part 1, there is " << lPart1 << " empty seats at the end\n";
    

    return EXIT_SUCCESS;
}
