#pragma once

#include <string>
#include <map>

class RuleClass
{
public:    
    RuleClass(const std::string& pRuleString);
    virtual ~RuleClass() = default;

    inline std::string getBagName() const { return aBagName; } 

    unsigned int hasBag(const std::string& pBagName) const;

private:
    std::string aBagName;
    std::map<std::string, unsigned int> aContent;

};