#ifndef FUNCTION_MIN_HPP
#define FUNCTION_MIN_HPP

#include <iostream>

using namespace std;

template <class T>
class MinHeap 
{  
public:
    // DONE:
    MinHeap(int theCapacity = 10);
    // DONE:
    ~MinHeap() {}  // virtual destructor
    // DONE:
    bool IsEmpty() const; //return true iff empty
    // DONE:
    const T& Top() const; //return reference to the min
    // DONE:
    void Push(const T&);
    // DONE:
    void Pop();
    // TODO:
    void Show();

private:
    T *heap;
    int heapSize;
    int capacity;
};

template <class T>
MinHeap<T>::MinHeap(int theCapacity)
{
    if(theCapacity < 1)
    {
        cout << "Capacity can't lower than 1, so I set it to 10 (default)." << endl;
        theCapacity = 10;
    }
    capacity = theCapacity;
    heapSize = 0;
    heap = new T[capacity+1]; // the first element will store from heap[1] to heap[capacity]
}

template <class T>
bool
MinHeap<T>::IsEmpty() const
{
    if(heapSize == 0)
        return true;
    else 
        return false;
}

template <class T>
const T&
MinHeap<T>::Top() const
{
    return heap[1];
}

template <class T>
void
MinHeap<T>::Push(const T& e)
{
    if(heapSize == capacity) // the heap is full -> double the capacity
    {
        T* newHeap = new T[2*capacity+1];
        copy(heap, heap+capacity-1, newHeap);
        capacity *= 2;
    }

    int currentNode = ++heapSize; 
    // use bubble sort 
    // -> so first put the new element at the last of the list 
    // and compare to the front if the new element is bigger than swap
    while(currentNode != 1 && heap[currentNode/2]>e)
    {  
        heap[currentNode] = heap[currentNode/2];
        currentNode /= 2;
    }
    heap[currentNode] = e;
    // if don't have any element in the heap
    // heapSize = 0 -> 1 and currentNode = 1
    // heap[1] = new element
}

template <class T>
void
MinHeap<T>::Pop()
{
    if(IsEmpty()) cout << "Heap is empty. So you can't delete." << endl;
    heap[1].~T();
    
    T lastElement = heap[heapSize--];
    int currentNode = 1;
    int child = 2;
    while(child <= heapSize)
    {
        if(child < heapSize && heap[child] > heap[child+1]) child++;

        if(lastElement <= heap[child]) break;

        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

template <class T>
void
MinHeap<T>::Show()
{
    for(int i = 0; i < heapSize; i++)
    {
        cout << heap[i+1] << " ";
    }
    cout << endl;
}




#endif // FUNCTION_MIN_HPP