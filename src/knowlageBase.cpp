#include "knowlageBase.hpp"
#include "rule.hpp"
#include <iostream>
#include <vector>

KnowledgeBase::KnowledgeBase() : rules() {}

void KnowledgeBase::addRule(const Rule& rule) { rules.push_back(rule); }

void KnowledgeBase::print() const {
    std::cout << "Knowledge Base:" << std::endl;
    for (const auto& rule : rules) {
        rule.print();
        std::cout << std::endl;
    }
}