/**
 * bank.cpp
 *
 * Created by Johnny Pham on 11/28/19.
 */

#include <fstream>
#include <sstream>

#include "bank.h"

// Default constructor creates bank
Bank::Bank() = default;

// Default destructor deletes bank
Bank::~Bank() = default;

// Reads file & puts transactions into a queue, then
// splits strings in order to process individual transactions
void Bank::processTransactions(const string &FileName) {
    ifstream TransactionInput(FileName);
    string Line;
    while (getline(TransactionInput, Line)) {
        Transactions.push(Line);
    }
    TransactionInput.close();
    while (Transactions.size() != 0) {
        stringstream Ss(Transactions.front());
        string Token;
        int TokenCount = 0;
        string SubTransaction[5];
        while (Ss >> Token) {
            SubTransaction[TokenCount] = Token;
            TokenCount++;
        }
        if (SubTransaction[0] == "O") {
            accountOpen(SubTransaction[1], SubTransaction[2], SubTransaction[3]);
        }
        if (SubTransaction[0] == "D") {
            accountDeposit(SubTransaction[1], SubTransaction[2], Ss.str());
        }
        if (SubTransaction[0] == "W") {
            accountWithdraw(SubTransaction[1], SubTransaction[2], Ss.str());
        }
        if (SubTransaction[0] == "T") {
            accountTransfer(SubTransaction[1], SubTransaction[3], SubTransaction[2], Ss.str());
        }
        if (SubTransaction[0] == "H") {
            displayIndividualAccount(SubTransaction[1]);
        }
        Transactions.pop();
    }
    cout << endl;
    Processed = true;
    displayAllBankBalances();
}

// Processes an account opening
void Bank::accountOpen(string LastName, string FirstName, string AccNum) {
    int Id = stoi(AccNum);
    Account *NewAccount = new Account(LastName, FirstName, Id);
    bool Insertion = Accounts.insert(NewAccount);
    if (!Insertion) {
        cout << "ERROR: Account " + AccNum +
                " is already open. Transaction refused." << endl;
    }
}

// Processes an account deposit
void Bank::accountDeposit(string AccNum, string Dol, string Hist) {
    int Id = stoi(AccNum.substr(0, 4));
    int Fund = stoi(AccNum.substr(4));
    int Amount = stoi(Dol);
    Account *AccountInUse = Accounts.obtain(Id);
    if (AccountInUse != nullptr) {
        AccountInUse->deposit(Fund, Amount);
        AccountInUse->addHistory(Fund, Hist);
    }
    else {
        cout << "ERROR: could not find Account " +
                AccNum.substr(0, 4) + ". Transaction canceled." << endl;
    }
}

// Processes an account withdraw
void Bank::accountWithdraw(string AccNum, string Dol, string Hist) {
    int Id = stoi(AccNum.substr(0, 4));
    int Fund = stoi(AccNum.substr(4));
    int Amount = stoi(Dol);
    Account *AccountInUse = Accounts.obtain(Id);
    bool Withdrawal = AccountInUse->withdraw(Fund, Amount);
    if (AccountInUse != nullptr) {
        if (Withdrawal) {
            AccountInUse->addHistory(Fund, Hist);
        }
        else {
            AccountInUse->addHistory(Fund, Hist + " (Failed)");
        }
    }
    else {
        cout << "ERROR: could not find Account " +
                AccNum.substr(0, 4) + ". Transaction canceled." << endl;
    }
}

// Processes an account transfer
void Bank::accountTransfer(string AccNumFrom, string AccNumTo, string Dol, string Hist) {
    int IdFrom = stoi(AccNumFrom.substr(0, 4));
    int FundFrom = stoi(AccNumFrom.substr(4));
    int IdTo = stoi(AccNumTo.substr(0, 4));
    int FundTo = stoi(AccNumTo.substr(4));
    int Amount = stoi(Dol);
    Account *AccountInUse = Accounts.obtain(IdFrom);
    Account *OtherAccount = Accounts.obtain(IdTo);
    if (AccountInUse != nullptr) {
        if (OtherAccount != nullptr) {
            AccountInUse->transfer(OtherAccount, FundFrom, FundTo, Amount);
            AccountInUse->addHistory(FundFrom, Hist);
        }
        else {
            cout << "ERROR: Could not find Account " +
                    AccNumTo.substr(0, 4) + ". Transaction canceled." << endl;
        }
    }
    else {
        cout << "ERROR: could not find Account " +
                AccNumFrom.substr(0, 4) + ". Transaction canceled." << endl;
    }
}

// Processes an account history display
void Bank::displayIndividualAccount(string AccNum) {
    // Display transactions for all funds
    if (AccNum.length() == 4) {
        int Id = stoi(AccNum);
        Account *AccountInUse = Accounts.obtain(Id);
        if (AccountInUse != nullptr) {
            cout << *AccountInUse;
        }
        else {
            cout << "ERROR: could not find Account " +
                    AccNum.substr(0, 4) + ". Transaction canceled." << endl;
        }
    }
    // Display transactions for one fund
    if (AccNum.length() == 5) {
        int Id = stoi(AccNum.substr(0, 4));
        int Fund = stoi(AccNum.substr(4));
        Account *AccountInUse = Accounts.obtain(Id);
        if (AccountInUse != nullptr) {
            AccountInUse->displayFund(Fund);
        }
        else {
            cout << "ERROR: could not find Account " +
                    AccNum.substr(0, 4) + ". Transaction canceled." << endl;
        }
    }
}

// Prints out all open bank balances
void Bank::displayAllBankBalances() const {
    // Call to display before processing transactions
    if (!Processed) {
        cout << "Transactions not processed yet." << endl;
    }
    else {
        cout << "Processing done. Final balances:" << endl;
        Accounts.display();
    }
}
