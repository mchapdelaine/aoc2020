#include "PassportClass.h"
#include <iostream>
#include <vector>
#include <fstream>

constexpr char BIRTH_YEAR[] = "byr";
constexpr char ISSUE_YEAR[] = "iyr";
constexpr char EXPIRATION_YEAR[] = "eyr";
constexpr char HEIGHT[] = "hgt";
constexpr char HAIR_COLOR[] = "hcl";
constexpr char EYE_COLOR[] = "ecl";
constexpr char PASSPORT_ID[] = "pid";
constexpr char COUNTRY_ID[] = "cid";

using namespace std;

PassportClass::PassportClass(stringstream& pPassportString)
{
    // Set all fields false before parsing
    aByrValid = false;
    aIyrValid = false;
    aEyrValid = false;
    aHgtValid = false;
    aHclValid = false;
    aEclValid = false;
    aPidValid = false;
    aCidValid = false;

    vector<string> lTokens;
    string lField;
    string lTypeValue;

    while (getline(pPassportString, lField, ' ')) 
    {
        //cout << "Got first token : " << lField << endl; 
        stringstream lFieldStream;
        lFieldStream << lField;

        int lCount = 0;
        string lType;
        string lValue;
        while (getline(lFieldStream, lTypeValue, ':'))
        {
            //cout << "  -- value : " << lTypeName << endl;

            if (lCount == 0)
            {
                lType = lTypeValue;
            }
            else
            {
                lValue = lTypeValue;
            }

            lCount++;
        }

        //cout << "Got type : " << lType << " and value " << lValue << endl;

        if (lType == BIRTH_YEAR)
        {
            //cout << " - Birth year valid !!!\n";
            aByrValid = true;
            aByr = lValue;
        }
        else if (lType == ISSUE_YEAR)
        {
            //cout << " - Issue year valid\n";
            aIyrValid = true;
            aIyr = lValue;
        }
        else if (lType == EXPIRATION_YEAR)
        {
            //cout << " - Expiration year valid\n";
            aEyrValid = true;
            aEyr = lValue;
        }
        else if (lType == HEIGHT)
        {
            //cout << " - Height valid\n";
            aHgtValid = true;
            aHgt = lValue;
        }
        else if (lType == HAIR_COLOR)
        {
            //cout << " - Hair color valid\n";
            aHclValid = true;
            aHcl = lValue;
        }
        else if (lType == EYE_COLOR)
        {
            //cout << " - Eye year valid\n";
            aEclValid = true;
            aEcl = lValue;
        }
        else if (lType == PASSPORT_ID)
        {
            //cout << " - Passport id valid\n";
            aPidValid = true;
            aPid = lValue;
        }
        else if (lType == COUNTRY_ID)
        {
            //cout << " - Country ID valid\n";
            aCidValid = true;
            aCid = lValue;
        }
    } 
}

bool PassportClass::isValidPart1() const noexcept
{
    // cout << "YYY=> aByrValid" << aByrValid << endl;
    // cout << "YYY=> aIyrValid" << aIyrValid << endl;
    // cout << "YYY=> aEyrValid" << aEyrValid << endl;
    // cout << "YYY=> aHgtValid" << aHgtValid << endl;
    // cout << "YYY=> aHclValid" << aHclValid << endl;
    // cout << "YYY=> aEclValid" << aEclValid << endl;
    // cout << "YYY=> aPidValid" << aPidValid << endl;
    // cout << "YYY=> aCidValid" << aCidValid << endl;

    return (aByrValid && aIyrValid && aEyrValid && aHgtValid && aHclValid && aEclValid && aPidValid); 
}

bool PassportClass::isBirthYearValid() const noexcept
{
    // byr (Birth Year) - four digits; at least 1920 and at most 2002.
    unsigned int lBirthYear = stoul(aByr);
    bool lBirthYearValid = false;
    if (lBirthYear >= 1920 && lBirthYear <= 2002)
    {
        lBirthYearValid = true;
    }

    return lBirthYearValid;
}

