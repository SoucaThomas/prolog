#include "knowledgeBase.hpp"
#include "rule.hpp"
#include <iostream>
#include <vector>

void knowledgeBase::addRule(const Rule& rule) { rules.push_back(rule); }

void knowledgeBase::print() const {
    std::cout << "Knowledge Base:" << '\n';
    for (const auto& rule : rules) {
        rule.print();
        std::cout << '\n';
    }
}