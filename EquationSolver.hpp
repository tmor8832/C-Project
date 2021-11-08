/* Source code taken from  https://www.daniweb.com/programming/software-development/code/217180/simple-equation-solver-in-c and adapted to meet the needs of the program - all comments are my own and 190+ lines of code were removed from original source code - THOMAS MORRIS */

#ifndef EQUATION_SOLVER_HPP
#define EQUATION_SOLVER_HPP
#include <string>
#include <vector>
using namespace std;

class EquationSolver{
public:
    EquationSolver();
    string doOperation(const string&, char, const string&);
    void correctedString(string&);
    void removeSpaces(string&);
    string parse(const string&);
    bool isSolvable(const string&);
    void calculate(vector<string>&, vector<char>&, const string&);
    double CubicSolve(string&);
    double QuadraticSolve(string&);
    double LinearSolve(string&);
    double ConstantSolve(string&);
    string PolynomialsearchString(string&);
    char TrigSearchString(string&);
    string ExpOrLogSearchString(string&);
    void PolynomialSolve(string);
    void TanSolve(string);
    void CosSolve(string);
    void SinSolve(string);
    void ExpSolve(string);
    void LogSolve(string);
    
    
protected:
    double Polynomial[4];
    double Sin[5], Tan[5], Cos[5], Exp[5], Log[5];
};

#endif





