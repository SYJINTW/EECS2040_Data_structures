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
    cout << "This is a Stack program." << endl;
    cout << "Set the initial capacity as: ";
    cin >> cap;
    Stack<T_TYPE> A(cap); // for Stack and Deque

    int flag = 1;
    cout << "Command: push <element> / pop / size / show / quit" << endl;
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
        else if (S == "pop")
        {
            cout << "pop out " << A.Element() << endl;
            A.Pop();
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