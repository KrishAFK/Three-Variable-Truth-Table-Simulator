#ifndef BOOLEAN_OPERATOR_H
#define BOOLEAN_OPERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std; 

// --- 1. Abstract Base Class ---
class BooleanOperator {
public:
    //Using Polymorphism via virtual functions
    //Virtual Function allows a parent class to define a function that will be redefined (overridden) by its child classes.

    virtual bool evaluate(bool op1, bool op2) const = 0;        //Pure Virtual Fucntion becuase of =0
    virtual string explain() const = 0;                         //explain() gives the explanation of what the operator does, before printing the Truth Table
    virtual ~BooleanOperator() = default;
};

// --- 2. Derived Classes ---
class AndOperator : public BooleanOperator {
public:
    bool evaluate(bool op1, bool op2) const override;   // Override function ensures it is using the same function as defined in the parent class
    string explain() const override;
};

class OrOperator : public BooleanOperator {
public:
    bool evaluate(bool op1, bool op2) const override;
    string explain() const override;
};

class NotOperator : public BooleanOperator {
public:
    bool evaluate(bool op1, bool op2) const override; 
    string explain() const override;
};

class XorOperator : public BooleanOperator {
public:
    bool evaluate(bool op1, bool op2) const override;
    string explain() const override;
};

class NandOperator : public BooleanOperator {
public:
    bool evaluate(bool op1, bool op2) const override;
    string explain() const override;
};

class NorOperator : public BooleanOperator {
public:
    bool evaluate(bool op1, bool op2) const override;
    string explain() const override;
};

class BooleanExpression {
//This function handles parsing
private:
    string exp;
public:
    BooleanExpression(string expression);
    void printExplanations() const;
    bool evaluateRow(bool a, bool b, bool c) const;
    string getExpressionString() const { return exp; }
};

class TruthTable {
//This function handles printing the Truth Table
private:
    BooleanExpression expression;
public:
    TruthTable(string expStr);
    void displayTable() const;
    void saveToFile(const string& filename) const; //Function to save the Truth table as .txt file
};

#endif