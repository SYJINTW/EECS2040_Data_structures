#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template <class T>
class Bag
{
public:
    Bag(int bagCapacity = 10);
    virtual  ~Bag();
    virtual int Size() const;
    virtual bool IsEmpty() const;
    virtual T& Element() const;
    virtual void Push(const T& item);
    virtual void Pop();

protected:
    int *array;
    int capacity;
    int top;
    int bottom;
};

template <class T>
class Stack : public Bag<T>
{
public:
    Stack(int stackCapacity = 10);
    ~Stack();
    T& Top() const;
    void Pop() override;
    void Push(const T& item) override;

protected:

};

template <class T>
class Queue : public Bag<T>
{
public:
    Queue(int queueCapacity = 10);
    ~Queue();
};


// Bag

template <class T>
Bag<T>::Bag(int bagCapacity):capacity(bagCapacity)
{
    if(bagCapacity < 1) throw "Queue capacity must be > 0";
    array = new T[capacity];
    top = bottom = 0;
}

// Stack

template <class T>
Stack<T>::Stack(int stackCapacity):Bag<T>::Bag(stackCapacity){} // calling Bag's constructor 

template <class T>
Stack<T>::~Stack(){} // automatic destruct by calling Bag's destructor

// Queue

template <class T>
Queue<T>::Queue(int queueCapacity):Bag<T>::Bag(queueCapacity){} // calling Bag's constructor 

template <class T>
Queue<T>::~Queue(){} // automatic destruct by calling Bag's destructor



int main()
{

}