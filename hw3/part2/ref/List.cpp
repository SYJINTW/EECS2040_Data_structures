#include <iostream>

using namespace::std;

template <class T> class List;

template <class T>
class Node {
    friend class List<T>;
private:
    T data;
    Node<T>* link;
public:
    Node(const T e = NULL, Node<T>* next = NULL): data{e}, link{next} {}
};


template <class T>
class List {
private:
    Node<T>* first;
public:
    List(): first{NULL} {}
    ~List();
    int Size();
    void InsertFront(const T& e);
    void InsertBack(const T& e);
    void Insert(int i, T e);
    void DeleteFront();
    void DeleteBack();
    void Delete(int i);
    T& Front();
    T& Back();
    T& Get(int i);
    void Concatenate(List<T>& b);
    void Reverse();
    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* startNode = 0): current{startNode} {};
        T& operator *() const { return current -> data; }
        T* operator ->() const { return &current -> data; }
        Iterator& operator++ () {
            current = current -> link;
            return *this;
        }
        Iterator operator ++(int) {
            Iterator old = *this;
            current = current -> link;
            return old;
        }
        bool operator !=(const Iterator right) const { return current != right.current; }
        bool operator ==(const Iterator right) const { return current == right.current; }
    };
    Iterator Begin() { return Iterator(first); }
    Iterator End() {return Iterator(NULL); }
    friend ostream& operator <<(ostream& out, List<T>& L) {
        out << "List = ";
        for (Iterator itr = L.Begin(); itr != L.End(); itr++) out << *itr << " ";
        return out << endl;
    }
};

