#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "function.hpp"

using namespace std;

#define T_TYPE char

int main()
{
    string S;
    int cap;
    cout << "Set the initial capacity as: ";
    cin >> cap;
    Stack<T_TYPE> A(cap); // for Stack and Deque
    //Queue<T_TYPE> A(cap); // for Queue

    int flag = 1;
    while (flag)
    {
        cout << ">> ";
        cin >> S;
        if (S == "push")
        {
            T_TYPE tmp;
            cin >> tmp;
            A.Push(tmp);
        }
        else if (S == "push_front")
        {
            T_TYPE tmp;
            cin >> tmp;
            A.Bag<T_TYPE>::Push_front(tmp);
        }
        else if (S == "pop")
        {
            cout << "pop out " << A.Element() << endl;
            A.Pop();
        }
        else if (S == "pop_first") // for Deque
        {
            cout << "pop out " << A.Bag<T_TYPE>::Element() << endl;
            A.Bag<T_TYPE>::Pop();
        }
        else if (S == "size")
        {
            cout << "size is " << A.Size() << endl;
        }
        else if (S == "quit")
        {
            flag = 0;
        }
        else cout << "command wrong" << endl;
    }
    
    cout << "The left element (first to last): ";
    while(!A.IsEmpty())
    {
        cout << A.Bag<T_TYPE>::Element() << " ";
        A.Bag<T_TYPE>::Pop(); 
    }
    cout << endl;

    return 0;
}