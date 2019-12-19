/**
 * main.cpp
 *
 * Created by Johnny Pham on 11/30/19.
 */
#include "bank.h"
#include "accounttree.h"
#include "account.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// Testing AccountTree methods
void test01() {
    AccountTree AccTree;
    Account *Acc1 = new Account("Bennis", "Dakota", 2468);
    Account *Acc2 = new Account("Jole", "Jameson", 2468);
    assert(AccTree.insert(Acc1));
    assert(!AccTree.insert(Acc2));
    assert(AccTree.retrieve(2468, Acc1));
    assert(!AccTree.retrieve(2468, Acc2));
    AccTree.clear();
    assert(AccTree.isEmpty());
    delete Acc1;
    delete Acc2;
}

// Testing Account methods
void test02() {
    Account *Acc1 = new Account("Bennis", "Dakota", 2468);
    Account *Acc2 = new Account("Jole", "Jameson", 9078);
    assert(Acc1->deposit(0, 100));
    assert(Acc1->getFund(0) == 100);
    assert(Acc1->withdraw(0, 50));
    assert(!Acc1->withdraw(0, 60));
    assert(Acc1->getFund(0) == 50);
    assert(Acc1->transfer(Acc2, 0, 0, 30));
    assert(!Acc1->transfer(Acc2, 0, 0, 101));
    assert(Acc1->getFund(0) == 20);
    assert(Acc2->getFund(0) == 30);
}

// Main method testing Bank
int main() {
    Bank Bank;
    // Note that tests were done in BankTransIn.txt
    // processTransactions method will call all methods inside bank class
    Bank.processTransactions("BankTransIn.txt");
    test01();
    test02();
    cout << "Done" << endl;
    return 0;
}
