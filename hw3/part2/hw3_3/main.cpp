#include <iostream>
#include <time.h>
#include <chrono>
#include "function.hpp"

using namespace std;

int main()
{
    Matrix A;
    cout << "Construct matrix A" << endl;
    cin >> A;
    cout << "A: " << A << endl;

    Matrix B;
    cout << "Construct matrix B" << endl;
    cin >> B;
    cout << "B: " << B << endl;

    Matrix C;
    C = A + B;
    cout << "A + B = C: " << C << endl;

    Matrix D;
    D = A * B;
    cout << "A * B = D: " << D << endl;

    Matrix E;
    E = D.Transpose();
    cout << "Transpose E: " << E << endl;

    auto start_time = std::chrono::high_resolution_clock::now(); 
    for(int i = 0; i < 100000; i++)
        Matrix F(A);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    cout << "Copy matrix 1 times spend " << time/(std::chrono::milliseconds(1)) << "/100000 ms" << endl;

    return 0;
}