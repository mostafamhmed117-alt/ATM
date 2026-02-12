## Automated Teller Machine (ATM) System

## Overview
A comprehensive ATM Management System that simulates real-life banking interactions.
The system focuses on a seamless user experience,
providing quick financial operations while maintaining strict account security through a dedicated login and balance management system.

## Key Features
 1. Client Authentication
Account-Based Login: Access is granted only via a valid Account Number and PIN/Password.
Session Management: Securely handles one client at a time, ensuring data privacy during transactions.
 2. Advanced Withdrawal Options
Quick Withdraw: Pre-set amounts (e.g., 20, 50, 100, 500) for faster transactions without manual typing.
Normal Withdraw: Allows the user to enter a custom amount, with real-time validation against the available balance.
 3. Core Financial Operations
Deposit: Instant cash deposit functionality that updates the account balance immediately.
Check Balance: A dedicated screen to view the current available funds in a clear format.
 4. Secure Session Control
Logout: Safely terminates the current session and returns to the login screen, preventing unauthorized access to the account.
 Technologies & Concepts
C++ Fundamentals: Utilizing structs or classes to represent client data.
File Handling: Persistent storage of account balances and credentials in Clients.txt.
Input Validation: Ensuring that withdrawal amounts do not exceed the balance and that only numeric inputs are accepted.
UI/UX Design: A clean, console-based menu system with clear navigation.

## ATM-System/
│── main.cpp           # Main menu logic and Program flow        
│── Clients.txt        # Database for account numbers and balances
└── README.md          # Project Documentation

## How to Use
Login: Enter your registered Account Number.
Navigate: Choose from the main menu (Withdraw, Deposit, etc.).
Execute: Perform your transaction; the system will update your file automatically.
Exit: Always use the Logout option before closing the application.