bool PassportClass::isIssueYearValid() const noexcept
{
    // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    unsigned int lIssueYear = stoul(aIyr);
    bool lIssueYearValid = false;
    if (lIssueYear >= 2010 && lIssueYear <= 2020)
    {
        lIssueYearValid = true;
    }

    return lIssueYearValid;
}

bool PassportClass::isExpirationYearValid() const noexcept
{
    // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    unsigned int lExpirationYear = stoul(aEyr);
    bool lExpirationYearValid = false;
    if (lExpirationYear >= 2020 && lExpirationYear <= 2030)
    {
        lExpirationYearValid = true;
    }

    return lExpirationYearValid;
}

bool PassportClass::isHeightValid() const noexcept
{
    // hgt (Height) - a number followed by either cm or in:
    // If cm, the number must be at least 150 and at most 193.
    // If in, the number must be at least 59 and at most 76.

    enum class TypeEnum
    {
        CENTIMETER,
        INCHES,
        INVALID,
    };

    bool lIsHeightValid = false;
    unsigned int lLength = aHgt.length();
    TypeEnum lType = TypeEnum::INVALID;

    if (lLength < 2)
    {
        return false;
    }

    if (aHgt[lLength - 2] == 'c' && aHgt[lLength - 1] == 'm')
    {
        lType == TypeEnum::CENTIMETER;
    }
    else if (aHgt[lLength - 2] == 'i' && aHgt[lLength - 1] == 'n')
    {
        lType == TypeEnum::INCHES;
    }

    unsigned int lValue = stoul(aHgt.substr(0, lLength - 2));

    switch (lType)
    {
    case TypeEnum::CENTIMETER:
        if (lValue >= 150 && lValue <= 193)
        {
            lIsHeightValid = true;
        }
        break;
    case TypeEnum::INCHES:
        if (lValue >= 59 && lValue <= 76)
        {
            lIsHeightValid = true;
        }
        break;
    
    default:
        break;
    }

    return lIsHeightValid;
}

bool PassportClass::isHairColorValid() const noexcept
{
    // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.

    if (aHcl.length() != 7)
    {
        return false;
    }

    if (aHcl[0] != '#')
    {
        return false;
    }

    for (unsigned int i = 1; i < 7; i++)
    {
        if (aHcl[i] != '0' &&
            aHcl[i] != '1' &&
            aHcl[i] != '2' &&
            aHcl[i] != '3' &&
            aHcl[i] != '4' &&
            aHcl[i] != '5' &&
            aHcl[i] != '6' &&
            aHcl[i] != '7' &&
            aHcl[i] != '8' &&
            aHcl[i] != '9' &&
            aHcl[i] != 'a' &&
            aHcl[i] != 'b' &&
            aHcl[i] != 'c' &&
            aHcl[i] != 'd' &&
            aHcl[i] != 'e' &&
            aHcl[i] != 'f')
        {
            return false;
        }
    }

    return true;
}

bool PassportClass::isEyeColorValid() const noexcept
{
    // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.

    if (aEcl == "amb" ||
        aEcl == "blu" ||
        aEcl == "brn" ||
        aEcl == "gry" ||
        aEcl == "hzl" ||
        aEcl == "oth")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PassportClass::isPassportIdValid() const noexcept
{
    // pid (Passport ID) - a nine-digit number, including leading zeroes.
    bool lPassportIdValid = false;

    if (aPid.length() == 9)
    {
        lPassportIdValid = true;
        for (unsigned int i = 0; i < aPid.length(); i++)
        {
            if (aPid[i] <= '0' && aPid[i] >= '9')
            {
                lPassportIdValid = false;
                break;
            }
        }
    }

    return lPassportIdValid;
}

bool PassportClass::isValidPart2() const noexcept
{
    // If no CID, it is still not valid in second part
    if (!isValidPart1())
    {
        return isBirthYearValid() &&
            isIssueYearValid() &&
            isExpirationYearValid() &&
            isHeightValid() &&
            isHairColorValid() && 
            isEyeColorValid() && 
            isPassportIdValid();
    }

    return false;

}