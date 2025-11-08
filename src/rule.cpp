#include "rule.hpp"
#include "term.hpp"

#include <iostream>
#include <string>
#include <vector>

Rule::Rule(const std::string& head, const std::vector<Term>& body) : head(head), body(body) {}

void Rule::print() const {
    std::cout << head << " :- ";
    for (size_t i = 0; i < body.size(); ++i) {
        body[i].print();
        if (i + 1 < body.size()) std::cout << ", ";
    }
    std::cout << ".";
}