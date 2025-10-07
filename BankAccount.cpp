// Daniel Castillo  MCSCI-272
#include "BankAccount.h"
#include <iostream>
#include <limits>
using namespace std;

// Rule of Three

// Default constructor - sets blank info and allocates balance on heap
BankAccount::BankAccount()
    : accountNumber(""), accountHolderName(""), balance(new double(0.0)) {}

// Parameterized constructor - sets info and allocates balance on heap
BankAccount::BankAccount(const string& acctNum, const string& holder, double initialBalance)
    : accountNumber(acctNum), accountHolderName(holder), balance(new double(0.0)) {

    if (initialBalance < 0.0) {
        cout << "[Error] Initial balance cannot be negative.\n";
        *balance = 0.0;
    } else {
        *balance = initialBalance;
    }
}

// Copy constructor - makes a new balance so both accounts have separate memory
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber),
      accountHolderName(other.accountHolderName),
      balance(new double(*other.balance)) {}

// Copy assignment operator - copies data safely, checks for self-assignment
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        *balance = *other.balance; // copy value stored in other
    }
    return *this;
}

// Destructor - releases the memory used for balance
BankAccount::~BankAccount() {
    delete balance;
    balance = nullptr;
}

// Accessors / Mutator

// Return account number
string BankAccount::getAccountNumber() const { return accountNumber; }

// Return account holder name
string BankAccount::getAccountHolderName() const { return accountHolderName; }

// Return balance value
double BankAccount::getBalance() const { return *balance; }

// Change account holder name
void BankAccount::setAccountHolderName(const string& newName) {
    if (newName.empty()) {
        cout << "[Error] Name cannot be empty.\n";
        return;
    }
    accountHolderName = newName;
}

// Operator Overloads

// Deposit money (+=)
BankAccount& BankAccount::operator+=(double amount) {
    if (amount <= 0.0) {
        cout << "[Error] Deposit must be positive.\n";
        return *this;
    }
    *balance += amount;
    return *this;
}

// Withdraw money (-=)
BankAccount& BankAccount::operator-=(double amount) {
    if (amount <= 0.0) {
        cout << "[Error] Withdrawal must be positive.\n";
        return *this;
    }
    if (amount > *balance) {
        cout << "[Error] Insufficient funds.\n";
        return *this;
    }
    *balance -= amount;
    return *this;
}

// Compare accounts by number
bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}

// Compare balances
bool BankAccount::operator<(const BankAccount& other) const {
    return *balance < *other.balance;
}

// Compare balances
bool BankAccount::operator>(const BankAccount& other) const {
    return *balance > *other.balance;
}

//  Static Utility Functions

// Prints account info
void BankAccount::printAccount(const BankAccount& a) {
    cout << "====================\n";
    cout << "Account #: " << a.accountNumber << '\n';
    cout << "Holder  : " << a.accountHolderName << '\n';
    cout << "Balance : $" << a.getBalance() << '\n';
    cout << "====================\n";
}

// Creates account using user input
BankAccount BankAccount::createAccountFromInput() {
    string acct, name;
    double initial = 0.0;

    cout << "Enter new account number: ";
    getline(cin, acct);

    cout << "Enter account holder name: ";
    getline(cin, name);

    cout << "Enter initial balance (>= 0): ";

    if (!(cin >> initial)) {
        cout << "[Erorr] Invalid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        initial = 0.0;
    } else if (initial < 0.0) {
        cout << "[Error] Initial balance cannot be negative.\n";
        initial = 0.0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return BankAccount(acct, name, initial);
}