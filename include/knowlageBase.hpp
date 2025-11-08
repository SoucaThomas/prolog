#pragma once
#include "rule.hpp"
#include <vector>

class KnowledgeBase {
   public:
    std::vector<Rule> rules;

    KnowledgeBase();
    void addRule(const Rule& rule);
    void print() const;
};