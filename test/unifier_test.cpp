// NOLINTBEGIN(readability-identifier-length)
#include <gtest/gtest.h>
#include "unifier.hpp"
#include "term.hpp"

// Test Substitution - bind and lookup
TEST(UnifierTest, SubstitutionBindAndLookup) {
    Substitution sub;
    Term john("john");
    sub.bind("X", john);

    EXPECT_TRUE(sub.contains("X"));
    Term result = sub.lookup("X");
    EXPECT_EQ(result.name, "john");
    EXPECT_FALSE(result.variable);
}

// Test Substitution - contains check
TEST(UnifierTest, SubstitutionContains) {
    Substitution sub;
    EXPECT_FALSE(sub.contains("X"));

    Term value("john");
    sub.bind("X", value);
    EXPECT_TRUE(sub.contains("X"));
    EXPECT_FALSE(sub.contains("Y"));
}

// Test applySubstitution - variable bound
TEST(UnifierTest, ApplySubstitutionBoundVariable) {
    Substitution sub;
    Term john("john");
    sub.bind("X", john);

    Term var("X", true);
    Term result = applySubstitution(var, sub);
    EXPECT_EQ(result.name, "john");
    EXPECT_FALSE(result.variable);
}

// Test applySubstitution - variable not bound
TEST(UnifierTest, ApplySubstitutionUnboundVariable) {
    Substitution sub;
    Term var("X", true);
    Term result = applySubstitution(var, sub);
    EXPECT_EQ(result.name, "X");
    EXPECT_TRUE(result.variable);
}

// Test applySubstitution - atom unchanged
TEST(UnifierTest, ApplySubstitutionAtom) {
    Substitution sub;
    Term atom("john");
    Term result = applySubstitution(atom, sub);
    EXPECT_EQ(result.name, "john");
    EXPECT_FALSE(result.variable);
}

// Test applySubstitution - compound term
TEST(UnifierTest, ApplySubstitutionCompoundTerm) {
    Substitution sub;
    Term john("john");
    sub.bind("X", john);

    Term compound("parent", {Term("X", true), Term("Y", true)}, false);
    Term result = applySubstitution(compound, sub);

    EXPECT_EQ(result.name, "parent");
    EXPECT_EQ(result.arguments[0].name, "john");
    EXPECT_TRUE(result.arguments[1].variable);  // Y not bound
}

// Test occursCheck - variable occurs in term
TEST(UnifierTest, OccursCheckVariableOccurs) {
    Substitution sub;
    Term compound("parent", {Term("X", true), Term("Y", true)}, false);
    EXPECT_TRUE(occursCheck("X", compound, sub));
}

// Test occursCheck - variable does not occur
TEST(UnifierTest, OccursCheckVariableNotOccurs) {
    Substitution sub;
    Term atom("john");
    EXPECT_FALSE(occursCheck("X", atom, sub));
}

// Test occursCheck - nested compound
TEST(UnifierTest, OccursCheckNested) {
    Substitution sub;
    std::vector<Term> innerArgs = {Term("X", true), Term("Y", true)};
    Term inner("parent", innerArgs, false);
    std::vector<Term> outerArgs = {inner, Term("Z", true)};
    Term outer("grandparent", outerArgs, false);

    EXPECT_TRUE(occursCheck("X", outer, sub));
    EXPECT_TRUE(occursCheck("Y", outer, sub));
    EXPECT_FALSE(occursCheck("W", outer, sub));
}

// Test unify - variable to atom
TEST(UnifierTest, UnifyVariableToAtom) {
    Substitution sub;
    Term X("X", true);
    Term john("john");

    bool result = unify(X, john, sub);
    EXPECT_TRUE(result);
    EXPECT_TRUE(sub.contains("X"));
    EXPECT_EQ(sub.lookup("X").name, "john");
}

