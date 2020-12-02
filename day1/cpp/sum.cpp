#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

constexpr unsigned int SUM_FOR_ANSWER = 2020;

bool twoSum(unsigned int lSum, const vector<unsigned int>& lValues)
{
    for (const auto l1 : lValues)
    {
        for (const auto l2 : lValues)
        {
            if (l1 + l2 == SUM_FOR_ANSWER)
            {
                cout << "l1 = " << l1 << " l2 = " << l2 << " = " << l1 * l2 << endl;
                return true;
            }
        }
    }
    
    return false;
}

bool threeSum(unsigned int lSum, const vector<unsigned int>& lValues)
{
    for (const auto l1 : lValues)
    {
        for (const auto l2 : lValues)
        {
            for (const auto l3 : lValues)
            {
                if (l1 + l2 + l3 == SUM_FOR_ANSWER)
                {
                    cout << "l1 = " << l1 << " l2 = " << l2 << " l3 = " << l3 << " " <<  l1 * l2 * l3 << endl;
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main(int pArgc, char** pArgv)
{
    if (pArgc < 2)
    {
        cout << "File not provided, exit\n";
        return EXIT_FAILURE;
    }

    vector<unsigned int> lValues;
    ifstream lInputFile(pArgv[1], std::ifstream::in);

    if (!lInputFile.is_open())
    {
        cout << "Could not open " << pArgv[1] << ", exit\n";
        return EXIT_FAILURE;
    }

    unsigned int lTemp;
    while (!lInputFile.eof())
    {
        lInputFile >> lTemp;
        lValues.emplace_back(lTemp);
    }

    if (!twoSum(SUM_FOR_ANSWER, lValues))
    {
        cout << "No values works for 2 in sum\n";
    }

    if (!threeSum(SUM_FOR_ANSWER, lValues))
    {
        cout << "No values works for 3 in sum\n";
    }

    cout << "No value found\n";

    return EXIT_SUCCESS;
}