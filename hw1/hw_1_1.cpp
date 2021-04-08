// Homework information
//
// (30%) Write a C++ program to implement the ADT2.3 Polynomial (pp.88) using Representation 3 (dynamic array of (coef, exp) tuples). 
// Implement the Mult(Polynomial p) and Eval(float x). 
// Estimate the computing time for Mult and Eval function.
// Add two more functions to input and output polynomials via overloading the >> and << operators. 
// You should try out at least two runs of your program (execution trace) to demonstrate the Add, Mult, Eval and input, output functions. 
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <tuple>
#include <time.h>

using namespace std;

clock_t tstart, tend;

class Polynomial;

class Term
{
    friend Polynomial;
    friend ostream& operator<<(ostream& os, Polynomial& a);
    friend istream& operator>>(istream &in, Polynomial& a);
    
    private:
    float coef;
    int exp;
};

class Polynomial
{
    public:
    Polynomial();
    Polynomial(float* coefList, int* expList, int t);

    Polynomial Add(Polynomial b); // add (*this) and b, then return a new poly
    Polynomial Mult(Polynomial b); // multiply (*this) and b, then return a new poly
    float Eval(float x); // bring a value into the poly

    friend istream& operator>>(istream &in, Polynomial& a); // for poly input
    friend ostream& operator<<(ostream& os, Polynomial& a); // for poly output
    
    void NewTerm(const float ncoef, const int nexp);

    private:
    Term *termArray; // tuple array to store coef and exp
    int capacity; // size of termArray
    int terms; // number of nonzero terms
};

Polynomial::Polynomial()
{
    capacity = 1;
    termArray = new Term[capacity];
    terms = 0;
}

Polynomial::Polynomial(float* coefList, int* expList, int t)
{
    terms = 0;
    capacity = t;
    termArray = new Term[capacity];
    for(int i = 0; i < t; i++){
        NewTerm(coefList[i], expList[i]);
    }
}

void
Polynomial::NewTerm(const float ncoef, const int nexp)
{
    // termArray is full -> double capacity -> create new termArray with new capacity -> copy
    if(terms == capacity)
    {
        capacity = capacity * 2;
        Term *temp = new Term[capacity];
        std::copy(termArray, termArray+terms, temp);
        delete [] termArray;
        termArray = temp;
    }
    termArray[terms].coef = ncoef;
    termArray[terms++].exp = nexp;
}

Polynomial
Polynomial::Add(Polynomial b)
{
    Polynomial c;
    int aPos = 0;
    int bPos = 0;
    // A and B overlapping terms
    while((aPos < terms) && (bPos < b.terms))
    {
        if(termArray[aPos].exp == b.termArray[bPos].exp)
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if(t) c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        }
        else if(termArray[aPos].exp < b.termArray[bPos].exp)
        {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else
        {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }

    // add the last a
    for(;aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

    // add the last b
    for(;bPos < b.terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    
    return c;
}

Polynomial
Polynomial::Mult(Polynomial b)
{
    Polynomial c;
    for(int aPos = 0; aPos < terms; aPos++)
    {
        Polynomial temp;
        for(int bPos = 0; bPos < b.terms; bPos++)
        {
            temp.NewTerm(termArray[aPos].coef * b.termArray[bPos].coef, termArray[aPos].exp + b.termArray[bPos].exp);
        }
        c = temp.Add(c);
        //cout << termArray[aPos].coef << " * " << b << " = " << temp << endl;
    }
    return c;
}

float
Polynomial::Eval(float k)
{
    float result = 0;
    for(int aPos = 0; aPos < terms; aPos++)
    {
        result += termArray[aPos].coef * pow(k, termArray[aPos].exp);
    }
    return result;
}

istream& operator>>(istream& in, Polynomial& a)
{
    int t, e, i;
    float c;
    cout << "How many terms: ";
    in >> t;

    float cl[t]; // list to store coef
    int el[t]; // list to store exp

    i = 0;
    while(i < t)
    {
        cout << "The " << i+1 << " term: ";
        in >> c >> e;
        // check if the coef is 0 or not
        if(c == 0)
            cout << "Enter again. The coef can't be 0." << endl;
        else
        {
            cl[i] = c;
            el[i] = e;
            i++;
        }
    }
    a = Polynomial(cl, el, t);
    return in;
}

ostream& operator<<(ostream& os, Polynomial& a)
{
    for(int aPos = a.terms-1; aPos >= 0; aPos--)
    {
        if(a.termArray[aPos].coef > 0 && aPos != a.terms-1)
            os << "+" << a.termArray[aPos].coef << "x^" << a.termArray[aPos].exp;
        else
            os << a.termArray[aPos].coef << "x^" << a.termArray[aPos].exp;
    }
    return os;
}

int main()
{    
    Polynomial A;
    Polynomial B;
    float x, ea, eb;
   
    cout << "Input poly A\n";
    cin >> A;
    cout << "Onput poly A\n";
    cout << A << endl;

    cout << endl; // for format

    cout << "Input poly B\n";
    cin >> B;    
    cout << "Onput poly B\n";
    cout << B << endl;

    cout << endl; // for format

    cout << "ADD:" << endl;
    cout << "A + B = ";
    Polynomial C; 
    C = A.Add(B);    
    cout << C << endl;

    cout << endl; // for format
    
    cout << "MULT:" << endl;
    cout << "A * B = ";
    tstart = clock(); // start calculate time
    C = A.Mult(B);
    tend = clock(); // end calculate time
    cout << C << endl;
    cout << "Time = " << (double)(tend - tstart)/CLOCKS_PER_SEC  << "sec" << endl; // print mult time

    cout << endl; // for format

    cout << "EVAL:" << endl;
    cout << "x = ";
    cin >> x;
    tstart = clock(); // start calculate time
    ea = A.Eval(x);
    tend = clock(); // end calculate time
    cout << "A(" << x << ") = " << ea << endl;
    cout << "Time = " << (double)(tend - tstart)/CLOCKS_PER_SEC  << "sec" << endl; // print eval time

    cout << endl; // for format

    tstart = clock(); // start calculate time
    eb = B.Eval(x);
    tend = clock(); // end calculate time
    cout << "B(" << x << ") = " << eb << endl;
    cout << "Time = " << (double)(tend - tstart)/CLOCKS_PER_SEC  << "sec" << endl; // print eval time
    
    return 0;
}

/*
Input1:
3
4 0
3 2
2 3
3
8 0
-2 2
3 4

Input2:
2
2 0
1 1
3
-1 0
-3 1
2 2
102
*/