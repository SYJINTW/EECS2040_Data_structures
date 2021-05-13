#include <iostream>
#include "function.hpp"

using namespace std;

int main()
{
    Matrix A;
    cin >> A;
    cout << A;
    Matrix B(A);
    cout << B;
    Matrix C;
    C = A + B;
    cout << C;
}