int main() {
    try {
        cout << "0 = Exit; 1 = Integer; 2 =  Float; 3 = Character; Enter the number: ";
        int type = 0;
        cin >> type;
        if (type == 1) {                                             // Test integer type
            List<int> L;
            int element;
            int times = 0;
            cout << "How many elements are in the List: ";
            cin >> times;
            cout << "Enter the List: ";
            for (int i = 0; i < times; i++) {
                cin >> element;
                L.InsertBack(element);
            }
            cout << L;                                              // Test overload <<, iterator, Begin, End
            cout << "The first element: " << L.Front() << endl;     // Test function Front
            cout << "The last element: " << L.Back() << endl;       // Test function Back
            cout << "Enter i to get the ith element in the List: "; // Test function Get
            int ith;
            cin >> ith;
            cout << "The " << ith << "th element in the List: " << L.Get(ith) << endl;
            while (1) {
                cout << "0 = Exit; 1 = Add a element; 2 = Delete a element; 3 = Concat a List; 4 = Reverse the List; ";
                cout << "Enter the number: ";
                int action = 0;
                cin >> action;
                if (action == 1) {
                    cout << "0 = Go back; 1 = InsertFront; 2 = InsertBack; 3 = Insert at a position; Enter the number: ";
                    int function = 0;
                    cin >> function;
                    if (function == 1) {                            // Test function InsertFront
                        cout << "Enter a element you want to insert at the front of the List: ";
                        cin >> element;
                        L.InsertFront(element);
                        cout << L;
                    } else if (function == 2) {                     // Test function InsertBack
                        cout << "Enter a element you want to insert at the back of the List: ";
                        cin >> element;
                        L.InsertBack(element);
                        cout << L;
                    } else if (function == 3) {                     // Test function Insert
                        cout << "Enter i to insert a new element as ith element in the List: ";
                        cin >> ith;
                        cout << "Enter a element you want to insert as " << ith << "th element in the List: ";
                        cin >> element;
                        L.Insert(ith, element);
                        cout << L;
                    } else {}
                } else if (action == 2) {
                    cout << "0 = Go back; 1 = DeleteFront; 2 = DeleteBack; 3 = Delete ith element; Enter the number: ";
                    int function = 0;
                    cin >> function;
                    if (function == 1) {                            // Test function DeleteFront
                        L.DeleteFront();
                        cout << L;
                    } else if (function == 2) {                     // Test function DeleteBack
                        L.DeleteBack();
                        cout << L;
                    } else if (function == 3) {                     // Test function Delete
                        cout << "Enter i to delete ith element in the List: ";
                        cin >> ith;
                        L.Delete(ith);
                        cout << L;
                    } else {}
                } else if (action == 3) {                           // Test function Concatenate
                    List<int> L2;
                    cout << "Enter a List that you want to concat at the back of the first List\n";
                    cout << "How many elements are in the List: ";
                    cin >> times;
                    cout << "Enter the List: ";
                    for (int i = 0; i < times; i++) {
                        cin >> element;
                        L2.InsertBack(element);
                    }
                    cout << "The second List: " << L2;
                    L.Concatenate(L2);
                    cout << "The List after concat the second List: " << L;
                } else if (action == 4) {
                    L.Reverse();
                    cout << "The reversed List: " << L;
                } else {                                            // Exit
                    return 0;
                }
            }
        } else if (type == 2) {                                     // Test float type.
            List<float> L;
            float element;
            int times = 0;
            cout << "How many elements are in the List: ";
            cin >> times;
            cout << "Enter the List: ";
            for (int i = 0; i < times; i++) {
                cin >> element;
                L.InsertBack(element);
            }
            cout << L;                                              // Test overload <<, iterator, Begin, End
            cout << "The first element: " << L.Front() << endl;     // Test function Front
            cout << "The last element: " << L.Back() << endl;       // Test function Back
            cout << "Enter i to get the ith element in the List: "; // Test function Get
            int ith;
            cin >> ith;
            cout << "The " << ith << "th element in the List: " << L.Get(ith) << endl;
            while (1) {
                cout << "0 = Exit; 1 = Add a element; 2 = Delete a element; 3 = Concat a List; 4 = Reverse the List; ";
                cout << "Enter the number: ";
                int action = 0;
                cin >> action;
                if (action == 1) {
                    cout << "0 = Go back; 1 = InsertFront; 2 = InsertBack; 3 = Insert at a position; Enter the number: ";
                    int function = 0;
                    cin >> function;
                    if (function == 1) {                            // Test function InsertFront
                        cout << "Enter a element you want to insert at the front of the List: ";
                        cin >> element;
                        L.InsertFront(element);
                        cout << L;
                    } else if (function == 2) {                     // Test function InsertBack
                        cout << "Enter a element you want to insert at the back of the List: ";
                        cin >> element;
                        L.InsertBack(element);
                        cout << L;
                    } else if (function == 3) {                     // Test function Insert
                        cout << "Enter i to insert a new element as ith element in the List: ";
                        cin >> ith;
                        cout << "Enter a element you want to insert as " << ith << "th element in the List: ";
                        cin >> element;
                        L.Insert(ith, element);
                        cout << L;
                    } else {}
                } else if (action == 2) {
                    cout << "0 = Go back; 1 = DeleteFront; 2 = DeleteBack; 3 = Delete ith element; Enter the number: ";
                    int function = 0;
                    cin >> function;
                    if (function == 1) {                            // Test function DeleteFront
                        L.DeleteFront();
                        cout << L;
                    } else if (function == 2) {                     // Test function DeleteBack
                        L.DeleteBack();
                        cout << L;
                    } else if (function == 3) {                     // Test function Delete
                        cout << "Enter i to delete ith element in the List: ";
                        cin >> ith;
                        L.Delete(ith);
                        cout << L;
                    } else {}
                } else if (action == 3) {                           // Test function Concatenate
                    List<float> L2;
                    cout << "Enter a List that you want to concat at the back of the first List\n";
                    cout << "How many elements are in the List: ";
                    cin >> times;
                    cout << "Enter the List: ";
                    for (int i = 0; i < times; i++) {
                        cin >> element;
                        L2.InsertBack(element);
                    }
                    cout << "The second List: " << L2;
                    L.Concatenate(L2);
                    cout << "The List after concat the second List: " << L;
                } else if (action == 4) {
                    L.Reverse();
                    cout << "The reversed List: " << L;
                } else {                                            // Exit
                    return 0;
                }
            }
        } else if (type == 3) {                                     // Test character type
            List<char> L;
            char element;
            int times = 0;
            cout << "How many elements are in the List: ";
            cin >> times;
            cout << "Enter the List: ";
            for (int i = 0; i < times; i++) {
                cin >> element;
                L.InsertBack(element);
            }
            cout << L;                                              // Test overload <<, iterator, Begin, End
            cout << "The first element: " << L.Front() << endl;     // Test function Front
            cout << "The last element: " << L.Back() << endl;       // Test function Back
            cout << "Enter i to get the ith element in the List: "; // Test function Get
            int ith;
            cin >> ith;
            cout << "The " << ith << "th element in the List: " << L.Get(ith) << endl;
            while (1) {
                cout << "0 = Exit; 1 = Add a element; 2 = Delete a element; 3 = Concat a List; 4 = Reverse the List; ";
                cout << "Enter the number: ";
                int action = 0;
                cin >> action;
                if (action == 1) {
                    cout << "0 = Go back; 1 = InsertFront; 2 = InsertBack; 3 = Insert at a position; Enter the number: ";
                    int function = 0;
                    cin >> function;
                    if (function == 1) {                            // Test function InsertFront
                        cout << "Enter a element you want to insert at the front of the List: ";
                        cin >> element;
                        L.InsertFront(element);
                        cout << L;
                    } else if (function == 2) {                     // Test function InsertBack
                        cout << "Enter a element you want to insert at the back of the List: ";
                        cin >> element;
                        L.InsertBack(element);
                        cout << L;
                    } else if (function == 3) {                     // Test function Insert
                        cout << "Enter i to insert a new element as ith element in the List: ";
                        cin >> ith;
                        cout << "Enter a element you want to insert as " << ith << "th element in the List: ";
                        cin >> element;
                        L.Insert(ith, element);
                        cout << L;
                    } else {}
                } else if (action == 2) {
                    cout << "0 = Go back; 1 = DeleteFront; 2 = DeleteBack; 3 = Delete ith element; Enter the number: ";
                    int function = 0;
                    cin >> function;
                    if (function == 1) {                            // Test function DeleteFront
                        L.DeleteFront();
                        cout << L;
                    } else if (function == 2) {                     // Test function DeleteBack
                        L.DeleteBack();
                        cout << L;
                    } else if (function == 3) {                     // Test function Delete
                        cout << "Enter i to delete ith element in the List: ";
                        cin >> ith;
                        L.Delete(ith);
                        cout << L;
                    } else {}
                } else if (action == 3) {                           // Test function Concatenate
                    List<char> L2;
                    cout << "Enter a List that you want to concat at the back of the first List\n";
                    cout << "How many elements are in the List: ";
                    cin >> times;
                    cout << "Enter the List: ";
                    for (int i = 0; i < times; i++) {
                        cin >> element;
                        L2.InsertBack(element);
                    }
                    cout << "The second List: " << L2;
                    L.Concatenate(L2);
                    cout << "The List after concat the second List: " << L;
                } else if (action == 4) {
                    L.Reverse();
                    cout << "The reversed List: " << L;
                } else {                                            // Exit
                    return 0;
                }
            }
        } else {                                                    // Exit
            return 0;
        }
    } catch (exception& errow) {
        cout << errow.what() << endl;
    }
    return 0;
}

