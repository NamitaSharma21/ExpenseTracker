#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct Expense {
    string Reason;
    int Amount;
    string dateTime;
};

void loadExpenses(vector<Expense>& expense) {
    ifstream file("expenses.txt");
    Expense exp;
    while (file >> exp.Reason >> exp.Amount) {
        getline(file, exp.dateTime);
        expense.push_back(exp);
    }
    file.close();
}

void addExpense(vector<Expense>& expense) {
    Expense exp;
    cout << "Amount spend today: ";
    cin >> exp.Amount;

    cout << "I have spent: " << exp.Amount << endl;

    cout << "On what I have spent amount: ";
    cin >> exp.Reason;

    time_t now = time(0);
    char* dt = ctime(&now);
    exp.dateTime = dt;

    cout << "Time recorded: " << exp.dateTime << endl;

    expense.push_back(exp);

    ofstream file("expenses.txt", ios::app);
    file << exp.Reason << " " << exp.Amount << " " << exp.dateTime;
    file.close();
}

void showSummary(vector<Expense>& expense) {
    int total = 0;
    cout << "\n---- Expense Summary ----\n";
    for (int i = 0; i < expense.size(); i++) {
        cout << "Reason: " << expense[i].Reason
             << ", Amount: " << expense[i].Amount
             << ", Time: " << expense[i].dateTime;
        total += expense[i].Amount;
    }
    cout << "Total spent: " << total << endl;
}

int main() {
    vector<Expense> expense;
    int option;

    loadExpenses(expense);

    do {
        cout << "\n===== Expense Tracker Menu =====\n";
        cout << "1. Add new expense\n";
        cout << "2. Show all expenses\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                addExpense(expense);
                break;
            case 2:
                showSummary(expense);
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option! Try again.\n";
        }
    } while (option != 3);

    system("pause");
    return 0;
}

