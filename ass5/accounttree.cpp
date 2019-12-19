/**
 * accounttree.cpp
 *
 * Created by Johnny Pham on 11/29/19.
 */

#include "accounttree.h"

// Default constructor creates AccountTree
AccountTree::AccountTree() = default;

// Delete all nodes in BST
AccountTree::~AccountTree() {
    clear();
}

// Insert new account
bool AccountTree::insert(Account *Account) {
    Node *NewNode = new Node(Account);
    // Make NewNode the Root in an empty tree
    if (isEmpty()) {
        Root = NewNode;
        return true;
    }
    Node* Parent = nullptr;
    Node* Current = Root;
    // Traverse through tree
    while (Current != nullptr) {
        // No duplicates
        if (Account->getId() == Current->Account->getId()) {
            delete NewNode;
            return false;
        }
        if (Account->getId() < Current->Account->getId()) {
            Parent = Current;
            Current = Current->Left;
        }
        else {
            Parent = Current;
            Current = Current->Right;
        }
    }
    // Set as child node
    if (Account->getId() < Parent->Account->getId()) {
        Parent->Left = NewNode;
    }
    else {
        Parent->Right = NewNode;
    }
    return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
    if (Root == nullptr) {
        return false;
    }
    // Traverse tree
    Node* Current = Root;
    while (Current != nullptr) {
        if (AccountNumber == Current->Account->getId() && Account == Current->Account) {
            return true;
        }
        if (AccountNumber == Current->Account->getId() && Account != Current->Account) {
            return false;
        }
        if (AccountNumber < Current->Account->getId()) {
            Current = Current->Left;
        }
        if (AccountNumber > Current->Account->getId()) {
            Current = Current->Right;
        }
    }
    return false;
}

// Obtains an account (similar to retrieve)
// returns an Account object for use inside bank class
Account* AccountTree::obtain(const int &AccountNumber) const {
    if (Root == nullptr) {
        return nullptr;
    }
    Node* Current = Root;
    while (Current != nullptr) {
        if (AccountNumber == Current->Account->getId()) {
            return Current->Account;
        }
        if (AccountNumber < Current->Account->getId()) {
            Current = Current->Left;
        }
        if (AccountNumber > Current->Account->getId()) {
            Current = Current->Right;
        }
    }
    return nullptr;
}

// Display information on all accounts
void AccountTree::display() const {
    preorderPrint(Root);
}

// Recursive helper for display() method
void AccountTree::preorderPrint(Node *Node) const {
    if (Node != nullptr) {
        cout << Node->Account->getLastName() << " " << Node->Account->getFirstName() <<
        " Account ID: " << Node->Account->getId() << endl;
        for (int i = 0; i < 10; i++) {
            if (i == 0) {
                cout << "Money Market: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 1) {
                cout << "Prime Money Market: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 2) {
                cout << "Long-Term Bond: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 3) {
                cout << "Short-Term Bond: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 4) {
                cout << "500 Index Fund: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 5) {
                cout << "Capital Value Fund: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 6) {
                cout << "Growth Equity Fund: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 7) {
                cout << "Growth Index Fund: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 8) {
                cout << "Value Fund: $" << Node->Account->getFund(i) << endl;
            }
            if (i == 9) {
                cout << "Value Stock Index: $" << Node->Account->getFund(i) << endl;
            }
        }
        cout << endl;
        preorderPrint(Node->Left);
        preorderPrint(Node->Right);
    }
}

// Delete all information in AccountTree
void AccountTree::clear() {
    postorderDelete(Root);
    Root = nullptr;
}

// Recursive helper for clear() method
void AccountTree::postorderDelete(Node *Node) {
    if (Node != nullptr) {
        postorderDelete(Node->Left);
        postorderDelete(Node->Right);
        delete Node;
    }
}

// Check if tree is empty
bool AccountTree::isEmpty() const {
    return Root == nullptr;
}
