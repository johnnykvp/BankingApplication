/**
 * account.h
 *
 * Created by Johnny Pham on 11/29/19.
 */

#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Account {
    // Displays all fund balances in account
    friend ostream &operator<<(ostream &Out, const Account &Account);
    
public:
    // Creates account
    explicit Account(string LastName, string FirstName, int Id);
    
    // Deletes account
    ~Account();
    
    // Obtains last name
    string getLastName() const;
    
    // Obtains first name
    string getFirstName() const;
    
    // Obtains ID
    int getId() const;
    
    // Obtains fund balance
    int getFund(int Fund) const;
    
    // Adds amount to fund
    bool deposit(int FundType, int Amount);
    
    // Subtracts amount from fund
    bool withdraw(int FundType, int Amount);
    
    // Subtracts amount from one fund & adds that same amount to the other fund
    bool transfer(Account *&OtherId, int FundTypeFrom, int FundTypeTo, int Amount);
    
    // Adds transaction line to the fund history
    void addHistory(int FundType, string Transaction);
    
    // Prints the transaction history of an individual fund
    void displayFund(int Fund);
    
private:
    string LastName;
    string FirstName;
    int Id;
    // Initialize values to 0
    int Funds[10] = { };
    // Array of vectors holding transaction history for each fund
    vector<string> TransactionHistory[10];
};

#endif // ASS5_ACCOUNT_H
