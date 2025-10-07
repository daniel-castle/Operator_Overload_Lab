// Daniel Castillo  MCSCI-272
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string accountNumber; // unique account id
    std::string accountHolderName; // name of account owner
    double* balance; // pointer to balance

public:
    // Rule of Three
    BankAccount();
    BankAccount(const std::string& acctNum, const std::string& holder, double initialBalance = 0.0);
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    ~BankAccount();

    // Accessors & Mutator
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;
    void setAccountHolderName(const std::string& newName);

    // Operators
    BankAccount& operator+=(double amount); // deposit if amount > 0
    BankAccount& operator-=(double amount); // withdraw if 0 < amount <= balance
    bool operator==(const BankAccount& other) const; // same account number
    bool operator<(const BankAccount& other) const;  // compare balance
    bool operator>(const BankAccount& other) const;  // compare balance

    // Static utilities
    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput(); // clamps negative initial balance to 0
};

#endif