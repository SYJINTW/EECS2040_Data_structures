#include <iostream>
#include "math.h"

using namespace::std;

class Polynomial;

class Node {
    friend Polynomial;
    friend ostream& operator <<(ostream& os, Polynomial& x);
    friend istream& operator >>(istream& is, Polynomial& x);
private:
    double coef;
    int exp;
    Node* link;
public:
    Node(double c = 0, int e = 0, Node* next = NULL): coef{c}, exp{e}, link{next} {}
    void Set(double c, int e) {
        coef = c;
        exp = e;
    }
};

class Polynomial {
private:
    Node* head;
    static Node* av;
public:
    Polynomial() {
        head = GetNode();
        head -> exp = -1;
        head -> link = head;
    }
    ~Polynomial();
    Polynomial(const Polynomial& a);
    Node* GetNode();
    void RetNode(Node*& x);
    void InsertBack(Node& x);
    friend istream& operator >>(istream& is, Polynomial& x);
    friend ostream& operator <<(ostream& os, Polynomial& x);
    Polynomial& operator =(const Polynomial& a);
    void* operator new(size_t size, Polynomial& x) {
        void* ptr = x.GetNode();
        return ptr;
    }
    Polynomial operator +(const Polynomial& b) const;
    Polynomial operator -(const Polynomial& b) const;
    Polynomial operator *(const Polynomial& b) const;
    double Evaluate(double x) const;
};

Node* Polynomial::av = NULL;

int main() {
    Polynomial P1, P2;
    cout << "Enter two polynomial: \n";
    cin >> P1 >> P2;
    cout << "P1 = " << P1 << "P2 = " << P2;
    Polynomial P3(P1);
    Polynomial P4 = P2;
    cout << "The copy of P1 by using copy constructor: " << P3;
    cout << "The copy of P2 by using overload operator '=': " << P4;
    P3 = P1 + P2;
    cout << "P1 + P2 = " << P3;
    P3 = P1 - P2;
    cout << "P1 - P2 = " << P3;
    P3 = P1 * P2;
    cout << "P1 x P2 = " << P3;
    cout << "Enter a number to evaluate P1: ";
    double num, value;
    cin >> num;
    value = P1.Evaluate(num);
    cout << "P1(" << num << ") = " << value << endl;
    return 0;
}

// Desctructor to return all nodes to available-space list
Polynomial::~Polynomial() {
    if (head -> link) {
        Node* ptr = head -> link;
        for (; ptr -> link != head; ptr = ptr -> link);
        ptr -> link = av;
        av = head -> link;
        head -> link = NULL;
    }
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& a) {
    head = new Node;
    head -> exp = -1;
    Node* ptr = head -> link = new Node;
    for (Node* aptr = a.head -> link; aptr != a.head; aptr = aptr -> link) {
        ptr -> coef = aptr -> coef;
        ptr -> exp = aptr -> exp;
        if (aptr -> link == a.head) ptr -> link = head;
        else ptr = ptr -> link = new Node;
    }
}

// Provide a node for use
Node* Polynomial::GetNode() {
    Node* x;
    if (av) {
        x = av;
        av = av -> link;
        return x;
    }
    x = new Node;
    return x;
}

// Free the node pointed to by x
void Polynomial::RetNode(Node*& x) {
    x -> link = av;
    av = x;
    x = NULL;
}

// Insert a node at the back of Polynomial
void Polynomial::InsertBack(Node &x) {
    Node* ptr = head -> link;
    for (; ptr -> link != head; ptr = ptr -> link);
    Node* newNode = new Node(x.coef, x.exp);
    newNode -> link = head;
    ptr -> link = newNode;
}

// Read in an input polynomial and convert it to its circular list representation using a header node.
istream& operator >>(istream& is, Polynomial& x) {
    int num = 0;
    cin >> num;
    Node* ptr = x.head -> link = new Node;
    for (int i = 0; i < num; i++) {
        is >> ptr -> coef;
        is >> ptr -> exp;
        if (i == num - 1) ptr -> link = x.head;
        else ptr = ptr -> link = new Node;
    }
    return is;
}

