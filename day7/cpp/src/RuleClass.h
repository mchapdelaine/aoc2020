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
    inline const std::map<std::string, unsigned int>& getContent() const { return aContent; }

private:
    std::string aBagName;
    std::map<std::string, unsigned int> aContent;

};