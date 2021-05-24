#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>

using namespace std;

// (a)	Write the C++ function, operator+(const Matrix& b) const, which returns the matrix *this + b.
// (b)	Write the C++ function, operator*(const Matrix& b) const, which returns the matrix *this * b.
// (c)	Write the C++ function, operator<<(), which outputs a sparse matrix as triples (i, j, aij).
// (d)	Write the C++ function, Transpose(), which transpose a sparse matrix.
// (e)	Write and test a copy constructor for sparse matrices. What is the computing time of your copy constructor?

struct Triple
{
    int row, col, value;
};

class Matrix; // 前向宣告

class MatrixNode
{
public:
    friend class Matrix;
    friend istream &operator>>(istream &, Matrix &);
    friend ostream &operator<<(ostream &, Matrix &);
    // DONE:
    MatrixNode(bool b, Triple *t);

private:
    MatrixNode *down, *right;
    bool head;
    union
    {
        MatrixNode *next;
        Triple triple;
    };
};

class Matrix
{
public:
    // DONE:
    friend istream &operator>>(istream &, Matrix &);
    // DONE:
    friend ostream &operator<<(ostream &, Matrix &);
    // DONE:
    Matrix() { headnode = NULL; }
    // DONE:
    Matrix(const Matrix &);
    // DONE:
    ~Matrix();
    // DONE:
    Matrix operator+(const Matrix &) const;
    // DONE:
    Matrix operator*(const Matrix &) const;
    // DONE:
    Matrix operator=(const Matrix &);
    // DONE:
    Matrix Transpose();
    // DONE:
    void addNode(Triple t);

private:
    MatrixNode *headnode;
    static MatrixNode *av;
};

MatrixNode *Matrix::av = NULL;

// DONE: MatrixNode constructor
MatrixNode::MatrixNode(bool b, Triple *t)
{
    head = b;
    if (b)
        right = down = this;
    else
        triple = *t; // triple(row,col,value)
}

// DONE: contructor
Matrix::Matrix(const Matrix &m)
{
    MatrixNode *ahead = m.headnode->right;
    MatrixNode *aptr = ahead->right;
    while (aptr == ahead)
    {
        ahead = ahead->next;
        aptr = ahead->right;
    }
    Triple s;
    s.row = m.headnode->triple.row;
    s.col = m.headnode->triple.col;
    s.value = m.headnode->triple.value;
    int p = max(s.row, s.col);
    headnode = new MatrixNode(false, &s);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    headnode->right = head[0];
    int currentRow = 0;
    MatrixNode *last = head[0];
    for (int i = 0; i < s.value; i++)
    {
        Triple t;
        t.row = aptr->triple.row;
        t.col = aptr->triple.col;
        t.value = aptr->triple.value;
        aptr = aptr->right;
        while (aptr == ahead)
        {
            ahead = ahead->next;
            aptr = ahead->right;
        }
        if (t.row > currentRow)
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last->right = new MatrixNode(false, &t);
        last = last->right;
        if (head[t.col]->down == head[t.col])
        {
            head[t.col]->next = last;
            head[t.col]->down = last;
        }
        else
        {
            head[t.col]->next->down = last;
            head[t.col]->next = last;
        }
    }
    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        if (head[i]->down != head[i])
            head[i]->next->down = head[i];
    }
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = headnode;
    delete[] head;
}

// DONE:
void Matrix::addNode(Triple t)
{
    MatrixNode *ptr = new MatrixNode(false, &t);
    MatrixNode *now = NULL;
    MatrixNode *Rnow = headnode->right;
    MatrixNode *Cnow = headnode->right;
    // find col headnode
    for (int i = 0; i < t.col; i++)
    {
        Cnow = Cnow->next;
    }
    now = Cnow;
    while (now->down != Cnow && t.col < now->down->triple.col)
    {
        now = now->down;
    }
    ptr->down = now->down;
    now->down = ptr;
    // find row headnode
    for (int i = 0; i < t.col; i++)
    {
        Rnow = Rnow->next;
    }
    now = Rnow;
    while (now->right != Rnow && t.row < now->right->triple.row)
    {
        now = now->right;
    }
    ptr->right = now->right;
    now->right = ptr;
}

