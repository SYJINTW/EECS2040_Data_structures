#ifndef FUNCTION_H
#define FUNCTION_H

template <class T>
class Bag
{
public:
    // DONE:
    Bag(int bagCapacity = 10);
    // DONE:
    virtual ~Bag();
    // DONE:
    virtual int Size() const;
    // DONE:
    virtual bool IsEmpty() const;
    // DONE:
    virtual void Push(const T &item);

    // TODO: ??????
    // virtual T& Element() const;
    // TODO:
    //virtual void Pop();

protected:
    T *array;
    int capacity;
    int top;    // point to the top element
    int bottom; // the bottom one (point to the empty place)
};


template <class T>
class Stack : public Bag<T>
{
public:
    // DONE:
    Stack(int stackCapacity = 10);
    // DONE:
    ~Stack();
    // DONE:
    T& Element() const;
    // DONE:
    void Pop();
};


template <class T>
class Queue : public Bag<T>
{
public:
    // DONE:
    Queue(int queueCapacity = 10);
    // DONE:
    ~Queue();
    // DONE:
    T& Element() const;
    // DONE:
    void Pop();
};

class Items
{
    int x;
    int y;
    int dir;
};

// Bag
template <class T>
Bag<T>::Bag(int bagCapacity):capacity(bagCapacity)
{
    if (bagCapacity < 1)
        throw "Queue capacity must be > 0";
    array = new T[capacity];
    top = bottom = 0;
}

template <class T>
Bag<T>::~Bag()
{
    delete[] array;
}

template <class T>
int Bag<T>::Size() const
{
    if (IsEmpty())
        return 0;
    else if (top > bottom)
        return top - bottom;
    else
        return capacity - bottom + top;
}

template <class T>
bool Bag<T>::IsEmpty() const
{
    return top == bottom;
}

template <class T>
void Bag<T>::Push(const T &item)
{ // add x to array(top)
    if ((top + 1) % capacity == bottom)
    {
        T *newAr = new T[2 * capacity];
        int start = (top + 1) % capacity;
        if (start < 2)
            copy(array + start, array + start + capacity - 1, newAr);
        else
        {
            copy(array + start, array + capacity, newAr);
            copy(array, array + top + 1, newAr + capacity - start);
        }
        bottom = 2 * capacity - 1;
        top = capacity - 2;
        capacity *= 2;
        delete[] array;
        array = newAr;
    }
    top = (top + 1) % capacity;
    array[top] = item;
}

// Stack

template <class T>
Stack<T>::Stack(int stackCapacity):Bag<T>::Bag(stackCapacity) {} // calling Bag's constructor

template <class T>
Stack<T>::~Stack() {} // automatic destruct by calling Bag's destructor

template <class T>
T &Stack<T>::Element() const
{
    if (Bag<T>::IsEmpty())
        throw "Stack is empty.";
    else
        return Bag<T>::array[Bag<T>::top];
}

template <class T>
void Stack<T>::Pop()
{
    if (Bag<T>::IsEmpty())
        throw "Stack is empty.";
    Bag<T>::array[Bag<T>::top].~T();
    if (Bag<T>::top > 0)
        Bag<T>::top--;
    else
        Bag<T>::top = Bag<T>::capacity - 1;
}

// Queue

template <class T>
Queue<T>::Queue(int queueCapacity) : Bag<T>::Bag(queueCapacity) {} // calling Bag's constructor

template <class T>
Queue<T>::~Queue() {} // automatic destruct by calling Bag's destructor

template <class T>
T &Queue<T>::Element() const
{
    if (Bag<T>::IsEmpty())
        throw "Queue is empty.";
    else
        return Bag<T>::array[(Bag<T>::bottom + 1) % Bag<T>::capacity];
}

template <class T>
void Queue<T>::Pop()
{
    if (Bag<T>::IsEmpty())
        throw "Queue is empty";
    Bag<T>::bottom = (Bag<T>::bottom + 1) % Bag<T>::capacity;
    Bag<T>::array[Bag<T>::bottom].~T(); // destructor for T
}

#endif // FUNCTION_H
