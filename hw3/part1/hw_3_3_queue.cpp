// Queue
template <class T>
class Queue:public List<T>
{
public:
    Queue();
    ~Queue();
    bool IsEmpty();
    T& Front();
    T& Rear();
    void Push(const T& item);
    void Pop();
protected:
    Node *rear;
};

template <class T>
Queue<T>::Queue():List<T>()
{
    Queue<T>::first = rear = 0;
}

template <class T>
Queue<T>::~Queue() {}

template <class T>
inline bool Queue<T>::IsEmpty() const
{
    return Queue<T>::first == 0;
}

template <class T>
inline T& 
Queue<T>::Front() const
{
    if (IsEmpty()) throw "Queue is empty.";
    return Queue<T>::first -> data;
}

template <class T>
inline T&
Queue<T>::Rear() const
{
    if (IsEmpty()) throw "Queue is empty.";
    return rear -> data;
}

template <class T>
void
Queue<T>::Push(const T& item)
{
    if (IsEmpty())
    {
        Queue<T>::first = rear = new Node<T>;
        rear -> data = item;
        rear -> link = 0;
    }
    else 
    {
        rear = rear -> link = new Node<T>;
        rear -> data = item;
        rear -> link = 0;
    } 
}

template <class T>
void
Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty.";
    Node *node = Queue<T>::first;
    Queue<T>::first = Queue<T>::first->link;
    delete node;
}
