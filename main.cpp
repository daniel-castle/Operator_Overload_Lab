// Daniel Castillo  MCSCI-272
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "BankAccount.h"

using namespace std;

/**
 * Clears the current input state and discards invalid or unwanted characters from the input buffer.
 * This is typically used to handle invalid input and prepare the input stream for further operations.
 */
void ClearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int Menu() {
    int choice;

    cout << "\nBank Account Manager\n";
    cout << "1. Create account\n";
    cout << "2. List accounts\n";
    cout << "3. Show account\n";
    cout << "4. Deposit (+=)\n";
    cout << "5. Withdraw (-=)\n";
    cout << "6. Rename account holder\n";
    cout << "7. Compare two accounts (==, <, >)\n";
    cout << "8. Delete account\n";
    cout << "9. Quit\n";
    cout << "Enter your choice: ";

    while (!(cin >> choice) || choice < 1 || choice > 9) {
        cout << "Invalid choice. Enter 1-9: ";
        ClearBadInput();
    }
    ClearBadInput();
    return choice;
}

/**
 * Searches for a bank account within a vector based on the given account number.
 * Returns the index of the matching account if found, or -1 if not found.
 *
 * @param v The vector of BankAccount objects to search.
 * @param acctNum The account number to look for within the vector.
 * @return The index of the account with a matching account number, or -1 if no match is found.
 */
int FindAccountIndex(const vector<BankAccount>& v, const string& acctNum) {
    for (int i = 0; i < (int)v.size(); ++i)
        if (v[i].getAccountNumber() == acctNum)
            return i;
    return -1;
}

/**
 * Creates a new bank account and adds it to the provided list if valid and unique.
 * Prompts for account details through user input, validates the account number, and prevents
 * duplicate account numbers. Displays appropriate messages for invalid input or duplicate entry.
 *
 * @param accounts A reference to the vector of BankAccount objects where the new account will be added.
 */
void ActionCreate(vector<BankAccount>& accounts) {
    BankAccount account = BankAccount::createAccountFromInput();
    if (account.getAccountNumber().empty()) {
        cout << "[Error] Empty account number. Not created.\n";
        return;
    }
    if (FindAccountIndex(accounts, account.getAccountNumber()) != -1) {
        cout << "[Error] Account number already exists.\n";
        return;
    }
    accounts.push_back(account);
    cout << "[Complete] Account created.\n";
}

/**
 * Lists all bank accounts in the provided list by printing their details.
 * If the accounts list is empty, displays a message indicating no accounts are available.
 *
 * @param accounts A constant reference to the vector of BankAccount objects to be listed.
 */
void ActionList(const vector<BankAccount>& accounts) {
    if (accounts.empty()) { cout << "(No accounts)\n"; return; }
    for (const auto& account : accounts)
        BankAccount::printAccount(account);
}

/**
 * Displays details of a specific bank account based on user input.
 * Prompts the user to input an account number, searches for the account
 * within the provided list of accounts, and displays the account information.
 * If the account is not found, an error message is displayed.
 *
 * @param accounts A constant reference to the vector of BankAccount objects used for searching.
 */
void ActionShow(const vector<BankAccount>& accounts) {
    string acct;
    cout << "Enter account number: ";
    getline(cin, acct);
    int index = FindAccountIndex(accounts, acct);
    if (index == -1) {
        cout << "[Error] Not found.\n"; return;
    }
    BankAccount::printAccount(accounts[index]);
}

/**
 * Handles a deposit operation for a specified bank account.
 * Prompts the user to input the account number and deposit amount.
 * Validates the account number by checking its existence in the provided list of accounts
 * and ensures the deposit amount entered is a valid numeric value.
 * Updates the account balance if the operation is successful, or displays error
 * messages if the account is not found or the input is invalid.
 *
 * @param accounts A reference to the vector of BankAccount objects where the deposit will be processed.
 */
void ActionDeposit(vector<BankAccount>& accounts) {
    string acct;
    cout << "Enter account number: ";
    getline(cin, acct);
    int index = FindAccountIndex(accounts, acct);
    if (index == -1) {
        cout << "[Error] Not found.\n"; return;
    }
    double amount;
    cout << "Enter deposit amount: ";
    if (!(cin >> amount)) {
        cout << "[Error] Invalid amount.\n"; ClearBadInput(); return;
    }
    ClearBadInput();

    accounts[index] += amount; // operator handles messages
    cout << "Balance: $" << accounts[index].getBalance() << '\n';
}

/**
 * Processes a withdrawal operation for a specified bank account.
 * Prompts the user for the account number and withdrawal amount. Validates the input,
 * including checks for a valid account number and a correct numeric value for the withdrawal amount.
 * If the account is found and the input amount is valid, the withdrawal is performed.
 * Otherwise, displays appropriate error messages without altering account data.
 *
 * @param accounts A reference to the vector of BankAccount objects representing the list of accounts.
 */