// DONE: Reading in a sparse matrix and set up its link representation
istream& operator >>(istream& is, Matrix& matrix) {
    Triple s; // num of row / num of col / num of terms
    cout << "Numbers of rows: ";
    is >> s.row;
    cout << "Numbers of cols: ";
    is >> s.col;
    cout << "Numbers of terms: ";
    is >> s.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0) {
        matrix.headnode -> right = matrix.headnode;
        return is;
    }
    MatrixNode** head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) head[i] = new MatrixNode(true, 0);
    matrix.headnode -> right = head[0];
    int currentRow = 0;
    MatrixNode* last = head[0];
    for (int i = 0; i < s.value; i++) {
        Triple t;
        cout << "Input the " << i+1 << "th terms ( row, col, value ): ";
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) {
            last -> right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last -> right = new MatrixNode(false, &t);
        last = last -> right;
        if (head[t.col] -> down == head[t.col]) {
            head[t.col] -> next = last;
            head[t.col] -> down = last;
        } else {
            head[t.col] -> next -> down = last;
            head[t.col] -> next = last;
        }
    }
    last -> right = head[currentRow];
    for (int i = 0; i < s.col; i++) {
        if (head[i] -> down != head[i]) head[i] -> next -> down = head[i];
    }
    for (int i = 0; i < p - 1; i++) head[i] -> next = head[i + 1];
    head[p - 1] -> next = matrix.headnode;
    delete [] head;
    return is;
}


// DONE:
ostream &operator<<(ostream &os, Matrix &matrix)
{
    MatrixNode *head = matrix.headnode->right;
    MatrixNode *ptr = head->right;
    while (head != matrix.headnode)
    {
        while (ptr != head)
        {
            os << "(" << ptr->triple.row << ", " << ptr->triple.col << ", " << ptr->triple.value << ") ";
            ptr = ptr->right;
        }
        head = head->next;
        ptr = head->right;
    }
    return os << endl;
}

// DONE: Return matrix *this + b
Matrix Matrix::operator+(const Matrix &b) const
{
    if (headnode->triple.row != b.headnode->triple.row || headnode->triple.col != b.headnode->triple.col)
    {
        throw invalid_argument("Two matrix must be the same size!");
    }
    MatrixNode *ahead = headnode->right;
    MatrixNode *aptr = ahead->right;
    if (aptr == ahead)
    {
        ahead = ahead->next;
        aptr = ahead->right;
    }
    MatrixNode *bhead = b.headnode->right;
    MatrixNode *bptr = bhead->right;
    if (bptr == bhead)
    {
        bhead = bhead->next;
        bptr = bhead->right;
    }
    Matrix matrix;
    Triple s;
    s.row = headnode->triple.row;
    s.col = headnode->triple.col;
    s.value = headnode->triple.value + b.headnode->triple.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    matrix.headnode->right = head[0];
    int currentRow = 0;
    MatrixNode *last = head[0];
    for (int i = 0; i < s.value; i++)
    {
        Triple t;
        if (aptr->triple.row == bptr->triple.row)
        {
            if (aptr->triple.col == bptr->triple.col)
            {
                matrix.headnode->triple.value -= 1;
                s.value -= 1;
                t.row = aptr->triple.row;
                t.col = aptr->triple.col;
                t.value = aptr->triple.value + bptr->triple.value;
                aptr = aptr->right;
                while (aptr == ahead)
                {
                    ahead = ahead->next;
                    aptr = ahead->right;
                }
                bptr = bptr->right;
                while (bptr == bhead)
                {
                    bhead = bhead->next;
                    bptr = bhead->right;
                }
            }
            else if (aptr->triple.col < bptr->triple.col)
            {
                t.row = aptr->triple.row;
                t.col = aptr->triple.col;
                t.value = aptr->triple.value;
                aptr = aptr->right;
                while (aptr == ahead)
                {
                    ahead = ahead->next;
                    aptr = ahead->right;
                }
            }
            else
            {
                t.row = bptr->triple.row;
                t.col = bptr->triple.col;
                t.value = bptr->triple.value;
                bptr = bptr->right;
                while (bptr == bhead)
                {
                    bhead = bhead->next;
                    bptr = bhead->right;
                }
            }
        }
        else if (aptr->triple.row < bptr->triple.row)
        {
            t.row = aptr->triple.row;
            t.col = aptr->triple.col;
            t.value = aptr->triple.value;
            aptr = aptr->right;
            while (aptr == ahead)
            {
                ahead = ahead->next;
                aptr = ahead->right;
            }
        }
        else
        {
            t.row = bptr->triple.row;
            t.col = bptr->triple.col;
            t.value = bptr->triple.value;
            bptr = bptr->right;
            while (bptr == bhead)
            {
                bhead = bhead->next;
                bptr = bhead->right;
            }
        }
        if (t.row > currentRow)
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last->right = new MatrixNode(false, &t);
        last = last->right;
        if (head[t.col]->down == head[t.col])
        {
            head[t.col]->next = last;
            head[t.col]->down = last;
        }
        else
        {
            head[t.col]->next->down = last;
            head[t.col]->next = last;
        }
    }
    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        if (head[i]->down != head[i])
            head[i]->next->down = head[i];
    }
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    delete[] head;
    return matrix;
}

