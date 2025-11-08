#include "term.hpp"
#include <iostream>

Term::Term(const std::string& name, bool variable) : name(name), variable(variable) {}

Term::Term(const std::string& name, const std::vector<Term>& arguments, bool variable)
    : name(name), arguments(arguments), variable(variable) {}

void Term::print() const {
    std::cout << name;
    if (!arguments.empty()) {
        std::cout << "(";
        for (size_t i = 0; i < arguments.size(); ++i) {
            arguments[i].print();
            if (i + 1 < arguments.size()) std::cout << ", ";
        }
        std::cout << ")";
    }
}
