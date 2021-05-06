#include <iostream>
#include "function.hpp"

using namespace std;

int main()
{
    Poly A;
    cin >> A;
    cout << "A: " << A << endl;
    cin >> A;
    cout << "A: " << A << endl;
    Poly B(A);
    cout << "B: " << B << endl;
    Poly C;
    C = A;
    cout << "C: " << C << endl;

    cin >> A;
    cout << "A: " << A << endl;
    
    C = A + B;
    cout << " A + B: " << C << endl;
}