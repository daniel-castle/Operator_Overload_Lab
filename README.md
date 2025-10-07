# Bank Account Management System

**Course:** MCSCI-272  
**Author:** Daniel Castillo  

## Class Information

### Data Members
| Name | Type | Description |
|------|------|--------------|
| `accountNumber` | `std::string` | Stores the unique account number. |
| `accountHolderName` | `std::string` | Stores the account holder's name. |
| `balance` | `double*` | Points to the account balance (used for the Rule of Three practice). |

---

### Key Methods
- **Constructors**
  - `BankAccount()` — Default constructor, sets empty values and $0 balance.  
  - `BankAccount(acctNum, holder, balance)` — Parameterized constructor with given info.  
  - `BankAccount(const BankAccount&)` — Copy constructor for deep copying.  
  - `operator=` and `~BankAccount()` — Manage memory safely (Rule of Three).

- **Accessors / Mutator**
  - `getAccountNumber()`, `getAccountHolderName()`, `getBalance()`  
  - `setAccountHolderName()` — updates the name (with validation).

- **Operator Overloads**
  - `+=` — Deposit into the account.  
  - `-=` — Withdraw from the account (checks for sufficient funds).  
  - `==`, `<`, `>` — Compare accounts by number or balance.

- **Static Functions**
  - `printAccount()` — Displays formatted account details.  
  - `createAccountFromInput()` — Prompts the user for account info and creates a new account.

---

## Program Features
- Create, list, and show individual accounts  
- Deposit or withdraw money  
- Change account holder name  
- Compare two accounts (`==`, `<`, `>`)  
- Delete accounts  
- All actions use **input validation** to prevent errors  
