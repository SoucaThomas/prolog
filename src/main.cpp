// NOLINTBEGIN(readability-identifier-length)
#include "term.hpp"
#include "unifier.hpp"
#include <iostream>

using namespace std;

auto main() -> int {
    // Test 1: Simple variable binding
    std::cout << "Test 1: X = john\n";
    Term X("X", true);  // variable
    Term john("john");  // atom
    Substitution sub1;
    bool result1 = unify(X, john, sub1);
    std::cout << "Result: " << (result1 ? "Success" : "Failure") << "\n";
    std::cout << "Substitution: ";
    sub1.print();
    std::cout << "\n\n";

    // Test 2: Variable to variable
    std::cout << "Test 2: X = Y, Y = mary\n";
    Term Y("Y", true);
    Term mary("mary");
    Substitution sub2;
    unify(X, Y, sub2);
    unify(Y, mary, sub2);
    std::cout << "Substitution: ";
    sub2.print();
    std::cout << "\n\n";

    // Test 3: Compound terms
    std::cout << "Test 3: parent(X, Y) = parent(john, mary)\n";
    Term query("parent", {Term("X", true), Term("Y", true)}, false);
    Term fact("parent", {Term("john"), Term("mary")}, false);
    Substitution sub3;
    bool result3 = unify(query, fact, sub3);
    std::cout << "Result: " << (result3 ? "Success" : "Failure") << "\n";
    std::cout << "Substitution: ";
    sub3.print();
    std::cout << "\n";

    return 0;
}
// NOLINTEND(readability-identifier-length)