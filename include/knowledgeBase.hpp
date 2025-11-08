#pragma once
#include "rule.hpp"
#include <vector>

class knowledgeBase {
   public:
    std::vector<Rule> rules;

    knowledgeBase() = default;
    void addRule(const Rule& rule);
    void print() const;
};