Prolog Interpreter Development Roadmap

This document is a step-by-step roadmap for building a Prolog interpreter in C++ using a class-based architecture. Each phase builds on the previous one, with clear milestones.

⸻

Phase 1: Core Data Structures & Initial Setup

Goal: Represent the basic components of Prolog (terms, rules, knowledge base) in C++ classes.

Tasks:
[x] Define a Term class to represent variables, atoms, and compound terms
[ ] Define a Rule class to represent facts (rules with empty body) and rules with bodies
[ ] Define a KnowledgeBase class to store all rules
[ ] Create a simple Utils class/namespace for helper functions (e.g., trimming strings)
[ ] Hardcode a few sample facts and rules to test the structure
[ ] Write print/debug functions for Term, Rule, and KnowledgeBase
[ ] Set up project structure with separate header files and a main.cpp
[ ] Test by printing hardcoded rules to the console

⸻

Phase 2: Unification Engine

Goal: Implement the core logic for matching queries with facts and rules.

Tasks:
[ ] Define a Substitution class/map to track variable bindings
[ ] Implement a Unifier class or function that can unify two Term objects and update substitutions
[ ] Handle variable-to-variable, variable-to-atom, and compound term unifications
[ ] Write unit tests for unification scenarios (success and failure cases)
[ ] Ensure substitution propagation works recursively within compound terms
[ ] Test by unifying hardcoded terms and printing the resulting substitutions

⸻

Phase 3: Query Solver / Backtracking

Goal: Implement the recursive engine that resolves queries using facts and rules.

Tasks:
[ ] Define a Solver class that takes a query and knowledge base
[ ] Implement recursive resolution: check each rule whose head can unify with the query
[ ] Implement handling of the rule body: recursively solve each predicate in order
[ ] Implement backtracking: explore all possible substitutions that satisfy the query
[ ] Support multiple solutions for queries with variables
[ ] Write tests for simple facts and rules (e.g., grandparent example)
[ ] Debug and ensure recursion and backtracking works correctly

⸻

Phase 4: Simple REPL

Goal: Allow the user to type queries interactively and get answers.

Tasks:
[ ] Implement a REPL loop that reads user input
[ ] Parse user input into Term objects for queries
[ ] Call the Solver to resolve queries
[ ] Print results in a user-friendly way, showing variable bindings
[ ] Support multiple solutions (e.g., ; to continue)
[ ] Add basic error handling for invalid input

⸻

Phase 5: Parser for Prolog Files

Goal: Allow the interpreter to read .pl files with facts and rules.

Tasks:
[ ] Implement a parser that reads a Prolog file line by line
[ ] Parse facts and rules into Term and Rule objects
[ ] Detect variables (uppercase) and atoms (lowercase)
[ ] Add parsed rules to the KnowledgeBase
[ ] Test by loading a sample family.pl file and printing all rules

⸻

Phase 6: Optional Enhancements
[ ] Built-in predicates (e.g., =, is, arithmetic operations)
[ ] Lists and structured terms
[ ] Negation as failure (\+) and cut operator (!)
[ ] Optimization of backtracking
[ ] Save/load knowledge base
[ ] Advanced REPL features (history, multi-line queries)

⸻

Notes:
[ ] Always test each phase thoroughly before moving to the next
[ ] Keep the class architecture modular: Term, Rule, KnowledgeBase, Unifier, Solver
[ ] Document each function and class for clarity
[ ] Use a small set of example facts and rules initially to verify correctness
