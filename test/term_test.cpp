#include <gtest/gtest.h>
#include "term.hpp"

// Test Term construction - atom
TEST(TermTest, AtomConstruction) {
    Term atom("john");
    EXPECT_EQ(atom.name, "john");
    EXPECT_TRUE(atom.arguments.empty());
    EXPECT_FALSE(atom.variable);
}

// Test Term construction - variable
TEST(TermTest, VariableConstruction) {
    Term var("X", true);
    EXPECT_EQ(var.name, "X");
    EXPECT_TRUE(var.arguments.empty());
    EXPECT_TRUE(var.variable);
}

// Test Term construction - compound term
TEST(TermTest, CompoundTermConstruction) {
    std::vector<Term> args = {Term("john"), Term("mary")};
    Term compound("parent", args);
    EXPECT_EQ(compound.name, "parent");
    EXPECT_EQ(compound.arguments.size(), 2);
    EXPECT_EQ(compound.arguments[0].name, "john");
    EXPECT_EQ(compound.arguments[1].name, "mary");
    EXPECT_FALSE(compound.variable);
}

// Test Term construction - compound term with variables
TEST(TermTest, CompoundTermWithVariables) {
    std::vector<Term> args = {Term("X", true), Term("Y", true)};
    Term compound("parent", args);
    EXPECT_EQ(compound.name, "parent");
    EXPECT_EQ(compound.arguments.size(), 2);
    EXPECT_TRUE(compound.arguments[0].variable);
    EXPECT_TRUE(compound.arguments[1].variable);
}

// Test nested compound terms
TEST(TermTest, NestedCompoundTerms) {
    std::vector<Term> innerArgs = {Term("john"), Term("mary")};
    Term inner("parent", innerArgs);
    std::vector<Term> outerArgs = {inner, Term("ann")};
    Term outer("grandparent", outerArgs);

    EXPECT_EQ(outer.name, "grandparent");
    EXPECT_EQ(outer.arguments.size(), 2);
    EXPECT_EQ(outer.arguments[0].name, "parent");
    EXPECT_EQ(outer.arguments[0].arguments.size(), 2);
}
