#include <iostream>
#include "function.hpp"

using namespace std;

int main()
{
    Chain<int> A;
    for(int i = 1; i <= 10; i++)
    {
        A.InsertFront(i);
    }
    cout << A;
    
    for(int i = 1; i <= 5; i++)
    {
        A.DeleteFront();
    }
    cout << A;

    for(int i = 1; i <= 2; i++)
    {
        A.DeleteBack();
    }
    cout << A;

    cout << A.Front() << endl;
    
    cout << A.Back() << endl;
    
    cout << A.Get(2) << endl;
    
    A.Delete(2);
    cout << A;
    
    int k = 100;
    A.Insert(2, k);
    cout << A;
    
    k = 500;
    A.Insert(1, k);
    cout << A;
    
}