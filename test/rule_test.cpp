#include <gtest/gtest.h>
#include "rule.hpp"
#include "term.hpp"

// Test Rule construction - fact (empty body)
TEST(RuleTest, FactConstruction) {
    std::vector<Term> emptyBody;
    Rule fact("parent", emptyBody);
    EXPECT_EQ(fact.head, "parent");
    EXPECT_TRUE(fact.body.empty());
}

// Test Rule construction - rule with body
TEST(RuleTest, RuleWithBody) {
    std::vector<Term> body = {Term("parent", {Term("X", true), Term("Y", true)}, false),
                              Term("parent", {Term("Y", true), Term("Z", true)}, false)};
    Rule rule("grandparent", body);
    EXPECT_EQ(rule.head, "grandparent");
    EXPECT_EQ(rule.body.size(), 2);
    EXPECT_EQ(rule.body[0].name, "parent");
    EXPECT_EQ(rule.body[1].name, "parent");
}

// Test Rule with single body term
TEST(RuleTest, RuleWithSingleBody) {
    std::vector<Term> body = {Term("parent", {Term("john"), Term("mary")}, false)};
    Rule rule("child", body);
    EXPECT_EQ(rule.head, "child");
    EXPECT_EQ(rule.body.size(), 1);
}
