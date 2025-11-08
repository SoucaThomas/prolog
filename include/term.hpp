#pragma once
#include <string>
#include <vector>

class Term {
   public:
    std::string name;
    std::vector<Term> arguments;
    bool variable;

    Term(const std::string& name, bool variable = false);
    Term(const std::string& name, const std::vector<Term>& arguments, bool variable = false);

    void print() const;
};