// Function to view all expenses
void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses to display.\n";
        return;
    }
