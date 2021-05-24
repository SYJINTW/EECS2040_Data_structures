#include <iostream>
#include "function_2.hpp"

using namespace std;

int main()
{
    Poly A;
    cout << "Input the polynomial(A)\n";
    cin >> A;
    cout << "A: " << A << endl;
    cout << endl;

    cout << "Input the polynomial(B)\n";
    Poly B;
    cin >> B;
    cout << "B: " << B << endl;
    cout << endl;

    Poly C(A);
    cout << "Poly C(A): " << C << endl;

    Poly D;
    D = B;
    cout << "D = B: " << D << endl;

    cout << endl;

    Poly tmp1 = A + B;
    cout << "A + B: " << tmp1 << endl;
    Poly tmp2 = A - B;
    cout << "A - B: " << tmp2 << endl;
    Poly tmp3 = A * B;
    cout << "A * B: " << tmp3 << endl;

    cout << endl;

    double x;
    cout << "Input a double for Eval: ";
    cin >> x;
    double ans = A.Eval(x);
    cout << "A.Eval(" << x << ") = " << ans << endl;
    cout << endl;
    cout << endl;
    return 0;
}