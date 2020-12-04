#pragma once

#include <string>
#include <sstream>

class PassportClass
{
    public:
        PassportClass(std::stringstream& pPassportLine);
        virtual ~PassportClass() = default;
        PassportClass(const PassportClass& pCopy) = default;
        PassportClass(PassportClass&& pMove) = default;

        bool isValidPart1() const noexcept;
        bool isValidPart2() const noexcept;

        bool isBirthYearValid() const noexcept;
        bool isIssueYearValid() const noexcept;
        bool isExpirationYearValid() const noexcept;
        bool isHeightValid() const noexcept;
        bool isHairColorValid() const noexcept;
        bool isEyeColorValid() const noexcept;
        bool isPassportIdValid() const noexcept;

        inline void setByr(const std::string& pByr) { aByr = pByr; }
        inline std::string getByr() const { return aByr; }

        inline void setIyr(const std::string& pIyr) { aIyr = pIyr; }
        inline std::string getIyr() const { return aIyr; }

        inline void setHgt(const std::string& pHgt) { aHgt = pHgt; }
        inline std::string getHgt() const { return aHgt; }

        inline void setHcl(const std::string& pHcl) { aHcl = pHcl; }
        inline std::string getHcl() const { return aHcl; }

        inline void setEcl(const std::string& pEcl) { aEcl = pEcl; }
        inline std::string getEcl() const { return aEcl; }

        inline void setPid(const std::string& pPid) { aPid = pPid; }
        inline std::string getPid() const { return aPid; }

    private:

        // byr (Birth Year)
        // iyr (Issue Year)
        // eyr (Expiration Year)
        // hgt (Height)
        // hcl (Hair Color)
        // ecl (Eye Color)
        // pid (Passport ID)
        // cid (Country ID)

        std::string aByr;
        std::string aIyr;
        std::string aEyr;
        std::string aHgt;
        std::string aHcl;
        std::string aEcl;
        std::string aPid;
        std::string aCid;

        bool aByrValid;
        bool aIyrValid;
        bool aEyrValid;
        bool aHgtValid;
        bool aHclValid;
        bool aEclValid;
        bool aPidValid;
        bool aCidValid;
};
