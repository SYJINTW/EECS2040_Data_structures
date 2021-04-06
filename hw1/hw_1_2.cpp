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

#include <iostream>
#include <iomanip>

using namespace std;

class SparseMatrix;

class MatrixTerm
{
    friend class SparseMatrix;
    public:
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
    friend istream & operator >> (istream &in, SparseMatrix &M);
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

// BUG:
SparseMatrix
SparseMatrix::Mult(SparseMatrix b)
{
    if (cols!=b.rows) throw "Incompatible matrices";
    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows, b.cols, 0);
    int currRowIndex = 0,
        currRowBegin = 0,
    currRowA = smArray[0].row;
    
    if (terms == capacity) ChangeSize1D(terms+1);
    bXpose.ChangeSize1D(bXpose.terms+1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;
    int sum = 0;
    while (currRowIndex<terms)
    {// 產生d的第currRowA列
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms)
        {//*this的第CurrRowA列乘上b的第currColB行
            if (smArray[currRowIndex].row != currRowA)
            {//currRowA的結尾
                d.StoreSum(sum, currRowA, currColB);
                sum = 0; //重設sum
                currRowIndex = currRowBegin;
                //前進至下一行
                while (bXpose.smArray[currColIndex].row == currColB) 
                    currColIndex++;
                currColB = bXpose.smArray[currColIndex].row;
            }
            else if (bXpose.smArray[currColIndex].row != currColB)
            { // b中第currColB行的結尾
                d.StoreSum(sum, currRowA, currColB);
                sum = 0; // 重設
                // 第currRowA列改成與下一行相乘
                currRowIndex = currRowBegin;
                currColB = bXpose.smArray[currColIndex].row;
            }
            else
                if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col) currRowIndex++;
                else if (smArray[currRowIndex].col ==bXpose.smArray[currColIndex].col)
                { // 加到sum裡
                    sum+=smArray[currRowIndex].value*
                        bXpose.smArray[currColIndex].value;
                    currRowIndex++;
                    currColIndex++;
                }
                else currColIndex++; // currColB的下一項
        } // while (currColIndex<= b.terms)結束
        while(smArray[currRowIndex].row == currRowA) // 前進至下一列
            currRowIndex++;
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    } // while (currRowIndex<terms)結束
    return d;   
}

SparseMatrix
SparseMatrix::FastTranspose()
{
    SparseMatrix b(cols, rows, terms);
    if(terms > 0)
    {
        int *rowSize = new int[cols]; // the numbers of nonzero in the row
        int *rowStart = new int[cols];
        fill(rowSize, rowSize+cols, 0);
        for(int i = 0; i < terms; i++) rowSize[smArray[i].col]++;
        rowStart[0] = 0;
        for(int i = 1; i < cols; i++) rowStart[i] = rowStart[i-1] + rowSize[i-1];
        for(int i = 0; i < terms; i++)
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
    for(int i = 0; i < terms; i++)
    {
        if(smArray[i].row == r && smArray[i].col == c)
            return smArray[i].value;
    }
    return 0;
}

// for output matrix
ostream& operator<<(ostream& os, SparseMatrix& M)
{
    for(int r = 0; r < M.rows; r++)
    {
        for(int c = 0; c < M.cols; c++)
        {
            // print the value
            os << setw(4) << M.search(r,c) << " ";
        }
        os << endl;
    }
    return os;
}

// for input matrix
istream & operator >> (istream &in, SparseMatrix &M)
{
    for(int i = 0; i < M.terms; i++)
    {
        in >> M.smArray[i].row >> M.smArray[i].col >> M.smArray[i].value;
    }
    return in;
}


int main()
{
    int rows, cols, terms;
    cout << "A:" << endl;
    cin >> rows >> cols >> terms;
    SparseMatrix A(rows, cols, terms);
    cin >> A;

    cout << "Matrix A" << endl;
    cout << A << endl;

    cout << "B:" << endl;
    cin >> rows >> cols >> terms;
    SparseMatrix B(rows, cols, terms);
    cin >> B;

    cout << "Matrix B" << endl;
    cout << B << endl;
    
    SparseMatrix C; 
    C = A.Add(B);
    
    cout << "A + B" << endl;
    cout << C << endl;

    /*
    SparseMatrix D; 
    D = A.FastTranspose();
    
    cout << "T(A)" << endl;
    cout << D << endl;
    */

    SparseMatrix E; 
    E = A.Mult(B);

    cout << "A * B" << endl;
    cout << E << endl;
}


/*
Input1:

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


Input2:

3 3 6
0 0 1
0 1 2
0 2 3
2 0 4
2 1 5
2 2 6

3 3 6
0 0 7
0 2 7
1 0 8
1 2 8
2 0 9
2 2 9
*/