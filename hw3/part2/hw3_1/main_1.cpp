#include <iostream>
#include "function_1.hpp"

using namespace std;

int main()
{
    // constructs an initially empty list
    cout << "Construct a list A\n";
    Chain<int> A;
    cout << "A: " << A << endl;

    // use InsertFront() to insert 1 to 10 at the front of the list.
    cout << "Insert 1 to 10\n";
    for(int i = 1; i <= 10; i++)
        A.InsertFront(i);
    cout << "A: " << A << endl;
    
    // use DeleteFront() and DeleteBack() to delete 3 element from either side.
    for(int i = 1; i <= 3; i++)
        A.DeleteFront();
    cout << "After delete front\nA: " << A << endl;
    for(int i = 1; i <= 3; i++)
        A.DeleteBack();
    cout << "After delete back\nA: " << A << endl;

    // use Front() and Back() functions to return the first and last elements of the list, respectively.
    cout << "A.Front(): " << A.Front() << endl;
    cout << "A.Back(): " << A.Back() << endl;
    
    // use Get(int i) to returns the ith element in the list.
    cout << "A.Get(2): "<< A.Get(2) << endl;
    cout << endl;
    // use Delete(int i) to delete the ith element
    A.Delete(2);
    cout << "After delete the 2nd element\nA: " << A << endl;
    
    // Insert(int i, T e) to insert as the ith element
    int k = 100;
    A.Insert(2, k);
    cout << "After insert 100 as the 2nd element\nA: " <<  A << endl;
    return 0;
}