// Test unify - variable to variable
TEST(UnifierTest, UnifyVariableToVariable) {
    Substitution sub;
    Term X("X", true);
    Term Y("Y", true);

    bool result = unify(X, Y, sub);
    EXPECT_TRUE(result);
    EXPECT_TRUE(sub.contains("X"));
}

// Test unify - same variable
TEST(UnifierTest, UnifySameVariable) {
    Substitution sub;
    Term X1("X", true);
    Term X2("X", true);

    bool result = unify(X1, X2, sub);
    EXPECT_TRUE(result);
}

// Test unify - atom to atom (success)
TEST(UnifierTest, UnifyAtomToAtomSuccess) {
    Substitution sub;
    Term t1("john");
    Term t2("john");

    bool result = unify(t1, t2, sub);
    EXPECT_TRUE(result);
}

// Test unify - atom to atom (failure)
TEST(UnifierTest, UnifyAtomToAtomFailure) {
    Substitution sub;
    Term t1("john");
    Term t2("mary");

    bool result = unify(t1, t2, sub);
    EXPECT_FALSE(result);
}

// Test unify - compound terms (success)
TEST(UnifierTest, UnifyCompoundTermsSuccess) {
    Substitution sub;
    Term query("parent", {Term("X", true), Term("Y", true)}, false);
    Term fact("parent", {Term("john"), Term("mary")}, false);

    bool result = unify(query, fact, sub);
    EXPECT_TRUE(result);
    EXPECT_TRUE(sub.contains("X"));
    EXPECT_TRUE(sub.contains("Y"));
    EXPECT_EQ(sub.lookup("X").name, "john");
    EXPECT_EQ(sub.lookup("Y").name, "mary");
}

// Test unify - compound terms (failure - different names)
TEST(UnifierTest, UnifyCompoundTermsDifferentNames) {
    Substitution sub;
    Term t1("parent", {Term("john"), Term("mary")}, false);
    Term t2("child", {Term("john"), Term("mary")}, false);

    bool result = unify(t1, t2, sub);
    EXPECT_FALSE(result);
}

// Test unify - compound terms (failure - different arity)
TEST(UnifierTest, UnifyCompoundTermsDifferentArity) {
    Substitution sub;
    Term t1("parent", {Term("john")}, false);
    Term t2("parent", {Term("john"), Term("mary")}, false);

    bool result = unify(t1, t2, sub);
    EXPECT_FALSE(result);
}

// Test unify - nested compound terms
TEST(UnifierTest, UnifyNestedCompoundTerms) {
    Substitution sub;
    std::vector<Term> args1 = {Term("parent", {Term("X", true), Term("Y", true)}, false), Term("Z", true)};
    Term t1("grandparent", args1, false);

    std::vector<Term> args2 = {Term("parent", {Term("john"), Term("mary")}, false), Term("ann")};
    Term t2("grandparent", args2, false);

    bool result = unify(t1, t2, sub);
    EXPECT_TRUE(result);
    EXPECT_TRUE(sub.contains("X"));
    EXPECT_TRUE(sub.contains("Y"));
    EXPECT_TRUE(sub.contains("Z"));
}

// Test unify - variable propagation
TEST(UnifierTest, UnifyVariablePropagation) {
    Substitution sub;
    Term X("X", true);
    Term Y("Y", true);
    Term john("john");

    unify(X, Y, sub);
    bool result = unify(Y, john, sub);
    EXPECT_TRUE(result);

    // X should also be bound to john through Y
    Term resolvedX = applySubstitution(Term("X", true), sub);
    EXPECT_EQ(resolvedX.name, "john");
}

// Test unify - circular binding prevention
TEST(UnifierTest, UnifyCircularBindingPrevention) {
    Substitution sub;
    Term X("X", true);
    Term compound("parent", {Term("X", true), Term("Y", true)}, false);

    bool result = unify(X, compound, sub);
    // This should fail due to occurs check (X occurs in parent(X, Y))
    EXPECT_FALSE(result);
}
// NOLINTEND(readability-identifier-length)