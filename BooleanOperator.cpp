#include "BooleanOperator.h"

// ==========================================
//         OPERATOR IMPLEMENTATIONS 
// ==========================================

bool AndOperator::evaluate(bool op1, bool op2) const { return op1 && op2; }
string AndOperator::explain() const { return "AND: True only if both inputs are true."; }

bool OrOperator::evaluate(bool op1, bool op2) const { return op1 || op2; }
string OrOperator::explain() const { return "OR: True if at least one input is true."; }

bool NotOperator::evaluate(bool op1, bool op2) const { return !op1; }
string NotOperator::explain() const { return "NOT: Inverts the input."; }

bool XorOperator::evaluate(bool op1, bool op2) const { return op1 ^ op2; }
string XorOperator::explain() const { return "XOR: True if inputs are different."; }

bool NandOperator::evaluate(bool op1, bool op2) const { return !(op1 && op2); }
string NandOperator::explain() const { return "NAND: False only if both inputs are true."; }

bool NorOperator::evaluate(bool op1, bool op2) const { return !(op1 || op2); }
string NorOperator::explain() const { return "NOR: True only if both inputs are false."; }

// ==========================================
//     BOOLEAN EXPRESSION IMPLEMENTATION
// ==========================================

BooleanExpression::BooleanExpression(string expression) : exp(expression) {}

void BooleanExpression::printExplanations() const {
    cout << "\nExplanation of Operators used:\n";
    if (exp.find("AND") != string::npos && exp.find("NAND") == string::npos) // Since AND is found inside NAND aswell, This line checks if AND is FOUND and NAND is NOT FOUND
        cout << "- " << AndOperator().explain() << "\n";
    if (exp.find("OR") != string::npos && exp.find("NOR") == string::npos && exp.find("XOR") == string::npos) // Similar logic as above
        cout << "- " << OrOperator().explain() << "\n";
    if (exp.find("NOT") != string::npos)
        cout << "- " << NotOperator().explain() << "\n";
    if (exp.find("XOR") != string::npos)
        cout << "- " << XorOperator().explain() << "\n";
    if (exp.find("NAND") != string::npos)
        cout << "- " << NandOperator().explain() << "\n";
    if (exp.find("NOR") != string::npos)
        cout << "- " << NorOperator().explain() << "\n";
}

bool BooleanExpression::evaluateRow(bool a, bool b, bool c) const {
    vector<string> tokens; //Splits the input expression into smaller tokens for parsing
    string current = "";
    
    for (char ch : exp) {
        if (ch == ' ' || ch == '(' || ch == ')') {
            if (current != "") tokens.push_back(current);
            current = "";
        } else {
            current += ch;
        }
    }
    if (current != "") tokens.push_back(current);

    vector<bool> values;
    vector<string> ops;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "NOT") {
            i++; 
            bool val = false;
            if (i < tokens.size()) {
                if (tokens[i] == "A") val = a;
                else if (tokens[i] == "B") val = b;
                else if (tokens[i] == "C") val = c;
            }
            values.push_back(NotOperator().evaluate(val, false));
        }
        else if (tokens[i] == "A") values.push_back(a);
        else if (tokens[i] == "B") values.push_back(b);
        else if (tokens[i] == "C") values.push_back(c);
        else {
            ops.push_back(tokens[i]); 
        }
    }

    if (values.empty()) return false;
    bool result = values[0];

    for (size_t i = 0; i < ops.size(); i++) {
        if (i + 1 < values.size()) {
            if (ops[i] == "AND") result = AndOperator().evaluate(result, values[i+1]);
            else if (ops[i] == "OR") result = OrOperator().evaluate(result, values[i+1]);
            else if (ops[i] == "XOR") result = XorOperator().evaluate(result, values[i+1]);
            else if (ops[i] == "NAND") result = NandOperator().evaluate(result, values[i+1]);
            else if (ops[i] == "NOR") result = NorOperator().evaluate(result, values[i+1]);
        }
    }
    return result;
}

// ==========================================
//      TRUTH TABLE IMPLEMENTATION
// ==========================================

TruthTable::TruthTable(string expStr) : expression(expStr) {}

void TruthTable::displayTable() const {
    expression.printExplanations();

    cout << "\nGenerating Truth Table..." << endl;
    cout << "| A | B | C | " << expression.getExpressionString() << " |" << endl;
    cout << "|---|---|---|-----------------|" << endl;

    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            for (int c = 0; c <= 1; c++) {
                bool result = expression.evaluateRow(a, b, c);
                cout << "| " << a << " | " << b << " | " << c << " |        " << result << "        |\n";
            }
        }
    }
}

void TruthTable::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Expression: " << expression.getExpressionString() << "\n\n";
        outFile << "| A | B | C | Result |" << endl;
        outFile << "|---|---|---|--------|" << endl;

        for (int a = 0; a <= 1; a++) {
            for (int b = 0; b <= 1; b++) {
                for (int c = 0; c <= 1; c++) {
                    bool result = expression.evaluateRow(a, b, c);
                    outFile << "| " << a << " | " << b << " | " << c << " |   " << result << "    |" << endl;
                }
            }
        }
        outFile.close(); 
    } else {
        cout << "Error opening file.\n";
    }
}