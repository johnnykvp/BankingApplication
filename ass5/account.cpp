/**
 * account.cpp
 *
 * Created by Johnny Pham on 11/29/19.
 */

#include "account.h"
#include <iostream>

// Displays each fund balance & transaction history in account
ostream &operator<<(ostream &Out, const Account &Account) {
    Out << "Displaying Transaction History for " << Account.LastName <<
           " " << Account.FirstName << " by fund." << endl;
    Out << "Money Market: $" << Account.getFund(0) << endl;
    for (string Transaction : Account.TransactionHistory[0]) {
        Out << Transaction << endl;
    }
    Out << "Prime Money Market: $" << Account.getFund(1) << endl;
    for (string Transaction : Account.TransactionHistory[1]) {
        Out << Transaction << endl;
    }
    Out << "Long-Term Bond: $" << Account.getFund(2) << endl;
    for (string Transaction : Account.TransactionHistory[2]) {
        Out << Transaction << endl;
    }
    Out << "Short-Term Bond: $" << Account.getFund(3) << endl;
    for (string Transaction : Account.TransactionHistory[3]) {
        Out << Transaction << endl;
    }
    Out << "500 Index Fund: $" << Account.getFund(4) << endl;
    for (string Transaction : Account.TransactionHistory[4]) {
        Out << Transaction << endl;
    }
    Out << "Capital Value Fund: $" << Account.getFund(5) << endl;
    for (string Transaction : Account.TransactionHistory[5]) {
        Out << Transaction << endl;
    }
    Out << "Growth Equity Fund: $" << Account.getFund(6) << endl;
    for (string Transaction : Account.TransactionHistory[6]) {
        Out << Transaction << endl;
    }
    Out << "Growth Index Fund: $" << Account.getFund(7) << endl;
    for (string Transaction : Account.TransactionHistory[7]) {
        Out << Transaction << endl;
    }
    Out << "Value Fund: $" << Account.getFund(8) << endl;
    for (string Transaction : Account.TransactionHistory[8]) {
        Out << Transaction << endl;
    }
    Out << "Value Stock Index: $" << Account.getFund(9) << endl;
    for (string Transaction : Account.TransactionHistory[9]) {
        Out << Transaction << endl;
    }
    return Out;
}

// Constructor creates account
Account::Account(string LastName, string FirstName, int Id) :
                 LastName(LastName), FirstName(FirstName), Id(Id)  {}

// Default destructor deletes account
Account::~Account() = default;
    
// Obtains account last name
string Account::getLastName() const {
    return LastName;
}
    
// Obtains account first name
string Account::getFirstName() const {
    return FirstName;
}
    
// Obtains account ID
int Account::getId() const {
    return Id;
}

// Obtains account fund
int Account::getFund(int Fund) const {
    return Funds[Fund];
}

// Adds amount to account fund
bool Account::deposit(int FundType, int Amount) {
    Funds[FundType] += Amount;
    return true;
}

// Subtracts amount from account fund
bool Account::withdraw(int FundType, int Amount) {
    if (Funds[FundType] - Amount < 0) {
        // Check if money market fund (0 & 1) or bond fund (2 & 3)
        if (FundType > 3) {
            return false;
        }
        int OtherFund = -1;
        if (FundType == 0) {
            OtherFund = 1;
        }
        if (FundType == 1) {
            OtherFund = 0;
        }
        if (FundType == 2) {
            OtherFund = 3;
        }
        if (FundType == 3) {
            OtherFund = 2;
        }
        // Combined is still not enough
        if (Funds[FundType] + Funds[OtherFund] < Amount) {
            return false;
        }
        // Transfer the necessary amount
        int AmountNeeded = abs(Funds[FundType] - Amount);
        Account *CurrentAccount = this;
        transfer(CurrentAccount, OtherFund, FundType, AmountNeeded);
        // Add transfer to the other fund's transaction history
        string WithdrawTransfer = "T " + to_string(getId()) + to_string(OtherFund) + " " +
                                  to_string(Amount) + " " + to_string(getId()) + to_string(FundType);
        addHistory(OtherFund, WithdrawTransfer);
        Funds[FundType] -= Amount;
        return true;
    }
    Funds[FundType] -= Amount;
    return true;
}

// Subtracts amount from an account fund, then adds that same amount to the other account fund
bool Account::transfer(Account *&OtherAccount, int FundTypeFrom, int FundTypeTo, int Amount) {
    if (Funds[FundTypeFrom] < Amount) {
        return false;
    }
    Funds[FundTypeFrom] -= Amount;
    OtherAccount->deposit(FundTypeTo, Amount);
    // Add deposit to the other fund's transaction history
    string TransferDeposit = "D " + to_string(getId()) + to_string(FundTypeTo) +
                             " " + to_string(Amount);
    addHistory(FundTypeTo, TransferDeposit);
    return true;
}

// Adds transaction line to fund history
void Account::addHistory(int FundType, string Transaction) {
    TransactionHistory[FundType].push_back(Transaction);
}

// Prints an individual account fund balance & transaction history
void Account::displayFund(int Fund) {
    cout << "Displaying Transaction history for " << LastName << " " << FirstName << "'s ";
    if (Fund == 0) {
        cout << "Money Market Fund: $" << Funds[0] << endl;
        for (string Transaction : TransactionHistory[0]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 1) {
        cout << "Prime Money Market: $" << Funds[1] << endl;
        for (string Transaction : TransactionHistory[1]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 2) {
        cout << "Long-Term Bond: $" << Funds[2] << endl;
        for (string Transaction : TransactionHistory[2]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 3) {
        cout << "Short-Term Bond: $" << Funds[3] << endl;
        for (string Transaction : TransactionHistory[3]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 4) {
        cout << "500 Index Fund: $" << Funds[4] << endl;
        for (string Transaction : TransactionHistory[4]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 5) {
        cout << "Capital Value Fund: $" << Funds[5] << endl;
        for (string Transaction : TransactionHistory[5]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 6) {
        cout << "Growth Equity Fund: $" << Funds[6] << endl;
        for (string Transaction : TransactionHistory[6]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 7) {
        cout << "Growth Index Fund: $" << Funds[7] << endl;
        for (string Transaction : TransactionHistory[7]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 8) {
        cout << "Value Fund: $" << Funds[8] << endl;
        for (string Transaction : TransactionHistory[8]) {
            cout << Transaction << endl;
        }
    }
    if (Fund == 9) {
        cout << "Value Stock Index: $" << Funds[9] << endl;
        for (string Transaction : TransactionHistory[9]) {
            cout << Transaction << endl;
        }
    }
}
