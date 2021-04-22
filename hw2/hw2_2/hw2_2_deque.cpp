#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "function.hpp"

using namespace std;

// #define T_TYPE char
#define T_TYPE float

int main()
{
    string S;
    int cap;
    cout << "This is a Deque program." << endl;
    cout << "Set the initial capacity as: ";
    cin >> cap;
    Stack<T_TYPE> A(cap); // for Stack and Deque

    int flag = 1;
    cout << "Command: push_top <element> / push_bottom <element>/ pop_top / pop_bottom / size / show / quit" << endl;
    while (flag)
    {
        cout << ">> ";
        cin >> S;
        if (S == "push_top")
        {
            T_TYPE tmp;
            cin >> tmp;
            A.Push(tmp);
        }
        else if (S == "push_bottom")
        {
            T_TYPE tmp;
            cin >> tmp;
            A.Bag<T_TYPE>::Push_front(tmp);
        }
        else if (S == "pop_top")
        {
            cout << "pop out " << A.Element() << endl;
            A.Pop();
        }
        else if (S == "pop_bottom")
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