// DONE:
Matrix
Matrix::operator=(const Matrix &m)
{
    if (headnode)
    {
        MatrixNode *x = headnode->right;
        headnode->right = av;
        av = headnode;
        while (x != headnode)
        {
            MatrixNode *y = x->right;
            x->right = av;
            av = y;
            x = x->next;
        }
        headnode = 0;
    }
    MatrixNode *ahead = m.headnode->right;
    MatrixNode *aptr = ahead->right;
    while (aptr == ahead)
    {
        ahead = ahead->next;
        aptr = ahead->right;
    }
    Triple s;
    s.row = m.headnode->triple.row;
    s.col = m.headnode->triple.col;
    s.value = m.headnode->triple.value;
    int p = max(s.row, s.col);
    headnode = new MatrixNode(false, &s);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    headnode->right = head[0];
    int currentRow = 0;
    MatrixNode *last = head[0];
    for (int i = 0; i < s.value; i++)
    {
        Triple t;
        t.row = aptr->triple.row;
        t.col = aptr->triple.col;
        t.value = aptr->triple.value;
        aptr = aptr->right;
        while (aptr == ahead)
        {
            ahead = ahead->next;
            aptr = ahead->right;
        }
        if (t.row > currentRow)
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last->right = new MatrixNode(false, &t);
        last = last->right;
        if (head[t.col]->down == head[t.col])
        {
            head[t.col]->next = last;
            head[t.col]->down = last;
        }
        else
        {
            head[t.col]->next->down = last;
            head[t.col]->next = last;
        }
    }
    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        if (head[i]->down != head[i])
            head[i]->next->down = head[i];
    }
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = headnode;
    delete[] head;
    return *this;
}