// Convert x from its linked list representation to its external representation and output it.
ostream& operator <<(ostream& os, Polynomial& x) {
    if (x.head -> link == x.head) return os << "0\n";
    for (Node* ptr = x.head -> link; ptr != x.head; ptr = ptr -> link)
        os << ptr -> coef << ", " << ptr -> exp << ", ";
    return os << endl;
}

// Assign polynomial a to *this.
Polynomial& Polynomial::operator =(const Polynomial& a) {
    Node* ptr = head -> link;
    if (ptr == head) ptr = ptr -> link = new Node;
    for (Node* aptr = a.head -> link; aptr != a.head; aptr = aptr -> link) {
        ptr -> coef = aptr -> coef;
        ptr -> exp = aptr -> exp;
        if (aptr -> link == a.head) {
            if (ptr -> link != head && ptr -> link != NULL) {
                Node* last = ptr -> link;
                for (;last -> link != head; last = last -> link);
                last -> link = av;
                av = ptr -> link;
            }
            ptr -> link = head;
        }
        else if (ptr -> link == head || ptr -> link == NULL) ptr = ptr -> link = new Node;
        else ptr = ptr -> link;
    }
    return *this;
}

// Create and return the polynomial *this + b
Polynomial Polynomial::operator +(const Polynomial& b) const {
    Node* ptr = head -> link, * bptr = b.head -> link;
    Polynomial result;
    Node temp;
    while (1) {
        if (ptr -> exp == bptr -> exp) {
            if (ptr -> exp == -1) return result;
            float sum = ptr -> coef + bptr -> coef;
            temp.Set(sum, ptr -> exp);
            if (sum) result.InsertBack(temp);
            ptr = ptr -> link;
            bptr = bptr -> link;
        } else if (ptr -> exp > bptr -> exp) {
            temp.Set(ptr -> coef, ptr -> exp);
            result.InsertBack(temp);
            ptr = ptr -> link;
        } else {
            temp.Set(bptr -> coef, bptr -> exp);
            result.InsertBack(temp);
            bptr = bptr -> link;
        }
    }
}

// Create and return the polynomial *this - b
Polynomial Polynomial::operator-(const Polynomial &b) const{
    Node* ptr = head -> link, * bptr = b.head -> link;
    Polynomial result;
    Node temp;
    while (1) {
        if (ptr -> exp == bptr -> exp) {
            if (ptr -> exp == -1) return result;
            float sum = ptr -> coef - bptr -> coef;
            temp.Set(sum, ptr -> exp);
            if (sum) result.InsertBack(temp);
            ptr = ptr -> link;
            bptr = bptr -> link;
        } else if (ptr -> exp > bptr -> exp) {
            temp.Set(ptr -> coef, ptr -> exp);
            result.InsertBack(temp);
            ptr = ptr -> link;
        } else {
            temp.Set(-(bptr -> coef), bptr -> exp);
            result.InsertBack(temp);
            bptr = bptr -> link;
        }
    }
}

// Create and return the polynomial *this * b
Polynomial Polynomial::operator*(const Polynomial &b) const {
    Polynomial result;
    Node* ptr = head -> link;
    Node* bptr = b.head -> link;
    while (ptr != head) {
        Polynomial temp;
        while (bptr != b.head) {
            Node newNode(ptr -> coef * bptr -> coef, ptr -> exp + bptr -> exp);
            temp.InsertBack(newNode);
            bptr = bptr -> link;
        }
        result = (result + temp);
        ptr = ptr -> link;
        bptr = bptr -> link;
    }
    return result;
}

// Evaluate the polynomial *this and return the result.
double Polynomial::Evaluate(double x) const {
    double evaluate = 0;
    Node* ptr = head -> link;
    while (ptr != head) {
        evaluate += ptr -> coef * pow(x, ptr -> exp);
        ptr = ptr -> link;
    }
    return evaluate;
}
