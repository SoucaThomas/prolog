#pragma once
#include <string>
#include <vector>

class Substitution;

class Term {
   public:
    std::string name;
    std::vector<Term> arguments;
    bool variable;

    Term(std::string name, bool variable = false);
    Term(std::string name, std::vector<Term> arguments, bool variable = false);

    void print() const;
};