// DONE: Return matrix *this * b
Matrix
Matrix::operator*(const Matrix &b) const
{
    if (headnode->triple.col != b.headnode->triple.row)
        throw invalid_argument("Incompatible matrixs!");
    Matrix matrix;
    MatrixNode *ahead = headnode->right;
    MatrixNode *aptr = ahead->right;
    while (aptr == ahead)
    {
        ahead = ahead->next;
        aptr = ahead->right;
    }
    MatrixNode *bhead = b.headnode->right;
    MatrixNode *bptr = bhead->down;
    while (bptr == bhead)
    {
        bhead = bhead->next;
        bptr = bhead->down;
    }
    Triple s;
    s.row = headnode->triple.row;
    s.col = b.headnode->triple.col;
    s.value = 0;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    matrix.headnode->right = head[0];
    int currentRow = 0;
    MatrixNode *last = head[0];
    while (ahead != headnode)
    {
        while (bhead != b.headnode)
        {
            double sum = 0;
            while (bptr != bhead)
            {
                if (aptr->triple.col == bptr->triple.row)
                {
                    sum += aptr->triple.value * bptr->triple.value;
                    aptr = aptr->right;
                    bptr = bptr->down;
                }
                else if (aptr->triple.col < bptr->triple.row)
                    aptr = aptr->right;
                else
                    bptr = bptr->down;
                if (aptr == ahead)
                    bptr = bhead;
            }
            aptr = ahead->right;
            bptr = bhead->down;
            if (sum)
            {
                matrix.headnode->triple.value += 1;
                Triple t;
                t.row = aptr->triple.row;
                t.col = bptr->triple.col;
                t.value = sum;
                if (t.row > currentRow)
                {
                    last->right = head[currentRow];
                    currentRow = t.row;
                    last = head[currentRow];
                }
                last->right = new MatrixNode(false, &t);
                last = last->right;
                if (head[t.col]->down == head[t.col])
                {
                    head[t.col]->next = last;
                    head[t.col]->down = last;
                }
                else
                {
                    head[t.col]->next->down = last;
                    head[t.col]->next = last;
                }
            }
            bhead = bhead->next;
            bptr = bhead->down;
            while (bptr == bhead)
            {
                bhead = bhead->next;
                bptr = bhead->down;
            }
        }
        ahead = ahead->next;
        aptr = ahead->right;
        while (aptr == ahead)
        {
            ahead = ahead->next;
            aptr = ahead->right;
        }
        bhead = b.headnode->right;
        bptr = bhead->down;
        while (bptr == bhead)
        {
            bhead = bhead->next;
            bptr = bhead->down;
        }
    }
    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        if (head[i]->down != head[i])
            head[i]->next->down = head[i];
    }
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    delete[] head;
    return matrix;
}

// DONE: Transpose a matrix
Matrix Matrix::Transpose()
{
    Matrix matrix;
    MatrixNode *ahead = headnode->right;
    MatrixNode *aptr = ahead->down;
    while (aptr == ahead)
    {
        ahead = ahead->next;
        aptr = ahead->down;
    }
    Triple s;
    s.row = headnode->triple.col;
    s.col = headnode->triple.row;
    s.value = headnode->triple.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    matrix.headnode->right = head[0];
    int currentRow = 0;
    MatrixNode *last = head[0];
    for (int i = 0; i < s.value; i++)
    {
        Triple t;
        t.row = aptr->triple.col;
        t.col = aptr->triple.row;
        t.value = aptr->triple.value;
        if (t.row > currentRow)
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        last->right = new MatrixNode(false, &t);
        last = last->right;
        if (head[t.col]->down == head[t.col])
        {
            head[t.col]->next = last;
            head[t.col]->down = last;
        }
        else
        {
            head[t.col]->next->down = last;
            head[t.col]->next = last;
        }
        aptr = aptr->down;
        while (aptr == ahead)
        {
            ahead = ahead->next;
            aptr = ahead->down;
        }
    }
    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        if (head[i]->down != head[i])
            head[i]->next->down = head[i];
    }
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    delete[] head;
    return matrix;
}

// DONE: Desctructor
Matrix::~Matrix()
{
    if (!headnode)
        return;
    MatrixNode *x = headnode->right;
    headnode->right = av;
    av = headnode;
    while (x != headnode)
    {
        MatrixNode *y = x->right;
        x->right = av;
        av = y;
        x = x->next;
    }
    headnode = 0;
}

#endif // FUNCTION_HPP
