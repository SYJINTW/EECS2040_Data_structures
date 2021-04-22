#ifndef FUNCTION_HPP
#define FUNCTION_HPP

using namespace std;

template <class T>
class Queue
{ 
public:
    // DONE: constructor
    Queue (int queueCapacity = 10);
	
    // DONE: check if the queue is empty by rear == front
    bool IsEmpty( ) const;

    // DONE: add an item into the queue
    void Push(const T& item);

    // DONE: delete the front element of queue 
    void Pop();
    
    // DONE: return top element of stack
    T& Front() const;
    
    // DONE: return top element of stack
    T& Rear() const;

    // DONE: return size of queue
    int Size();

    int Capacity();
    // DONE: return capacity of queue

    void MergeQ(Queue a, Queue b);
    // DONE: merge two queue a, b

private:
    T* queue;
    int front;
    int rear;
    int capacity;
};

template < class T >
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{ 
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue = new T[capacity];
    front = rear = 0; // indicate empty stack
}

template <class T>
inline bool
Queue<T>::IsEmpty() const
{
    return front == rear;
}

template <class T>
void
Queue<T>::Push(const T& item) 
{// add x to queue
    if ((rear + 1) % capacity == front) 
    {   
        T* newQu = new T[2*capacity];
        int start = (front+1) % capacity;
        if(start<2)
           copy(queue+start, queue+start+capacity-1, newQu);
        else{
           copy(queue+start, queue+capacity, newQu);
           copy(queue, queue+rear+1, newQu+capacity-start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete[] queue;
        queue = newQu;
    }
    rear = (rear + 1) % capacity;  
    queue[rear] = item;
}


template <class T>
void
Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty, cannot delete";	
    front = (front + 1) % capacity;
    queue[front].~T(); // destructor for T
}

template <class T>
inline T&
Queue<T>:: Front() const
{
   if (IsEmpty()) throw "Queue is empty. No front element.";
   return queue[(front + 1) % capacity];
}

template <class T>
inline T&
Queue<T>::Rear() const
{
   if (IsEmpty()) throw "Queue is empty. No rear element.";
   return queue[rear];
}

template <class T>
int
Queue<T>::Size()
{
    if(IsEmpty()) return 0;
    else if(rear > front) return rear - front;
    else return capacity - front + rear;
}

template <class T>
int
Queue<T>::Capacity()
{
    return capacity;
}

template <class T>
void
Queue<T>::MergeQ(Queue a, Queue b)
{
    T temp;
    while(!a.IsEmpty() || !b.IsEmpty())
    {
        if(!a.IsEmpty())
        {
            temp = a.Front();
            Push(temp);
            a.Pop();
        }
        if(!b.IsEmpty())
        {
            temp = b.Front();
            Push(temp);
            b.Pop();
        }
    }
    return;
} 

#endif // FUNCTION_HPP