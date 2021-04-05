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

    Polynomial Add(Polynomial b);

    Polynomial Mult(Polynomial b);

    float Eval(float x);

    friend ostream& operator<<(ostream& os, Polynomial& a);
    friend istream& operator>>(istream &in, Polynomial& a);

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





int main()
{    
    Polynomial A;
    Polynomial B;

    cout << "Input poly A\n";
    cin >> A;
    cout << "Input poly B\n";
    cin >> B;

    cout << "Onput poly A\n";
    cout << A << endl;
    cout << "Onput poly B\n";
    cout << B << endl;

    cout << "A + B\n";
    Polynomial C; 
    C = A.Add(B);    
    cout << C << endl;
    
    cout << "A * B\n";
    C = A.Mult(B);
    cout << C << endl;

    float x, ea, eb;
    cout << "x = ";
    cin >> x;
    ea = A.Eval(x);
    cout << "A(" << x << ") = " << ea << endl;
    eb = B.Eval(x);
    cout << "B(" << x << ") = " << eb << endl;
    return 0;
}
