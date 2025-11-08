#include "knowledgeBase.hpp"
#include "rule.hpp"
#include <iostream>
#include <vector>

knowledgeBase::knowledgeBase() : rules() {}

void knowledgeBase::addRule(const Rule& rule) { rules.push_back(rule); }

void knowledgeBase::print() const {
    std::cout << "Knowledge Base:" << std::endl;
    for (const auto& rule : rules) {
        rule.print();
        std::cout << std::endl;
    }
}