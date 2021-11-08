
/* Source code taken from  https://www.daniweb.com/programming/software-development/code/217180/simple-equation-solver-in-c and adapted to meet the needs of the program - all comments are my own and 190+ lines of code were removed from original source code - THOMAS MORRIS */
#include "EquationSolver.hpp"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
typedef EquationSolver ES; //save typing it every time

ES::EquationSolver(){ //constructor
    for(int i=0; i<5; i++){
        Sin[i] =0;
        Cos[i] =0;
        Tan[i] =0;
        Exp[i] =0;
    }
    for(int i=0; i<4;i++){
        Polynomial[i] =0;
    }
}

string ES::doOperation(const string& lhs, char op, const string& rhs){
    //does the maths for the operator and value(s)
    try { double bdLhs = stod(lhs); //convert the strings to doubles
        double bdRhs = stod(rhs); }//std::invalid_argument: stod: no conversion
    
    catch (const invalid_argument& e){
        cout<<"\nUnfortunately, there was an unexpected error, please re-run the program" << endl;
        exit(EXIT_FAILURE); }
    
    
    double bdLhs = stod(lhs); //convert the strings to doubles
    double bdRhs = stod(rhs);
    
    double value;
    switch(op){
        case '^':
            value= ( pow( bdLhs, bdRhs ) );
            break;
        case '*':
            value=( bdLhs * bdRhs );
            break;
        case '/':
            value=( bdLhs / bdRhs );
            break;
        case '+':
            value=( bdLhs + bdRhs );
            break;
        default: cout<<"There was an error" << endl; //error if no matching operator
    }
    return to_string(value); //convert the double back to a string
}

void ES::correctedString(string& arg){ //removes external brackets and returns string
    
    int pos1 = arg.find_first_of("(");
    int pos2 = arg.find_last_of(")");
    arg[pos1] = arg[pos2] = ' ';
    
}
/**
 * Remove spaces from the argument string.
 */
void ES::removeSpaces(string& argu){
    string temp = "";
    for(size_t i = 0; i < argu.length(); i++)
        if(argu[i] != ' ')
            temp += argu[i];
    argu = temp;
}

//main function of the program, largely unchanged from source code - thoroughly commented.

string ES::parse(const string& param){
    
    string expression = param;
    correctedString(expression); //removes string from outside brackets
    removeSpaces(expression); //removes spaces
    string finalExpression = "";
    
    bool operatorEncountered = true;
    for(size_t i = 0; i < expression.length(); i++){
        if(expression[i] == '('){//find brackets inside the string
            string placeHolder = "("; //set string = open bracket
            int valuesCounted = 1;
            operatorEncountered = false; //no operator encountered as there is a bracket
            for(size_t j = i + 1; valuesCounted != 0; j++){
                if(expression[j] == '(')  //find if there are more open brackets
                    valuesCounted++;
                else if(expression[j] == ')')
                    valuesCounted--;   // loop until brackets cancel one another
                placeHolder += expression[j]; //add to string until brackets cancel each other
            }
            string evaluatedString = parse(placeHolder); //repeat process to remove oustide brackets
            finalExpression += evaluatedString; //add string to final expression
            i += (placeHolder.length() - 1); }//i=where it was before -1
        //sorted string
        
        /* if the character is a negative sign, add so adding a negative */
        else{
            if(expression[i] == '-' && operatorEncountered == false) {
                finalExpression += '+'; }
            /* if the character is a number or operator, add to expression */
            finalExpression += expression[i];
            
            if((expression[i] == '+' || expression[i] == '/' || expression[i] == '^' || expression[i] == '*'  || expression[i] == '-'))
            {operatorEncountered = true; }
            else if(expression[i] != ' ') {operatorEncountered = false;}
        }
    }
    removeSpaces(finalExpression); //after sorting whole expression, remove spaces again
    string perfectExpression = "";
    for(size_t i = 0; i < finalExpression.length(); i++){ //ignore double negatives
        if((i + 1) < finalExpression.length())
            if(finalExpression[i] == '-' && finalExpression[i + 1] == '-')
                i += 2;
        perfectExpression += finalExpression[i];
    }
    finalExpression = perfectExpression; //final sorted expression
    vector<string> totalNumbers; //string vector
    vector<char> totalOperations; //char vector for operations
    
    /* if a number, a negative sign or a . add this to a temporary string
     */
    for(size_t i = 0; i < finalExpression.length(); i++){
        if((finalExpression[i] >= '0' && finalExpression[i] <= '9')
           || finalExpression[i] == '-' || finalExpression[i] == '.'){
            string temp = "";
            for(size_t j = i; j < finalExpression.length(); j++){
                if((finalExpression[j] >= '0' && finalExpression[j] <= '9')
                   || finalExpression[j] == '-' || finalExpression[j] == '.'){
                    temp += finalExpression[j];
                }else break;
            }
            totalNumbers.push_back(temp); //add number string to vector
            i += temp.length() == 0 ? 0 : (temp.length() - 1);
            
        }else if(finalExpression[i] == '*'
                 || finalExpression[i] == '/'
                 || finalExpression[i] == '^'
                 || finalExpression[i] == '+'){
            totalOperations.push_back(finalExpression[i]); //add to total operations vector
        }
    }
    
    ES::calculate(totalNumbers, totalOperations, "^"); //
    ES::calculate(totalNumbers, totalOperations, "/");
    ES::calculate(totalNumbers, totalOperations, "*");
    ES::calculate(totalNumbers, totalOperations, "+");
    return totalNumbers[0]; //return vector final value
}
/**
 * Calculates the numbers in the first vector using the operands in the 2nd vector, based on the expressions allowed which are determined by the string argument.
 NPOS means nothing was found.
 */

