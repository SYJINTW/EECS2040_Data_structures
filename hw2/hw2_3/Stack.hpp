#ifndef Stack_hpp
#define Stack_hpp

using namespace::std;

template <class T>                  // Class Bag
class Bag {
public:
    Bag(int bagCapacity);
    virtual ~Bag() {delete [] array;}
    
    virtual inline int Size() const {return top + 1;}
    virtual inline bool IsEmpty() const {return Size() == 0;}
    virtual T& Element() const;
    virtual void Push(const T& item);
    virtual void Pop();
    
protected:
    T* array;
    int capacity;
    int top;
};

template <class T>
Bag<T>::Bag(int bagCapacity): capacity(bagCapacity) {
    if (capacity < 1) throw invalid_argument("Capacity must be > 0");
    array = new T[capacity];
    top = -1;
}

template <class T>
inline T& Bag<T>::Element() const {
    if (IsEmpty()) throw invalid_argument("Bag is empty");
    return array[0];
}

template <class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
    if (newSize < 0) throw invalid_argument("New length must be >= 0");
    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

template <class T>
void Bag<T>::Push(const T &item) {
    if (capacity == top + 1) {
        ChangeSize1D(array, capacity, capacity * 2);
        capacity *= 2;
    }
    array[++top] = item;
}

template <class T>
void Bag<T>::Pop() {
    if (IsEmpty()) throw invalid_argument("Bag is empty, cannot delete");
    int deletePos = top / 2;
    copy(array + deletePos + 1, array + top + 1, array + deletePos);
    array[top--].~T();
}

template <class T>                  //Stack base on Bag
class Stack: public Bag<T> {
public:
    Stack(int stackCapacity);
    ~Stack() {}
    T& Top() const;
    void Pop();
    void GetStack();
    friend ostream& operator <<(ostream& out, Stack<T>& s) {
        out << "Total steps = " << s.top + 1 << endl;
        for (int i = 0; i <= s.top; i++) out << i << ": " << s.array[i] << endl;
        return out;
    }
};

template <class T>
Stack<T>::Stack(int bagCapacity): Bag<T>(bagCapacity) {}

template <class T>
T& Stack<T>::Top() const {
    if (Stack<T>::IsEmpty()) throw invalid_argument("Stack is empty");
    return Stack<T>::array[Stack<T>::top];
}

template <class T>
void Stack<T>::Pop() {
    if (Stack<T>::IsEmpty()) throw invalid_argument("Stack is empty. Cannot delete.");
    Stack<T>::array[Stack<T>::top--].~T();
}

template <class T>
void Stack<T>::GetStack() {
    for (int i = 0; i <= Stack<T>::top; i++) cout << Stack<T>::array[i] << " ";
    if (Bag<T>::IsEmpty()) cout << "Empty!";
    cout << endl;
}


#endif
