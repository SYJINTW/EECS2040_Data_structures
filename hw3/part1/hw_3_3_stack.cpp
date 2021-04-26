// Stack

template <class T>
class Stack:public List<T>
{
public:
    Stack();
    ~Stack();
    bool IsEmpty();
    T& Top() const;
    void Push(const T& value);
    void Pop();
};

template <class T>
Stack<T>::Stack():List<T>() {}

template <class T>
Stack<T>::~Stack() {}

template <class T>
inline bool
Stack<T>::IsEmpty() {return Stack<T>::first == 0;}

template <class T>
T&
Stack<T>::Top() const
{
    if (Stack<T>::IsEmpty()) throw "Stack is empty.";
    return Stack<T>::first -> data;
}

template <class T>
void
Stack<T>::Push(const T& value)
{
    Node *node = new Node;
    node -> data = value;
    node -> link = Stack<T>::first;
    Stack<T>::first = node;
}

template <class T>
void
Stack<T>::Pop()
{
    if (Stack<T>::IsEmpty()) throw "Stack is empty.";
    Node *node = Stack<T>::first;
    Stack<T>::first = Stack<T>::first -> link;
    delete node;
}