void ActionWithdraw(vector<BankAccount>& accounts) {
    string acct;
    cout << "Enter account number: ";
    getline(cin, acct);
    int index = FindAccountIndex(accounts, acct);

    if (index == -1) {
        cout << "[Error] Not found.\n"; return;
    }

    double amount;
    cout << "Enter withdrawal amount: ";
    if (!(cin >> amount)) { cout << "[Error] Invalid amount.\n"; ClearBadInput(); return; }
    ClearBadInput();

    accounts[index] -= amount; // operator handles messages
    cout << "Balance: $" << accounts[index].getBalance() << '\n';
}

/**
 * Renames the account holder of a bank account identified by its account number.
 *
 * The method prompts the user to enter the account number of an existing account,
 * searches for the corresponding account in the provided list, and updates the
 * account holder's name to a new value specified by the user. If the account
 * number is not found, an error message is displayed.
 *
 * @param accounts A vector of BankAccount objects representing the existing bank accounts.
 */
void ActionRename(vector<BankAccount>& accounts) {
    string acct;
    cout << "Enter account number: ";
    getline(cin, acct);
    int index = FindAccountIndex(accounts, acct);

    if (index == -1) {
        cout << "[Error] Not found.\n"; return;
    }

    string newName;
    cout << "Enter new holder name: ";
    getline(cin, newName);
    accounts[index].setAccountHolderName(newName);
}


/**
 * Compares the details of two bank accounts selected by their account numbers.
 * The comparison includes checking if the accounts are the same and comparing their balances.
 * Displays the comparison results in the console.
 *
 * @param accounts A vector of BankAccount objects that holds all available accounts for comparison.
 */
void ActionCompare(const vector<BankAccount>& accounts) {
    if (accounts.size() < 2) {
        cout << "[Error] You need at least two accounts to compare.\n";
        return;
    }

    string acct1, acct2;
    cout << "Enter the first account number: ";
    getline(cin, acct1);
    cout << "Enter the second account number: ";
    getline(cin, acct2);

    int firstIndex = FindAccountIndex(accounts, acct1);
    int secondIndex = FindAccountIndex(accounts, acct2);

    if (firstIndex == -1 || secondIndex == -1) {
        cout << "[Error] One or both of those accounts were not found.\n";
        return;
    }

    const BankAccount& A = accounts[firstIndex];
    const BankAccount& B = accounts[secondIndex];

    cout << "\n=== Account Comparison ===\n";
    cout << "Comparing Account #" << A.getAccountNumber() << " and Account #" << B.getAccountNumber() << "...\n";

    // Checks if same account number
    if (A == B) {
        cout << " Both accounts have the same account number.\n";
    }

    // Compare balances
    if (A.getBalance() == B.getBalance()) {
        cout << " Both accounts have the same balance.\n";
    } else if (A < B) {
        cout << " Account #" << A.getAccountNumber() << " has a smaller balance than Account #" << B.getAccountNumber() << ".\n";
    } else {
        cout << " Account #" << A.getAccountNumber() << " has a larger balance than Account " << B.getAccountNumber() << ".\n";
    }

    cout << "===========================\n";
}

/**
 * Deletes a bank account from the given list of accounts based on the account number.
 * If the account number is not found, a message is displayed and the operation is aborted.
 *
 * @param accounts A reference to the vector of BankAccount objects representing the list of accounts.
 */
void ActionDelete(vector<BankAccount>& accounts) {
    string acct;
    cout << "Enter account number to delete: ";
    getline(cin, acct);
    int index = FindAccountIndex(accounts, acct);
    if (index == -1) {
        cout << "[Error] Not found.\n"; return;
    }

    accounts.erase(accounts.begin() + index);
    cout << "Account deleted.\n";
}

/**
 * Entry point of the Bank Account Manager program.
 * Manages a menu-driven interface to perform operations on a list of bank accounts.
 * Users can create, list, display, deposit to, withdraw from, rename,
 * compare, and delete bank accounts, or exit the program.
 *
 * @return Returns 0 upon successful program termination.
 */
int main() {
    vector<BankAccount> accounts;
    int choice;

    do {
        choice = Menu();
        switch (choice) {
            case 1: ActionCreate(accounts); break;
            case 2: ActionList(accounts); break;
            case 3: ActionShow(accounts); break;
            case 4: ActionDeposit(accounts); break;
            case 5: ActionWithdraw(accounts); break;
            case 6: ActionRename(accounts); break;
            case 7: ActionCompare(accounts); break;
            case 8: ActionDelete(accounts); break;
            case 9: cout << "Exiting program.\n"; break;
        }
    } while (choice != 9);

    return 0;
}