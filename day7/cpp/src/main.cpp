#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

#include "RuleClass.h"

using namespace std;

unsigned int lNumberOfCombinationPart1(const vector<RuleClass>& lRules, const std::string& pBagToSearch)
{
    set<string> lAllBags;
    set<string> lCurrentBagsPass;
    set<string> lPreviousBagsPass;

    unsigned int lPass = 1;

    do
    {
        // For first pass, do not flush results and recopy vectors
        if (lPass != 1)
        {
            lPreviousBagsPass.swap(lCurrentBagsPass);
            lCurrentBagsPass.clear();
        }

        if (lPass == 1)
        {
            for (const auto lRule : lRules)
            {
                if (lRule.hasBag(pBagToSearch))
                {
                    // Add bag to both all bags and this current pass result
                    lAllBags.insert(lRule.getBagName());
                    lCurrentBagsPass.insert(lRule.getBagName());
                }
            }
        }
        else
        {
            for (const auto lPreviousPassBag : lPreviousBagsPass)
            {
                for (const auto lRule : lRules)
                {
                    if (lRule.hasBag(lPreviousPassBag))
                    {
                        // Add bag to both all bags and this current pass result
                        lAllBags.insert(lRule.getBagName());
                        lCurrentBagsPass.insert(lRule.getBagName());
                    }
                }
            }
        }

        {
            for (const auto lBag : lCurrentBagsPass)
            {

                lPreviousBagsPass.insert(lBag);
            }
        }

        lPass++;
    } 
    while (lCurrentBagsPass.size() != 0);
    
    return lAllBags.size();
}

uint64_t subBags(const vector<RuleClass>& lRules, const std::string& pBagToSearch, unsigned int lLevel)
{
    uint64_t lNumberBags = 0;

    for (const auto lRule : lRules)
    {
        if (lRule.getBagName() == pBagToSearch)
        {
            for (const auto lContent : lRule.getContent())
            {
                lNumberBags += lContent.second;
                lNumberBags += lContent.second * subBags(lRules, lContent.first, lLevel + 1);
            }

            break;
        }
    }

    return lNumberBags;
}

int main(int pArgc, char** pArgv) 
{
    cout << "Day 7\n";
    
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

    vector<RuleClass> lRules;
    
    while (getline(lInputFile, lTemp))
    {
        lRules.emplace_back(RuleClass(lTemp));
    }

    cout << "For Part 1, there is " << lNumberOfCombinationPart1(lRules, "shiny gold") << " combinaisons\n";
    cout << "For Part 2, there is " << subBags(lRules, "shiny gold", 1) << " bags\n";


    return EXIT_SUCCESS;
}
