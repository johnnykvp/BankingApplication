/**
 * accounttree.h
 *
 * Created by Johnny Pham on 11/29/19.
 */

#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>

class AccountTree {
public:
    // Create BST
    AccountTree();
    
    // Delete all nodes in BST
    ~AccountTree();
    
    // Insert new account
    bool insert(Account *Account);
    
    // Retrieve account
    // returns true if successful AND *Account points to account
    bool retrieve(const int &AccountNumber, Account *&Account) const;
    
    // Obtains an account (similar to retrieve)
    // returns Account pointer for use in bank
    Account* obtain(const int &AccountNumber) const;
    
    // Display information on all accounts
    void display() const;
    
    // Delete all information in AccountTree
    void clear();
    
    // Check if tree is empty
    bool isEmpty() const;
    
private:
    class Node {
    public:
        explicit Node(Account *Account) :
                      Account{Account}, Right{nullptr}, Left{nullptr} {};
        Account *Account;
        Node *Right;
        Node *Left;
    };
    Node *Root = nullptr;
    
    // Recursive helper for display() method
    void preorderPrint(Node *Node) const;
    
    // Recursive helper for clear() method
    void postorderDelete(Node *Node);
    
};
#endif // ASS5_ACCOUNTTREE_H
