// NOLINTBEGIN(readability-identifier-length)
#include <gtest/gtest.h>
#include "knowledgeBase.hpp"
#include "rule.hpp"
#include "term.hpp"

// Test KnowledgeBase construction
TEST(KnowledgeBaseTest, Construction) {
    knowledgeBase kb;
    EXPECT_TRUE(kb.rules.empty());
}

// Test adding a fact to KnowledgeBase
TEST(KnowledgeBaseTest, AddFact) {
    knowledgeBase kb;
    std::vector<Term> emptyBody;
    Rule fact("parent", emptyBody);
    kb.addRule(fact);
    EXPECT_EQ(kb.rules.size(), 1);
    EXPECT_EQ(kb.rules[0].head, "parent");
}

// Test adding multiple rules
TEST(KnowledgeBaseTest, AddMultipleRules) {
    knowledgeBase kb;

    std::vector<Term> body1 = {Term("parent", {Term("X", true), Term("Y", true)}, false)};
    Rule rule1("grandparent", body1);
    kb.addRule(rule1);

    std::vector<Term> emptyBody;
    Rule fact("parent", emptyBody);
    kb.addRule(fact);

    EXPECT_EQ(kb.rules.size(), 2);
    EXPECT_EQ(kb.rules[0].head, "grandparent");
    EXPECT_EQ(kb.rules[1].head, "parent");
}

// Test adding rule with body
TEST(KnowledgeBaseTest, AddRuleWithBody) {
    knowledgeBase kb;
    std::vector<Term> body = {Term("parent", {Term("X", true), Term("Y", true)}, false),
                              Term("parent", {Term("Y", true), Term("Z", true)}, false)};
    Rule rule("grandparent", body);
    kb.addRule(rule);

    EXPECT_EQ(kb.rules.size(), 1);
    EXPECT_EQ(kb.rules[0].body.size(), 2);
}
// NOLINTEND(readability-identifier-length)