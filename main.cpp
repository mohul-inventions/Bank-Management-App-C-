#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> 

using namespace std;

const string FILE_NAME = "bank_records.txt";

// --- The Object-Oriented Class ---
class BankAccount {
private:
    long long accountNo; // UPGRADED to long long!
    string name;
    double balance;

public:
    BankAccount(long long accNo, string accName, double initialBalance) {
        accountNo = accNo;
        name = accName;
        balance = initialBalance;
    }

    long long getAccountNo() const { return accountNo; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << fixed << setprecision(2) << amount << ".\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << ".\n";
        } else if (amount > balance) {
            cout << "Error: Insufficient funds! Current balance is $" << balance << "\n";
        } else {
            cout << "Invalid withdrawal amount!\n";
        }
    }

    void displayBalance() const {
        cout << "Account: " << accountNo << " | Name: " << name 
             << " | Balance: $" << fixed << setprecision(2) << balance << "\n";
    }
};

// --- File Handling Functions ---

vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    ifstream file(FILE_NAME);
    
    if (!file.is_open()) return accounts;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string accStr, name, balStr;
        
        getline(ss, accStr, ',');
        getline(ss, name, ',');
        getline(ss, balStr, ',');

        // Safely try to load the data, skip the line if it's corrupted
        try {
            if (!accStr.empty() && !balStr.empty()) {
                accounts.push_back(BankAccount(stoll(accStr), name, stod(balStr)));
            }
        } catch (...) {
            // If stod or stoll fails, we just silently skip the broken line
            continue; 
        }
    }
    file.close();
    return accounts;
}

void saveAccounts(const vector<BankAccount>& accounts) {
    ofstream file(FILE_NAME);
    for (const auto& acc : accounts) {
        file << acc.getAccountNo() << "," << acc.getName() << "," << acc.getBalance() << "\n";
    }
    file.close();
}

// --- Menu Operations ---

void createAccount() {
    vector<BankAccount> accounts = loadAccounts();
    long long accNo; // UPGRADED!
    string name;
    double initialDeposit;

    cout << "\n--- Open New Account ---\n";
    cout << "Enter Account Number: ";
    cin >> accNo;

    // Failsafe: If the user types letters instead of numbers, clear the error
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: Invalid account number format.\n";
        return;
    }
    
    for (const auto& acc : accounts) {
        if (acc.getAccountNo() == accNo) {
            cout << "Error: Account number already exists!\n";
            return;
        }
    }

    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, name);
    cout << "Enter Initial Deposit: $";
    cin >> initialDeposit;

    BankAccount newAccount(accNo, name, initialDeposit);
    accounts.push_back(newAccount);
    saveAccounts(accounts);
    
    cout << "Account created successfully!\n";
}

void performTransaction(int type) {
    vector<BankAccount> accounts = loadAccounts();
    long long accNo; // UPGRADED!
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    for (auto& acc : accounts) {
        if (acc.getAccountNo() == accNo) {
            found = true;
            if (type == 1) {
                double amount;
                cout << "Enter Deposit Amount: $";
                cin >> amount;
                acc.deposit(amount);
            } else if (type == 2) {
                double amount;
                cout << "Enter Withdrawal Amount: $";
                cin >> amount;
                acc.withdraw(amount);
            } else if (type == 3) {
                acc.displayBalance();
            }
            break; 
        }
    }

    if (found && type != 3) {
        saveAccounts(accounts); 
    } else if (!found) {
        cout << "Error: Account not found.\n";
    }
}

// --- Main Menu ---

int main() {
    int choice;
    do {
        cout << "\n=================================\n";
        cout << "    Thiranex Bank Management     \n";
        cout << "=================================\n";
        cout << "1. Open New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: performTransaction(1); break;
            case 3: performTransaction(2); break;
            case 4: performTransaction(3); break;
            case 5: cout << "Thank you for banking with us. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}