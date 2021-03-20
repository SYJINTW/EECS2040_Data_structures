// Homework information
//
// (30%) Write a C++ program to implement the ADT2.3 Polynomial (pp.88) using Representation 3 (dynamic array of (coef, exp) tuples). 
// Implement the Mult(Polynomial p) and Eval(float x). 
// Estimate the computing time for Mult and Eval function.
// Add two more functions to input and output polynomials via overloading the >> and << operators. 
// You should try out at least two runs of your program (execution trace) to demonstrate the Add, Mult, Eval and input, output functions. 
//

#include <iostream>

class Polynomial
{
    public:
    Polynomial();

    Polynomial Add(Polynomial b);

    Polynomial Mult(Polynomial b);

    Polynomial Eval(Polynomial b);
    
    
};
