#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
class Account {
protected:
    string name;
    int accNo;
    double balance;
public:
    Account(string n = "", int a = 0, double b = 0.0) {
        name = n;
        accNo = a;
        balance = b;
    }
    virtual void display() {
        cout << "\nAccount Holder: " << name;
        cout << "\nAccount Number: " << accNo;
        cout << "\nBalance: Rs. " << balance << endl;
    }
    Account& operator+=(double amount) {
        balance += amount;
        logTransaction("Deposited", amount);
        return *this;
    }
    Account& operator-=(double amount) {
        if (balance >= amount) {
            balance -= amount;
            logTransaction("Withdrawn", amount);
        } else {
            cout << "\nInsufficient Balance!" << endl;
        }
        return *this;
    }
    void logTransaction(string type, double amount) {
        ofstream file("account_log.txt", ios::app);
        if (!file) return;
        time_t now = time(0);
        string dt = ctime(&now);
        if (!dt.empty() && dt[dt.length() - 1] == '\n') {
            dt.erase(dt.length() - 1);
        }
        file << dt << " | " << type << " Rs." << amount
             << " | Acc No: " << accNo
             << " | Balance: Rs." << balance << endl;
        file.close();
    }
};
class SavingsAccount : public Account {
public:
    SavingsAccount(string n, int a, double b) : Account(n, a, b) {}
    void display() {
        cout << "\n[Savings Account]";
        Account::display();
    }
};
class CurrentAccount : public Account {
public:
    CurrentAccount(string n, int a, double b) : Account(n, a, b) {}
    void display() /*override for C++11 users*/ {
        cout << "\n[Current Account]";
        Account::display();
    }
};
int main() {
    int choice;
    Account *acc = NULL;

    cout << "BANK ACCOUNT MANAGEMENT SYSTEM\n";
    cout << "----------------------------------\n";

    string name;
    int accNo;
    double balance;

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Account Number: ";
    if (!(cin >> accNo)) return 0;

    cout << "Enter Initial Balance: ";
    if (!(cin >> balance)) return 0;

    cout << "\nSelect Account Type:\n1. Savings\n2. Current\nChoice: ";
    if (!(cin >> choice)) return 0;

    if (choice == 1)
        acc = new SavingsAccount(name, accNo, balance);
    else
        acc = new CurrentAccount(name, accNo, balance);

    do {
        cout << "\n----- MENU -----";
        cout << "\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\n3. Display Details";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        double amt;
        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            if (cin >> amt) {
                (*acc) += amt;
            } else {
                cout << "Invalid amount." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            if (cin >> amt) {
                (*acc) -= amt;
            } else {
                cout << "Invalid amount." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            break;
        case 3:
            acc->display();
            break;
        case 4:
            cout << "\nThank you for using our service!" << endl;
            break;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    } while (choice != 4);

    delete acc;
    return 0;
}

