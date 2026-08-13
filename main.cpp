#include "BooleanOperator.h"


int main() {
    cout << "~ ~ ~ BOOLEAN TRUTH TABLE SIMULATOR ~ ~ ~" << endl;
    cout << "Enter a 3 variable Boolean Expression :" << endl;

    string inputExp;
    getline(cin, inputExp);

    TruthTable table(inputExp);
    table.displayTable();

    cout << "\nWould you like to save this Truth table to a file? (Y/N): ";
    char choice;
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        cout << "Enter filename: ";
        string filename;
        cin >> filename;
        table.saveToFile(filename);
        cout << "Expression and truth table saved successfully!" << endl;
    }

    return 0;
}