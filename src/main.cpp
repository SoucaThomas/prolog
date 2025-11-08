#include "term.hpp"
#include "rule.hpp"
#include "knowlageBase.hpp"
#include <iostream>

using namespace std;
int main() {
    Term parent("parent", {Term("john"), Term("mary")});
    parent.print();
    cout << endl;

    Term grandparent("grandparent", {Term("john"), Term("mary")});
    grandparent.print();
    cout << endl;

    Term child("child", {Term("john"), Term("mary")});
    child.print();
    cout << endl;

    Term grandchild("grandchild", {Term("john"), Term("mary")});
    grandchild.print();
    cout << endl;

    Rule rule("parent", {parent, child});
    rule.print();
    cout << endl;

    Rule grandparent_rule("grandparent", {grandparent, grandchild});
    grandparent_rule.print();
    cout << endl;

    KnowledgeBase knowledgeBase;
    knowledgeBase.addRule(rule);
    knowledgeBase.addRule(grandparent_rule);
    knowledgeBase.print();
    cout << endl;

    return 0;
}