// Destructor for List that deletes all nodes in the List.
template <class T>
List<T>::~List() {
    for (Node<T>* ptr = first; ptr != NULL; ptr = first) {
        first = first -> link;
        delete ptr;
    }
}

// Return the number of nodes in the List.
template <class T>
int List<T>::Size() {
    int numOfNodes = 0;
    for (Node<T>* ptr = first; ptr != NULL; ptr = ptr -> link) numOfNodes++;
    return numOfNodes;
}

// Function to insert a new element at the front of the List.
template <class T>
void List<T>::InsertFront(const T& e) {
    Node<T>* newNode = new Node<T>(e, first);
    first = newNode;
}

// Function to insert a new element at the back of the List.
template <class T>
void List<T>::InsertBack(const T& e) {
    if (!first) {
        first = new Node<T>(e, NULL);
        return;
    }
    Node<T>* ptr = first;
    for (; ptr -> link != NULL; ptr = ptr -> link);
    Node<T>* newNode = new Node<T>(e, NULL);
    ptr -> link = newNode;
}

// Function to insert a new element as ith element in the List.
template <class T>
void List<T>::Insert(int i, T e) {
    if (i <= 0 || i > Size() + 1) throw invalid_argument("No such index!");
    if (i == 1) {
        Node<T>* newNode = new Node<T>(e, first);
        first = newNode;
        return;
    }
    Node<T>* ptr = first;
    for (int j = 0; j < i - 2; j++) ptr = ptr -> link;
    Node<T>* newNode = new Node<T>(e, ptr -> link);
    ptr -> link = newNode;
}


