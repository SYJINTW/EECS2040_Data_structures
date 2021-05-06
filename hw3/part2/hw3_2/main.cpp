#include <iostream>
#include "function.hpp"

using namespace std;

int main()
{
    Poly A;
    cin >> A;
    Poly B;
    cin >> B;
    Poly C = A - B;
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "C: " << C << endl;
    Poly D = A + B;
    cout << "D: " << D << endl;
    double x;
    cin >> x;
    double ans = C.Eval(x);
    cout << "ans = " << ans << endl;
}