void ES::calculate(vector<string>& totalNumbers, vector<char>& totalOperations,
                   const string& arg){
    for(int i = 0; i < totalOperations.size(); i++){
        if( arg.find(totalOperations[i]) != arg.npos){ //if the operations total is less than i
            totalNumbers[i] = doOperation(totalNumbers[i], totalOperations[i], totalNumbers[i + 1]);
            
            //reduces vector sizes of each by 1 now components have been used
            
            int oldNumberLength = totalNumbers.size();
            int oldOperatorLength = totalOperations.size();
            int nextNumberLength = oldNumberLength - 1; //reduce vector sizes by 1
            int nextOperatorLength = oldOperatorLength - 1;
            int NumbersCount = 0;
            int OperatorsCount = 0;
            
            vector<string> NumbersTemporary( nextNumberLength ); //new vectors for size change
            vector<char> OperatorsTemporary ( nextOperatorLength );
            
            
            //loop and add existing vector values to new temporary vector, 1 size smaller!
            for(int j = 0; j < oldNumberLength; j++){
                if(j != (i + 1)){ //excluding number operated on +1, e.g numbers used
                    NumbersTemporary[NumbersCount++] = totalNumbers[j];
                }
                if(j != i && j < oldOperatorLength){
                    OperatorsTemporary[OperatorsCount++] = totalOperations[j];
                }
            }
            totalNumbers = NumbersTemporary; //reduce vector size for next loop
            totalOperations = OperatorsTemporary;
        }
    }
}


bool ES::isSolvable(const string& eq){
    int paranthesisCount = 0; //number of brackets = 0
    bool CanBeSolved = true;
    for(int i = 0; i < eq.length(); i++){ //Check the number of open and
        if(eq[i] == '(')                     // close brackets match in the equation
            paranthesisCount++;
        else if(eq[i] == ')')
            paranthesisCount--;
        
        if(paranthesisCount < 0) //if they do not cancel one another ERROR
        {cout<<"There was an error with your brackets, try again! " << endl;
            CanBeSolved = false;} }
    
    for(int i=0; i < eq.length(); i++){ //check the values entered are valid
        if(eq[i]<39 || eq[i] > 57) //if not within numbers and operators range
            if(eq[i] !=32 && eq[i] != 94){ // if it is not a space or a power sign
                cout<<"You entered a something unexpected! try again! " << endl;
                CanBeSolved = false;
                break;}
    }
    return CanBeSolved;
}


double ES :: CubicSolve(string& cubic){
    string temp = "0";
    int locx3 = 0; //asign value of location to 0
    locx3 = cubic.find("x^3");
    
    if(cubic[locx3-2] == '(') {cubic.insert(locx3-1, "0");}
    
    locx3 = cubic.find("x^3");
    
    string substring = cubic.substr(0, locx3);
    if(isSolvable(substring)){
        
        substring = '(' + substring + ')';
        temp = parse(substring);
        string restOfEquation = cubic.substr(locx3+4, cubic.length());
        
        cubic = restOfEquation;
        
        cout<<"Number of x^3 = " << stod(temp) << endl; }
    
    return stod(temp);}

