//
//  EquationElement.cpp
//  Solver(1)

#include "EquationElement.hpp"
#include <math.h>

EquationElement :: EquationElement(){
    for(int e=-10; e<11; e++){x[e+10] = e;} //initialise x array values from -10 to 10
}

void EquationElement:: PolynomialElements(){
    for(int i =0; i<=20; i++)
    {
        double total =0;
        total += Polynomial[0]*(pow(x[i],3)); //total += x^2 * x value
        total += Polynomial[1]*(pow(x[i],2)); //total += x^2 * x value
        total += Polynomial[2]*(x[i]); //total = x * x value
        total += Polynomial[3];
        y[i] = total;
    }
    CheckWithinRange();
    OutputElements();
}

void EquationElement:: TanElements(){
    for(int i =0; i<=20; i++)
    {   double total =0;
        total += Tan[1]*(pow(x[i],3)); //total += x^2 * x value
        total += Tan[2]*(pow(x[i],2)); //total += x^2 * x value
        total += Tan[3]*(x[i]); //total = x * x value
        total += Tan[4];
        total = tan(total);
        total = Tan[0]*total;
        y[i] = total;}
    CheckWithinRange();
    OutputElements();
}

void EquationElement:: SinElements(){
    for(int i =0; i<=20; i++)
    {   double total =0;
        total += Sin[1]*(pow(x[i],3)); //total += x^2 * x value
        total += Sin[2]*(pow(x[i],2)); //total += x^2 * x value
        total += Sin[3]*(x[i]); //total = x * x value
        total += Sin[4];
        total = sin(total);
        total = Sin[0]*total;
        y[i] = total;
    }
    CheckWithinRange();
    OutputElements();
}

void EquationElement:: CosElements(){
    for(int i =0; i<=20; i++)
    {   double total =0;
        total += Cos[1]*(pow(x[i],3)); //total += x^2 * x value
        total += Cos[2]*(pow(x[i],2)); //total += x^2 * x value
        total += Cos[3]*(x[i]); //total = x * x value
        total += Cos[4];
        total = cos(total);
        total = Cos[0]*total;
        y[i] = total;}
    CheckWithinRange();
    OutputElements();
}

void EquationElement::CheckWithinRange(){
    for(int j =0; j<=20; j++){
        if(y[j] > 23){
            for(int k =0; k<=20; k++){
                y[k] = (y[k]/2); //half the values
                x[k] = (x[k]/2);
                j=0;  }}}}

void EquationElement :: OutputElements(){
    for(int i =0; i<=20; i++){
        cout<<" X element is: " << x[i] << " Y element is: " << y[i] << endl;
    }
}