// Function to delete the first node of the List.
template <class T>
void List<T>::DeleteFront() {
    if (!first) throw invalid_argument("Empty list cannot be deleted!");
    Node<T>* toDelete = first;
    first = first -> link;
    delete toDelete;
}

// Function to delete the last node of the List.
template <class T>
void List<T>::DeleteBack() {
    if (!first) throw invalid_argument("Empty list cannot be deleted!");
    Node<T>* ptr = first;
    for (; ptr -> link -> link != NULL; ptr = ptr -> link);
    delete ptr -> link;
    ptr -> link = NULL;
}

// Function to delete the ith element in the List.
template <class T>
void List<T>::Delete(int i) {
    if (!first) throw invalid_argument("Empty list cannot be deleted!");
    if (i <= 0 || i > Size()) throw invalid_argument("No such element!");
    if (Size() == 1) {
        delete first;
        first = NULL;
        return;
    }
    if (i == 1) {
        Node<T>* toDelete = first;
        first = first -> link;
        delete toDelete;
        return;
    }
    Node<T>* ptr = first;
    for (int j = 0; j < i - 2; j++) ptr = ptr -> link;
    Node<T>* toDelete = ptr -> link;
    ptr -> link = toDelete -> link;
    delete toDelete;
}

// Function to retrun the first element of the List.
template <class T>
T& List<T>::Front() {
    if (!first) throw invalid_argument("The list is empty!");
    return first -> data;
}

// Function to retrun the last element of the List.
template <class T>
T& List<T>::Back() {
    if (!first) throw invalid_argument("The list is empty!");
    Node<T>* ptr = first;
    for (; ptr -> link != NULL; ptr = ptr -> link);
    return ptr -> data;
}

// Function to return the ith element in the List.
template <class T>
T& List<T>::Get(int i) {
    if (!first) throw invalid_argument("The list is empty!");
    if (i <= 0 || i > Size()) throw invalid_argument("No such element!");
    Node<T>* ptr = first;
    for (int j = 0; j < i - 1; j++) ptr = ptr -> link;
    return ptr -> data;
}

// Function to concat two List.
template <class T>
void List<T>::Concatenate(List<T> &b) {
    if (!first) {
        first = b.first;
        return;
    }
    Node<T>* ptr = first;
    for (; ptr -> link != NULL; ptr = ptr -> link);
    ptr -> link = b.first;
    b.first = NULL;
}

// Function to reverse the List.
template <class T>
void List<T>::Reverse() {
    Node<T>* previous = NULL,
            * current = first,
            * next = first -> link;
    while (next != NULL) {
        current -> link = previous;
        previous = current;
        current = next;
        next = next -> link;
    }
    current -> link = previous;
    first = current;
}
