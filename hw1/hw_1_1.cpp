// Homework information
//
// (30%) Write a C++ program to implement the ADT2.3 Polynomial (pp.88) using Representation 3 (dynamic array of (coef, exp) tuples). 
// Implement the Mult(Polynomial p) and Eval(float x). 
// Estimate the computing time for Mult and Eval function.
// Add two more functions to input and output polynomials via overloading the >> and << operators. 
// You should try out at least two runs of your program (execution trace) to demonstrate the Add, Mult, Eval and input, output functions. 
//

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <tuple>

using namespace std;

class Polynomial;

class Term
{
    friend Polynomial;
    public:
    float coef;
    int exp;
};

class Polynomial
{
    public:
    Polynomial();
    Polynomial(float* coefList, int* expList, int t);

    Polynomial Add(Polynomial b);

    Polynomial Mult(Polynomial b);

    float Eval(float x);

    friend ostream& operator<<(ostream& os, Polynomial& a);

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
        terms++;
    }
}



void
Polynomial::NewTerm(const float ncoef, const int nexp)
{
    // termArray is full -> double capacity -> create new termArray with new capacity -> copy
    if(terms == capacity)
    {
        capacity *= 2;
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
            float t = termArray[aPos].coef + termArray[bPos].coef;
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
    for(;bPos < terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    
    return c;
}

Polynomial
Polynomial::Mult(Polynomial b)
{
    Polynomial c;
    Polynomial *temp;
    int aPos = 0;
    int bPos = 0;
    for(; aPos < terms; aPos++)
    {
        temp = new Polynomial();
        for(; bPos < terms; bPos++)
        {
            if(termArray[aPos].coef * b.termArray[bPos].coef)
                (*temp).NewTerm(termArray[aPos].coef * b.termArray[bPos].coef, termArray[aPos].exp + b.termArray[bPos].exp);
        }
        c.Add(*temp);
        delete [] temp;
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


ostream& operator<<(ostream& os, Polynomial& a)
{
    for(int aPos = 0; aPos < a.terms; aPos++)
    {
        if(a.termArray[aPos].coef >= 0 && aPos != 0)
            os << "+" << a.termArray[aPos].coef << "x^" << a.termArray[aPos].exp;
        else
            os << a.termArray[aPos].coef << "x^" << a.termArray[aPos].exp;
    }
    return os;
}





int main()
{
    int aterms, bterms;
    float acoef[100];
    float bcoef[100];
    int aexp[100];
    int bexp[100];
    
    cout << "How many terms in A?\n";
    cin >> aterms;
    cout << "Input A's coef exp\n";
    for(int i = 0; i < aterms; i++)
        cin >> acoef[i] >> aexp[i];
    Polynomial A(acoef, aexp, aterms);

    
    cout << "How many terms in B?\n";
    cin >> bterms;
    cout << "Input B's coef exp\n";
    for(int i = 0; i < bterms; i++)
        cin >> bcoef[i] >> bexp[i];
    Polynomial B(bcoef, bexp, bterms);

    cout << A << endl;
    cout << B << endl;
    Polynomial C; 
    C = A.Add(B);
    cout << C << endl;
    Polynomial D;
    D = A.Mult(B);
    cout << D << endl;
    return 0;
}
