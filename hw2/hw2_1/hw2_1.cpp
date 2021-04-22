#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "function.hpp"

using namespace std;

bool flag = true;

int main()
{
    int cap; 
    string UI;
    Queue<char> Q[2]; // define T as char
    for(int i = 0; i < 2; i++)
    {
        cout << i+1 << "th queue" << endl;
        cout << "Set the queue capacity as: ";
        cin >> cap;
        Queue<char> tmp(cap); 
        Q[i] = tmp;
        cout << "Command: push <element> / pop / front / rear / size / capacity / end" << endl;
        flag = true;
        while(flag)
        {
            cout << ">> ";
            cin >> UI;
            if(UI == "isempty")
            {
                if(Q[i].IsEmpty()) cout << "queue is empty.\n";
                else cout << "queue is not empty.\n";
            }
            else if(UI == "push")
            {
                char c; 
                cin >> c;
                Q[i].Push(c);
            }
            else if(UI == "pop")
            {
                cout << "Pop out " << Q[i].Front() << endl;
                Q[i].Pop();
            }
            else if(UI == "front")
            {
                cout << "The front is " << Q[i].Front() << endl;
            }
            else if(UI == "rear")
            {
                cout << "The rear is " << Q[i].Rear() << endl;
            }
            else if(UI == "size")
            {
                cout << "The size is " << Q[i].Size() << endl;
            }
            else if(UI == "capacity")
            {
                cout << "The capacity is " << Q[i].Capacity() << endl;
            }
            else if(UI == "end")
            {
                flag = false;
            }
            else 
            {
                cout << "Wrong command." << endl;
            }
        }
    }

    // merge two queue
    cout << "Merge two queue" << endl;
    Queue<char> mergeQu;
    mergeQu.MergeQ(Q[0], Q[1]);
    
    // cout two Queue
    for(int i = 0; i < 2; i++)
    {
        cout << "The " << i << " Queue (first to last) -> ";
        while(!Q[i].IsEmpty())
        {
            cout << Q[i].Front() << " ";
            Q[i].Pop();
        }
        cout << endl;
    }
    
    int s = mergeQu.Size();
    cout << "Merge size is " << s << endl; 
    for(int i = 0; i < s; i++)
    {
        cout << i+1 << ": " << mergeQu.Front() << endl;
        mergeQu.Pop();
    } 
}

/*
Input 1:
push a
push b
push c
end
push 1
push 2
push 3
push 4
end
*/