double ES :: QuadraticSolve(string& quadratic){
    string temp = "0";
    int locx2 = 0; //asign value of location to 0
    locx2 = quadratic.find("x^2");
    
    if(quadratic[locx2-2] == '(') { quadratic.insert(locx2-1, "0");}
    locx2 = quadratic.find("x^2");
    
    string substring = quadratic.substr(0, locx2);
    if(isSolvable(substring)){
        
        substring = '(' + substring + ')';
        
        temp = parse(substring);
        
        cout<<"Number of x^2 = " << stod(temp) << endl;
        
        string restOfEquation = quadratic.substr(locx2+4, quadratic.length());
        quadratic = restOfEquation;}
    
    return stod(temp);}

double ES :: LinearSolve(string& linear)
{
    string temp = "0";
    int locx =0; //asign value of location to 0 for x and constant
    locx = linear.find("x");
    
    if(linear[locx-2] == '(') { linear.insert(locx-1, "0");}
    
    locx = linear.find("x");
    string substring = linear.substr(0, locx);
    if(isSolvable(substring)){
        substring = '(' + substring + ')';
        temp = parse(substring);
        cout<<"Number of x = " << stod(temp) << endl; }
    string restOfEquation = linear.substr(locx+2, linear.length());
    
    linear = restOfEquation;
    
    return stod(temp);}

double ES:: ConstantSolve(string& constant){
    string temp = "0";
    int locC =0; //asign value of location to 0 for x and constant
    locC = constant.find(")");
    if(constant[locC-1] == '(') { constant.insert(locC, "0");}
    locC = constant.find(")");
    if(isSolvable(constant)){
        temp = parse(constant);
        cout<<"Constant value  = " << stod(temp) << endl;}
    return stod(temp); }

string ES :: PolynomialsearchString(string& initString)
{
    removeSpaces(initString); //remove any spaces
    
    string SearchedString = ""; //initialise empty string
    initString = " " + initString + " ";
    
    int x3location, x2location, xlocation = 0; //initialise location to 0
    bool x3found, x2found, xfound= false;
    
    while(initString.find("x^3") != string::npos){
        
        x3found = false;
        while(x3found==false) {
            x3location = initString.find("x^3");
            if(initString[x3location-1] == ')'){ //if there are brackets before term
                for(int z=x3location-1; z>=0; z--){
                    if(initString[z] =='('){
                        string substring = initString.substr(z-1,(x3location-z)+1);
                        SearchedString += substring;
                        initString.erase(z-1,(x3location-z)+4); //erase x3 and bracketed str
                        x3found = true;
                        break;}}  } //end of if loop
            
            else {
                for(int z=x3location-1; z>=0; z--){
                    
                    if((initString[z]== '+' || initString[z] == '-'|| z== 0 )) {
                        string substring = initString.substr(z,(x3location-z));
                        SearchedString += substring;
                        initString.erase(z,(x3location-z)+3); //erase x3 and bracketed str
                        
                        x3found = true;
                        break;}}}}}
    
    SearchedString= '(' + SearchedString + ')' + "x^3 + (";
    
    while(initString.find("x^2") != string::npos){
        x2found = false;
        while(x2found==false) {
            x2location = initString.find("x^2");
            if(initString[x2location-1] == ')'){ //if there are brackets before term
                for(int z=x2location-1; z>=0; z--){
                    if(initString[z] =='('){
                        string substring = initString.substr(z-1,(x2location-z)+1);
                        SearchedString += substring;
                        initString.erase(z-1,(x2location-z)+4); //erase x3 and bracketed str
                        x2found = true;
                        break;}}  } //end of if loop
            
            else {
                for(int z=x2location-1; z>=0; z--){
                    if((initString[z]== '+' || initString[z] == '-'|| z== 0 )) {
                        string substring = initString.substr(z,(x2location-z));
                        SearchedString += substring;
                        initString.erase(z,(x2location-z)+3); //erase x3 and bracketed str
                        x2found = true;
                        break;}}}}}
    
    SearchedString= SearchedString + ")x^2 + (";
    
    while(initString.find("x") != string::npos){
        xfound = false;
        while(xfound==false) {
            xlocation = initString.find("x");
            if(initString[xlocation-1] == ')'){ //if there are brackets before term
                for(int z=xlocation-1; z>=0; z--){
                    if(initString[z] =='('){
                        string substring = initString.substr(z-1,(xlocation-z)+1);
                        SearchedString += substring;
                        initString.erase(z-1,(xlocation-z)+2); //erase x3 and bracketed string
                        xfound = true;
                        break;}}  } //end of if loop
            
            else {
                for(int z=xlocation-1; z>=0; z--){
                    
                    if((initString[z]== '+' || initString[z] == '-'|| z== 0 )) {
                        string substring = initString.substr(z,(xlocation-z));
                        SearchedString += substring;
                        initString.erase(z,(xlocation-z)+1); //erase x3 and bracketed str
                        xfound = true;
                        break;}}}}}
    
    SearchedString= SearchedString + ")x + (" + initString + ")";
    removeSpaces(SearchedString);
    
    for(int y=0; y<SearchedString.length(); y++)
    {
        if(SearchedString[y] =='(')
        {
            if(SearchedString[y+1]=='+'){ SearchedString[y+1]=' ';}
        }
    }
    removeSpaces(SearchedString);
    return SearchedString; }


