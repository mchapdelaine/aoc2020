#pragma once

#include <string>

class PasswordClass 
{
public:
    PasswordClass() = delete;
    PasswordClass(const std::string& pPasswordLine);
    PasswordClass(const PasswordClass& pOrig) = default;
    PasswordClass(PasswordClass&& pMove) = default;
    virtual ~PasswordClass() = default;

    std::string getCharacters() const {
        return aCharacters;
    }

    void getMax(int aMax) {
        this->aMax = aMax;
    }

    int getMax() const {
        return aMax;
    }

    void setMin(int aMin) {
        this->aMin = aMin;
    }

    int getMin() const {
        return aMin;
    };
    
    bool isValid() const;
    
    bool isValid2() const;
    
private:
    int aMin;
    int aMax;
    char aLetter;
    std::string aCharacters;
};


