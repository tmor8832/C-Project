#include <iostream>
#include <string>
#include "EquationSolver.hpp"
#include "EquationElement.hpp"
using namespace std;
bool again = true;


int main(){
    EquationElement EquationEl;
    char choice1, choice2;
    string trigterm;
    while(again == true){
        cout << "\n\nIs your equation:\n\n Polynomial (1)\n\n Trigonometric (2)\n\n Logarithmic OR Exponential (3)\n\n Enter 1,2 or 3..."<< endl;
        cin >> choice1;
        
        if(choice1 == '1'){
            cout << "Enter an equation you would like to solve, up to and including x^3: " << endl;
            string input;
            cin.ignore();
            getline(cin, input);
            string answer = EquationEl.PolynomialsearchString(input);
            EquationEl.PolynomialSolve(answer);}
    
         if(choice1 == '2'){
            cout << "Enter an equation containing one trig\nterm that you would\n like to solve: " << endl;
            cin.ignore();
            string input;
            getline(cin, input);
           choice2 = EquationEl.TrigSearchString(input);
            switch(choice2){ //switch to see which element function to call
                case 't':
                    EquationEl.TanElements();
                    break;
                case 'c':
                    EquationEl.CosElements();
                    break;
                case 's':
                    EquationEl.SinElements();
                    break;
                default: cout << "There was an error" << endl;}
            }
        
        if(choice1 == '3'){
            cout << "Enter an equation containing:\nOne Logarithmic\n\tor\nOne Exponential\nterm that you would like to solve: " << endl;
            cin.ignore();
            string input;
            getline(cin, input);
            string answer = EquationEl.ExpOrLogSearchString(input);}

    }
    return 0;
}

void whoops(){
    cout<< "Unfortunately, there was an error" << endl;
    again=true;
}