char ES :: TrigSearchString(string& input)
{   int loctrigterm = 0;
    string copy = input;
    double amplitude = 1;
    char typefound = 'x';
    string stringamp, SearchingFor;
    bool trigtermfound= false;
    removeSpaces(input);
    input = " " + input;
    string SearchedString = ""; //initialise empty string
    if (input.find("tan") != string::npos){
        SearchingFor = "tan";
        typefound = 't';
    }
    else if(input.find("sin") != string::npos){ SearchingFor = "sin";
        typefound = 's';}
    else if(input.find("cos") != string::npos){ SearchingFor = "cos";
        typefound = 'c';}
    
    while(input.find(SearchingFor) != string::npos){
        trigtermfound = false;
        
        while(trigtermfound==false){
            loctrigterm = input.find(SearchingFor);
            if(input[loctrigterm+3] == '('){ //if there are brackets after term
                for(int z=loctrigterm+3; z>=0; z++){
                    if(input[z] ==')'){
                        string substring = input.substr(loctrigterm+4,(z-(loctrigterm+4)));
                        cout<<substring<<endl;
                        SearchedString += substring;
                        if(input[loctrigterm-1] == ' ') {
                            amplitude = 1;
                            cout<<"AMPLITUDE IS " << amplitude<< endl;} //output the amplitude
                        
                        else{
                            for(int a=loctrigterm; a>=0; a--){
                                if (input[a] == 32 || input[a] == '+' || input[a] == '-'){
                                    stringamp = input.substr(a, (loctrigterm-(a)));
                                    try {  amplitude = stod(stringamp); }
                                    
                                    catch(const invalid_argument& e){
                                        cout<<"\nError found, amplitude assumed to be 1\n";
                                        amplitude = 1;
                                    }
                                    
                                    cout<<"AMPLITUDE IS " << amplitude<< endl;}}}
                        
                        input.erase();//erase x3 and bracketed string
                        trigtermfound = true;
                        break; }}}//end of if loop
            
            else { cout<<"trig terms require brackets after them!" << endl;
                input.erase(0, input.length());
                SearchedString = "trig terms require brackets after them!";
                typefound = 'f';
                return typefound;}}}
    
    removeSpaces(SearchedString);
    string test =  PolynomialsearchString(SearchedString);
    cout<<test<< endl; //output the polynomial search of the string
    
    char firstletter; //get the first letter of the trig term
    firstletter = copy[loctrigterm-1];
    switch(firstletter){
        case 't':
            Tan[0] = amplitude;
            TanSolve(test);
            break;
        case 's':
            Sin[0] = amplitude;
            SinSolve(test);
            break;
        case 'c':
            Cos[0] = amplitude;
            CosSolve(test);
            break;
            
        default: cout<<"There was an error" << endl;} //error if no matching operator
    return typefound; }


