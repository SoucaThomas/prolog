#pragma once
#include "term.hpp"
#include <map>

class Substitution {
    std::map<std::string, Term> bindings;

   public:
    void bind(const std::string& var, const Term& term);
    [[nodiscard]] auto lookup(const std::string& var) const -> Term;
    [[nodiscard]] auto contains(const std::string& var) const -> bool;
    void print() const;
};

auto applySubstitution(const Term& term, const Substitution& sub) -> Term;
auto occursCheck(const std::string& varName, const Term& term, const Substitution& sub) -> bool;
auto unify(const Term& term1, const Term& term2, Substitution& sub) -> bool;