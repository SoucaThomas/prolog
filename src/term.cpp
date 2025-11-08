#include "term.hpp"
#include <iostream>

Term::Term(std::string name, bool variable) : name(std::move(name)), variable(variable) {}

Term::Term(std::string name, std::vector<Term> arguments, bool variable)
    : name(std::move(name)), arguments(std::move(arguments)), variable(variable) {}

void Term::print() const {
    std::cout << name;
    if (!arguments.empty()) {
        std::cout << "(";
        for (size_t i = 0; i < arguments.size(); ++i) {
            arguments[i].print();
            if (i + 1 < arguments.size()) {
                std::cout << ", ";
            }
        }
        std::cout << ")";
    }
}