string ES :: ExpOrLogSearchString(string& input){
    string answer, amp, SearchingFor;
    int locexpterm = 0;
    double amplitude = 1;
    char firstletter = 'z';
    bool exptermfound = false;
    
    for (int i=0;i<input.length();i++){ // input.length() gets the length of the string
        input[i]=tolower(input[i]);    // convert every character of input to lowercase
    }
    
    removeSpaces(input);
    string copy = input;
    input = " " + input;
    string SearchedString = ""; //initialise empty string
    
    if (input.find("exp") != string::npos){
        SearchingFor = "exp";
    }
    else { if(input.find("log") != string::npos){ SearchingFor = "log";} }
    
    while(input.find(SearchingFor) != string:: npos){
        while(exptermfound==false){
            int locexpterm = input.find(SearchingFor);
            firstletter = input[locexpterm];
            if(input[locexpterm+3] == '('){ //if there are brackets after term
                for(int z=locexpterm+3; z>=0; z++){
                    if(input[z] ==')'){
                        string substring = input.substr(locexpterm+4,(z-(locexpterm+4)));
                        cout<<substring<<endl;
                        SearchedString += substring;
                        if(input[locexpterm-1] == ' ') {
                            amplitude = 1;
                            exptermfound = true;}
                        
                        else{
                            for(int a=locexpterm; a>=0; a--){
                                if (input[a] == 32 || input[a] == '+' || input[a] == '-'){
                                    amp = input.substr(a, (locexpterm-a));
                                    try {  amplitude = stod(amp); }
                                    catch(const invalid_argument& e){
                                        cout<<"\nError found, amplitude assumed to be 1\n";
                                        amplitude = 1;
                                    } }}}
                        
                        input.erase();//erase x3 and bracketed string
                        exptermfound = true;
                        break; }}}//end of if loop
            
            else { cout<<"Exponential and log terms require brackets after them!" << endl;
                input.erase(0, input.length());
                answer = "Error";
                return answer;}}}
    
    removeSpaces(SearchedString);
    string test =  PolynomialsearchString(SearchedString);
    cout<<test<< endl;
    SearchedString = test;//output the polynomial search of the string
    
    switch(firstletter){
        case 'l':
            Log[0] = amplitude;
            LogSolve(test);
            break;
        case 'e':
            Exp[0] = amplitude;
            ExpSolve(test);
            break;
        default: cout<<"Sorry, there was an error!" << endl;}
    return SearchedString;
}

void ES :: PolynomialSolve(string input) //get values in to the Polynomial array
{    cout<<"\nPolynomial Function Solved For...\n";
    Polynomial[0] = CubicSolve(input);
    Polynomial[1] = QuadraticSolve(input);
    Polynomial[2] = LinearSolve(input);
    Polynomial[3] = ConstantSolve(input);
    cout << Polynomial[0] << Polynomial[1] << Polynomial[2] << Polynomial[3] << endl;
}

void ES :: TanSolve(string input) //get values in to the Tan array
{    cout<<"\nTan Function Solved For...\n";
    Tan[1] = CubicSolve(input);
    Tan[2] = QuadraticSolve(input);
    Tan[3] = LinearSolve(input);
    Tan[4] = ConstantSolve(input);
    cout<< Tan[0] << Tan[1] << Tan[2] << Tan[3] << Tan[4] << endl;
}

void ES :: CosSolve(string input) //get values in to the Cos array
{    cout<<"\nCos Function Solved For...\n";
    Cos[1] = CubicSolve(input);
    Cos[2] = QuadraticSolve(input);
    Cos[3] = LinearSolve(input);
    Cos[4] = ConstantSolve(input);
    cout<< Cos[0] << Cos[1] << Cos[2] << Cos[3] << Cos[4] << endl;
}

void ES :: SinSolve(string input) //get values in to the Sin array
{    cout<<"\nSin Function Solved For...\n";
    Sin[1] = CubicSolve(input);
    Sin[2] = QuadraticSolve(input);
    Sin[3] = LinearSolve(input);
    Sin[4] = ConstantSolve(input);
    cout<< Sin[0] << Sin[1] << Sin[2] << Sin[3] << Sin[4] << endl;
}

void ES :: ExpSolve(string input) //get values in to the Sin array
{   cout<<"\nExponential Function Solved For...\n";
    Exp[1] = CubicSolve(input);
    Exp[2] = QuadraticSolve(input);
    Exp[3] = LinearSolve(input);
    Exp[4] = ConstantSolve(input);
    cout<< Exp[0] << Exp[1] << Exp[2] << Exp[3] << Exp[4] << endl;
}

void ES :: LogSolve(string input) //get values in to the Sin array
{    cout<<"\nLogarithmic Function Solved For...\n";
    Log[1] = CubicSolve(input);
    Log[2] = QuadraticSolve(input);
    Log[3] = LinearSolve(input);
    Log[4] = ConstantSolve(input);
    cout<< Log[0] << Log[1] << Log[2] << Log[3] << Log[4] << endl;
}
