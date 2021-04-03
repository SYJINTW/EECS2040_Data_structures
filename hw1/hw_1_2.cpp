// Homework Information
//
// (35%) Write a C++ program to implement the ADT2.4 SparseMatrix in textbook (pp.97) (with Transpose implemented by FastTranspose).
// You should build you program based on the example codes in the book and implement the Add function and functions to input, output a sparse matrix by overloading the >> and << operators. 
// You should try out at least two runs of your program to demonstrate the Add, Mult and input, output functions.
// 1. Add
// 2. Mult
// 3. input
// 4. output
//

/*
6 6 8
0 0 15
0 3 22
0 5 -15
1 1 11
1 2 3
2 3 -6
4 0 91
5 2 28

6 6 8
0 0 15
0 4 91
1 1 11
2 1 3 
2 5 28
3 0 22
3 2 -6
5 0 -15
*/

#include <iostream>
#include <iomanip>

using namespace std;

class SparseMatrix;

class MatrixTerm
{
    friend class SparseMatrix;
    private:
    int row, col, value;
};

class SparseMatrix
{
    public:
    SparseMatrix();
    SparseMatrix(int r, int c);
    SparseMatrix(int r, int c, int t);
    SparseMatrix Add(SparseMatrix b);
    SparseMatrix Mult(SparseMatrix b);
    SparseMatrix FastTranspose();
    void ChangeSize1D(const int newSize);
    void StoreSum(const int sum, const int r, const int c);
    friend ostream& operator<<(ostream& os, SparseMatrix& M);
    int search(int r, int c);
    private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix()
{
    rows = 0;
    cols = 0;
}

SparseMatrix::SparseMatrix(int r, int c)
{
    rows = r;
    cols = c;
}

SparseMatrix::SparseMatrix(int r, int c, int t)
{
    rows = r;
    cols = c;
    terms = t;
    capacity = t;
    smArray = new MatrixTerm[capacity];
    for(int i = 0; i < t; i++)
    {
        cin >> smArray[i].row >> smArray[i].col >> smArray[i].value;
    }
}

SparseMatrix
SparseMatrix::Add(SparseMatrix b)
{
    if(rows == b.rows && cols == b.cols)
    {
        int aPos = 0, bPos = 0, cPos = 0;
        SparseMatrix c(rows, cols);
        c.capacity = terms + b.terms;
        c.smArray = new MatrixTerm[c.capacity];
        while(aPos < terms && bPos < b.terms)
        {
            if(smArray[aPos].row == b.smArray[bPos].row)
            {
                if(smArray[aPos].col == b.smArray[bPos].col)
                {
                    c.smArray[cPos].row = smArray[aPos].row; 
                    c.smArray[cPos].col = smArray[aPos].col; 
                    c.smArray[cPos++].value = smArray[aPos++].value + b.smArray[bPos++].value; 
                }
                else if(smArray[aPos].col < b.smArray[bPos].col)
                {
                   c.smArray[cPos++] = smArray[aPos++]; 
                }
                else
                {
                    c.smArray[cPos++] = b.smArray[bPos++];
                }
            }
            else if(smArray[aPos].row < b.smArray[bPos].row)
            {
                c.smArray[cPos++] = smArray[aPos++];
            }
            else
            {
                c.smArray[cPos++] = b.smArray[bPos++];
            }
        }
        for(; aPos < terms; aPos++)
        {
           c.smArray[cPos++] = smArray[aPos++]; 
        }
        for(; bPos < b.terms; bPos++)
        {
           c.smArray[cPos++] = b.smArray[bPos++]; 
        }
        c.terms = cPos;
        return c;
    }
    else throw "Incompatible matrices";
}

// TODO:
SparseMatrix
SparseMatrix::Mult(SparseMatrix b)
{

}

SparseMatrix
SparseMatrix::FastTranspose()
{
    SparseMatrix b(cols, rows);
    b.terms = terms;
    if(terms > 0)
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
        fill(rowSize, rowSize+cols, 0);
        for(int i = 0; i < terms; i++) rowSize[smArray[i].col]++;
        rowStart[0] = 0;
        for(int i = 1; i < terms; i++)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
        delete [] rowSize;
        delete [] rowStart;
    }
    return b;
}

void
SparseMatrix::ChangeSize1D(const int newSize)
{
    if(newSize < terms) throw "New size must be >= number of terms";
    MatrixTerm *temp = new MatrixTerm[newSize];
    copy(smArray, smArray+terms, temp);
    delete [] smArray;
    smArray = temp;
    capacity = newSize;
}

void
SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
    if(sum != 0)
    {
        if(terms == capacity) ChangeSize1D(2*capacity);
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}


int
SparseMatrix::search(int r, int c)
{
    int result = 0;
    for(int i = 0; i < terms; i++)
    {
        if(smArray[i].row == r && smArray[i].col == c)
            return smArray[i].value;
    }
    return result;
}

ostream& operator<<(ostream& os, SparseMatrix& M)
{
    for(int r = 0; r < M.rows; r++)
    {
        for(int c = 0; c < M.cols; c++)
        {
            os << setw(4) << M.search(r,c) << " ";
        }
        cout << endl;
    }
    return os;
}


int main()
{
    int rows, cols, terms;
    cout << "A:" << endl;
    cin >> rows >> cols >> terms;
    SparseMatrix A(rows, cols, terms);
    cout << A << endl;
    cout << "B:" << endl;
    cin >> rows >> cols >> terms;
    SparseMatrix B(rows, cols, terms);
    cout << B << endl;
    SparseMatrix C; 
    C = A.Add(B);
    cout << C << endl;
}

