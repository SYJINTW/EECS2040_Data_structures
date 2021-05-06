#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>

using namespace std;

// (a)	Write the C++ function, operator+(const Matrix& b) const, which returns the matrix *this + b.
// (b)	Write the C++ function, operator*(const Matrix& b) const, which returns the matrix *this * b.
// (c)	Write the C++ function, operator<<(), which outputs a sparse matrix as triples (i, j, aij). 
// (d)	Write the C++ function, Transpose(), which transpose a sparse matrix.
// (e)	Write and test a copy constructor for sparse matrices. What is the computing time of your copy constructor?


struct Triple{int row, col, value;};

class Matrix; // 前向宣告

class MatrixNode
{
    friend class Matrix;
    friend istream& operator>>(istream&, Matrix&); // 為了能夠讀進矩陣
    private:
        MatrixNode *down , *right;
        bool head;
        union { // 沒有名字的union
            MatrixNode *next;
            Triple triple;
        };
        MatrixNode(bool, Triple*); // constructor
};


// constructor
MatrixNode::MatrixNode(bool b, Triple *t)
{
    head = b;
    if (b) {right = down = this;} // 列/行的標頭節點
    else triple = *t; // 標頭節點串列的元素節點或標頭節點
}

class Matrix
{
    friend istream& operator>>(istream&, Matrix&);
    public:
        //~Matrix(); // 解構子
    private:
        MatrixNode *headnode;
};





// Reading in a sparse matrix and set up its link representation
istream& operator>>(istream& is, Matrix& matrix)
{   
    // Read in a maxtix and set up its linked representation
    Triple s;
    is >> s.row >> s.col >> s.value; // matrix dimensions -> cin >> number of rows >> number of cols >> number of element 
    int p = max(s.row, s.col);


    // set up header node for list of header nodes
    matrix.headnode = new MatrixNode(false, &s); // false means that the node is not headnode
    if (p == 0) // row = 0 && col = 0 => list of header nodes
    {
        matrix.headnode->right = matrix.headnode; 
        return is; // for supporting "cin >> mi >> mj;" => can input continuous
    }

    // at least one row or column
    MatrixNode **head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0); // headnodes save in head[]

    int currentRow = 0;
    MatrixNode *last = head[0]; // last node in current row

    // input triples 
    for (int i = 0; i < s.value; i++) 
    {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) { // end of current row
            last->right = head[currentRow]; // close current row
            currentRow = t.row;
            last = head[currentRow];
        } // end of if

        // link new node into row list
        last->right = new MatrixNode(false, &t); 
        last = last->right;
        
        // link into column list
        head[t.col]->next->down = last; 
        head[t.col]->next = head[t.col]->next->down;
    } // end of for

    last->right = head[currentRow]; // close last row
    for (int i = 0; i < s.col; i++) 
        head[i]->next->down = head[i]; // close all column lists

    // link the header nodes together
    for (int i = 0; i < p; i++) 
        head[i]->next = head[i + 1];
    head[p-1]->next = matrix.headnode;
    matrix.headnode->right = head[0];

    delete [] head;
    return is;
}


/*
// destructor
Matrix::~Matrix()
{   
    // Return all nodes to the av list, which is a chain linked via the right field.
    // av is a static variable pointing to the first of the av list.
    if (!headnode) return; // no nodes to delete

    // have node to delete
    MatrixNode *x = headnode->right;
    headnode->right = av; 
    av = headnode; // return headnode

    while (x != headnode) { // erase nodes by rows
        MatrixNode *y = x->right; 
        x->right = av; 
        av = y;
        x = x->next; // next row
    }
    headnode = 0;
}
*/







#endif // FUNCTION_HPP