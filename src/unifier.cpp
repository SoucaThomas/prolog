#include "unifier.hpp"
#include <iostream>
#include <vector>

void Substitution::bind(const std::string& var, const Term& term) { bindings.insert_or_assign(var, term); }

auto Substitution::lookup(const std::string& var) const -> Term { return bindings.at(var); }

auto Substitution::contains(const std::string& var) const -> bool { return bindings.find(var) != bindings.end(); }

void Substitution::print() const {
    std::cout << "{";
    bool first = true;
    for (const auto& [var, term] : bindings) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << var << " = ";
        term.print();
        first = false;
    }
    std::cout << "}";
}

/*
Logic:
If term is a variable and it’s in the substitution → return the bound value
If term is a variable but not bound → return the term as-is
If term is an atom → return as-is
If term is compound → recursively apply to all arguments
*/
auto applySubstitution(const Term& term, const Substitution& sub) -> Term {
    if (term.variable) {
        if (sub.contains(term.name)) {
            //* recursively apply the substitutions
            return applySubstitution(sub.lookup(term.name), sub);
        }

        return term;
    }

    //* term is a atom
    if (term.arguments.empty()) {
        return term;
    }

    //* compound term -> recursively apply substitution
    std::vector<Term> newArguments;

    newArguments.reserve(term.arguments.size());
    for (const auto& arg : term.arguments) {
        newArguments.push_back(applySubstitution(arg, sub));
    }

    return {term.name, newArguments, false};
}

//* Check if variable occurs in term (prevents circular bindings like X = parent(X, Y))
auto occursCheck(const std::string& varName, const Term& term, const Substitution& sub) -> bool {
    //* If term is the same variable, it occurs
    if (term.variable && term.name == varName) {
        return true;
    }

    //* If term is a variable that's bound, check its binding
    if (term.variable && sub.contains(term.name)) {
        return occursCheck(varName, sub.lookup(term.name), sub);
    }

    //* If term is compound, check all arguments
    for (const auto& arg : term.arguments) {
        if (occursCheck(varName, arg, sub)) {
            return true;
        }
    }

    return false;
}

/*
 * Unification Algorithm
 *
 * Implementation based on:
 * Sterling, L., & Shapiro, E. (1994). The Art of Prolog: Advanced Programming Techniques
 * (2nd ed.). MIT Press. (Chapter 4, Section 4.1: Unification, p. 90, Figure 4.1)
 *
 * Reference: https://cliplab.org/~logalg/doc/The_Art_of_Prolog.pdf
 *
 * This implementation follows the recursive variant of the unification algorithm
 * described in Figure 4.1. The algorithm handles:
 *
 * - Variable-to-variable unification (with occurs check)
 * - Variable-to-term unification (with occurs check to prevent circular bindings)
 * - Constant-to-constant unification (name matching)
 * - Compound term unification (recursive unification of arguments)
 *
 * The recursive approach is equivalent to the stack-based algorithm in Figure 4.1,
 * where the call stack replaces the explicit stack data structure.
 *
 * Key cases from Figure 4.1:
 * 1. X is a variable that does not occur in Y: bind X = Y
 * 2. Y is a variable that does not occur in X: bind Y = X
 * 3. X and Y are identical constants/variables: continue (success)
 * 4. X = f(X1...Xn) and Y = f(Y1...Yn): recursively unify each Xi = Yi
 * 5. Otherwise: failure
 */
auto unify(const Term& term1, const Term& term2, Substitution& sub) -> bool {
    //* Step 1: Apply existing sub to both terms first
    auto term1_resolved = applySubstitution(term1, sub);
    auto term2_resolved = applySubstitution(term2, sub);

    //* Step 2: Check if term1_resolved is a variable
    if (term1_resolved.variable) {
        //* If same variable, already unified
        if (term2_resolved.variable && term1_resolved.name == term2_resolved.name) {
            return true;
        }
        //* Check for circular binding
        if (occursCheck(term1_resolved.name, term2_resolved, sub)) {
            return false;
        }
        //* Bind variable to term2_resolved
        sub.bind(term1_resolved.name, term2_resolved);
        return true;
    }

    //* Step 3: Check if term2_resolved is a variable
    if (term2_resolved.variable) {
        //* Check for circular binding
        if (occursCheck(term2_resolved.name, term1_resolved, sub)) {
            return false;
        }
        //* Bind variable to term1_resolved
        sub.bind(term2_resolved.name, term1_resolved);
        return true;
    }

    //* Step 4: Both are atoms (no arguments)
    if (term1_resolved.arguments.empty() && term2_resolved.arguments.empty()) {
        return term1_resolved.name == term2_resolved.name;
    }

    //* Step 5: Both are compound terms
    //* Check if names and argument counts match
    if (term1_resolved.name != term2_resolved.name || term1_resolved.arguments.size() != term2_resolved.arguments.size()) {
        return false;
    }

    //* Recursively unify each argument pair
    for (size_t i = 0; i < term1_resolved.arguments.size(); ++i) {
        if (!unify(term1_resolved.arguments[i], term2_resolved.arguments[i], sub)) {
            return false;
        }
    }

    return true;
};