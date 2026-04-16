# C++ Bank Management Application

A secure, console-based Bank Management Application built in C++ utilizing Object-Oriented Programming (OOP) and persistent file handling. 

This project was developed as Task 2 for the C++ Developer Internship.

## 🚀 Core Features
* **Object-Oriented Design:** Utilizes a `BankAccount` class with encapsulation (`private` variables) to securely manage sensitive financial data.
* **Account Management:** Open new bank accounts with an initial deposit.
* **Financial Transactions:** Securely deposit and withdraw funds with built-in validation (e.g., preventing overdrafts).
* **Balance Inquiry:** Quickly view current account balances formatted to standard currency.
* **Persistent Storage:** All banking records are automatically synchronized with a local `bank_records.txt` file.

## 📂 Project Structure

```text
Bank-Management-App/
│
├── main.cpp                # Main C++ source code with OOP implementation
├── bank_records.txt        # Flat-file database for persistent records
├── bank.exe                # The compiled Windows executable file
└── README.md               # Project documentation