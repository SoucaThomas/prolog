#include "term.hpp"
#include <iostream>

using namespace std;
int main() {
    Term term("parent", {Term("john"), Term("mary")});
    term.print();
    return 0;
}