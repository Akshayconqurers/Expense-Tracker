#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Expense {
public:
    string category;
    double amount;
    string date;

    Expense(string cat, double amt, string dt) : category(cat), amount(amt), date(dt) {}
};

class ExpenseTracker {
private:
    vector<Expense> expenses;
    string filename = "expenses.txt";

public:
    ExpenseTracker() {
        loadFromFile();
    }

    void addExpense() {
        string category, date;
        double amount;

        cout << "Enter expense category: ";
        cin >> category;
        cout << "Enter amount: ";
        cin >> amount;
        cout << "Enter date (DD/MM/YYYY): ";
        cin >> date;

        Expense newExpense(category, amount, date);
        expenses.push_back(newExpense);
        saveToFile(newExpense);
        cout << "Expense added successfully!\n";
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses to show.\n";
            return;
        }

        cout << "Category\tAmount\t\tDate\n";
        cout << "-------------------------------------\n";
        for (const auto &exp : expenses) {
            cout << exp.category << "\t\t" << exp.amount << "\t\t" << exp.date << "\n";
        }
    }

    void calculateTotal() {
        double total = 0;
        for (const auto &exp : expenses) {
            total += exp.amount;
        }
        cout << "Total expenses: " << total << "\n";
    }

    void saveToFile(const Expense &exp) {
        ofstream outFile;
        outFile.open(filename, ios::app); // append mode
        if (outFile.is_open()) {
            outFile << exp.category << " " << exp.amount << " " << exp.date << "\n";
            outFile.close();
        }
    }

    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            // If file doesn't exist, we just return without doing anything
            return;
        }

        string category, date;
        double amount;
        while (inFile >> category >> amount >> date) {
            expenses.push_back(Expense(category, amount, date));
        }
        inFile.close();
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add an expense\n";
        cout << "2. View all expenses\n";
        cout << "3. Calculate total expenses\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tracker.addExpense();
            break;
        case 2:
            tracker.viewExpenses();
            break;
        case 3:
            tracker.calculateTotal();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
