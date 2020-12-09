#include "RuleClass.h"
#include <iostream>
#include <sstream>

using namespace std;

RuleClass::RuleClass(const string& pRuleString)
{
    // Parse string;
    istringstream lRuleStream(pRuleString);

    string lCurrentWord;

    bool lBagNameFound = false;
    bool lNewContent = false;

    unsigned int lContentCount = 0;
    string lContentName;

    while (lRuleStream >> lCurrentWord)
    {
        if (!lBagNameFound)
        {
            if (lCurrentWord == "bags" || lCurrentWord == "bag")
            {
                continue;
            }

            if (lCurrentWord != "contain")
            {
                if (aBagName.length() == 0)
                {
                    aBagName += lCurrentWord;
                }
                else
                {
                    aBagName += " ";
                    aBagName += lCurrentWord;
                }
            }
            else
            {
                lBagNameFound = true;
            }
        }
        else
        {
            if (lNewContent == false)
            {
                // If there is no content, abort
                if (lCurrentWord == "no")
                {
                    break;
                }
                else
                {
                    lContentCount = stoul(lCurrentWord);
                    lNewContent = true;
                }
            }
            else
            {
                if (lCurrentWord == "bags," || lCurrentWord == "bag,")
                {
                    // New content complete, add to database
                    aContent.insert(pair<string, unsigned int>(lContentName, lContentCount));

                    // Reset values
                    lContentName = "";
                    lContentCount = 0;
                    lNewContent = false;
                }
                else if (lCurrentWord == "bags." || lCurrentWord == "bag.")
                {
                    // New content complete, add to database
                    aContent.insert(pair<string, unsigned int>(lContentName, lContentCount));

                    // End of parsing will quit anyway
                }
                else
                {
                    if (lContentName.length() == 0)
                    {
                        lContentName += lCurrentWord;
                    }
                    else
                    {
                        lContentName += " ";
                        lContentName += lCurrentWord;
                    }
                }
            }
        }
    }

}

unsigned int RuleClass::hasBag(const std::string& pBagName) const
{
    unsigned int lNumber = 0;
    try
    {
        lNumber = aContent.at(pBagName);
    }
    catch(...)
    {
        // May be normal, not found
        ;
    }
    
    return lNumber;
}