#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

constexpr unsigned int MAX_CHAR = 0xFF;

unsigned int numberUniqueCharacters(const std::string& pString)
{
    unsigned int lCharacters[MAX_CHAR] = {0};

    for (unsigned int i = 0; i < pString.length(); i++)
    {
        if (pString[i] == ' ')
        {
            continue;
        }
        lCharacters[pString[i]] = 1;
    }

    unsigned int lCount = 0;
    for (unsigned int i = 0; i < MAX_CHAR; i++)
    {
        lCount += lCharacters[i];
    }

    return lCount;
}

unsigned int numberOfAllAnswers(const std::string& pString)
{
    istringstream lStream(pString);
    vector<string> lAnswers {istream_iterator<string>{lStream}, istream_iterator<string>{}};

    unsigned int lCharacters[MAX_CHAR] = {0};

    if (lAnswers.size() == 0)
    {
        return 0;
    }

    for (char lCurrentCharacter = 'a'; lCurrentCharacter <= 'z'; lCurrentCharacter++)
    {
        bool lFoundInOne = false;
        bool lMissingInOne = false;
        for (const auto lAnswer : lAnswers)
        {
            bool lFoundLocal = false;
            for (unsigned int i = 0; i < lAnswer.length(); i++)
            {
                if (lAnswer[i] == lCurrentCharacter)
                {
                    lFoundLocal = true;
                    lFoundInOne = true;
                }
            }

            if (lFoundLocal == false)
            {
                lMissingInOne = true;
            }
        }

        if (lFoundInOne == true && lMissingInOne == false)
        {
            lCharacters[lCurrentCharacter] = 1;
        }
    }

    unsigned int lCount = 0;
    for (unsigned int i = 0; i < MAX_CHAR; i++)
    {
        lCount += lCharacters[i];
    }

    return lCount;
}


int main(int pArgc, char** pArgv) 
{
    cout << "Day 6\n";
    
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
    string lAnswer;
    vector<string> lTests;
    
    while (getline(lInputFile, lTemp))
    {
        if (lTemp.length() != 0)
        {
            lAnswer += lTemp;
            lAnswer += " ";
        }
        else
        {    
            lTests.emplace_back(lAnswer);
            lAnswer = "";
        }
    }

    // Add the last passport if the file does not end with an empty line
    if (lAnswer.length() != 0)
    {
        lTests.emplace_back(lAnswer);
    }

    // Part 1 : Sum them all
    unsigned int lUniqueAnswerSum = 0;
    for (auto lAnswer : lTests)
    {
        lUniqueAnswerSum += numberUniqueCharacters(lAnswer);
    }

    cout << "Part 1 : There is " << lUniqueAnswerSum << " unique answers" << endl;


    // Part 2 : 
    unsigned int lPart2Sum = 0;
    for (auto lAnswer : lTests)
    {
        lPart2Sum += numberOfAllAnswers(lAnswer);
    }

    cout << "Part 2 : There is " << lPart2Sum << " unique answers" << endl;
    
    return EXIT_SUCCESS;
}
