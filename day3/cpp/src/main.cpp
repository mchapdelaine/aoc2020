#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

constexpr char TREE_SYMBOL = '#';

using namespace std;

bool verifyTree(const vector<string>& pTerrain, unsigned int pX, unsigned int pY)
{
    if (pTerrain[pX][pY] == TREE_SYMBOL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int findTrees(const vector<string>& pTerrain, unsigned int pDown, unsigned int pRight)
{
    unsigned int lTrees = 0;
    unsigned int lHeight = pTerrain.size();

    unsigned int lTests = 0;
    
    if (lHeight != 0)
    {
        unsigned int lWidth = pTerrain[0].length(); // All lines has the same width

        // Start at the top left corner
        unsigned int lX = 0;
        unsigned int lY = 0;

        do
        {
            lY += pRight;
            lX += pDown;

            lTests++;
            if (verifyTree(pTerrain, lX, lY % lWidth))
            {
                lTrees++;
            }
        }
        while (lX < lHeight - 1);
    }
    else
    {
        cout << "Empty terrain\n";
    }
    
    return lTrees;
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
    vector<string> lTests;
    
    while (getline(lInputFile, lTemp))
    {
        lTests.emplace_back(lTemp);
    }
    
    cout << "Right 1 down 1 : " <<  findTrees(lTests, 1, 1) << " trees\n";
    cout << "Right 3 down 1 : " <<  findTrees(lTests, 1, 3) << " trees\n";
    cout << "Right 5 down 1 : " <<  findTrees(lTests, 1, 5) << " trees\n";
    cout << "Right 7 down 1 : " <<  findTrees(lTests, 1, 7) << " trees\n";
    cout << "Right 1 down 2 : " <<  findTrees(lTests, 2, 1) << " trees\n";

    // Use int64_t, may go over max(unsigned int 32!)
    uint64_t lMultiply = findTrees(lTests, 1, 1);
    lMultiply *= findTrees(lTests, 1, 3);
    lMultiply *= findTrees(lTests, 1, 5);
    lMultiply *= findTrees(lTests, 1, 7);
    lMultiply *= findTrees(lTests, 2, 1);

    cout << "Multiply is equal " << lMultiply << endl;

    return EXIT_SUCCESS;
}
