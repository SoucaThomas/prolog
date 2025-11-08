#pragma once
#include "term.hpp"
#include <string>
#include <vector>

class Rule {
   public:
    std::string head;
    std::vector<Term> body;

    Rule(const std::string& head, const std::vector<Term>& body);

    void print() const;
};