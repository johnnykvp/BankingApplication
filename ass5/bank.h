/**
 * bank.h
 *
 * Created by Johnny Pham on 11/28/19.
 */

#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include "account.h"
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class Bank {
public:
    // Create bank
    Bank();
    
    // Delete bank
    ~Bank();
    
    // Reads & processes a file of transactions
    void processTransactions(const string &FileName);
    
    // Prints out all open balances
    void displayAllBankBalances() const;
    
private:
    queue<string> Transactions;
    AccountTree Accounts;
    bool Processed;
    
    // Process account opening transaction
    void accountOpen(string LastName, string FirstName, string AccNum);
    
    // Process account deposit transaction
    void accountDeposit(string AccNum, string Dol, string Hist);
    
    // Process account withdraw transaction
    void accountWithdraw(string AccNum, string Dol, string Hist);
    
    // Process account transfer transaction
    void accountTransfer(string AccNumFrom, string AccNumTo, string Dol, string Hist);
    
    // Process account history display transaction
    void displayIndividualAccount(string AccNum);
};
#endif // ASS5_BANK_H
