#include <iostream>
#include <iomanip>
#include "function_max.hpp"
#include "function_min.hpp"

using namespace std;

int main()
{
    int num, tmp;
    MaxHeap<int> Q;
    MinHeap<int> H;

    if(Q.IsEmpty())
        cout << "Max Heap is empty." << endl;
    else
        cout << "Max Heap is not empty." << endl;

    if(H.IsEmpty())
        cout << "Min Heap is empty." << endl;
    else
        cout << "Min Heap is not empty." << endl;
    
    cout << endl;

    cout << "How many elements in the Max/Min heaps: ";
    cin >> num;
    cout << "Insert " << num << " elements: ";
    while(num--)
    {
        cin >> tmp;
        Q.Push(tmp);
        H.Push(tmp); 
    }

    cout << endl;    

    cout << "The max element of Max Heap: " <<  Q.Top() << endl;
    cout << "The min element of Min Heap: " <<  H.Top() << endl;
    
    cout << endl;

    cout << "Max heap: ";
    Q.Show();
    cout << "Min heap: ";
    H.Show();

    cout << endl;

    cout << "Pop Max heap." << endl;
    Q.Pop();
    cout << "Pop Min heap." << endl;
    H.Pop();

    cout << endl;

    cout << "The max element of Max Heap: " <<  Q.Top() << endl;
    cout << "The min element of Min Heap: " <<  H.Top() << endl;

    cout << endl;

    cout << "Max heap: ";
    Q.Show();
    cout << "Min heap: ";
    H.Show();    

}

// 50 5 30 40 80 35 2 20 15 60 70