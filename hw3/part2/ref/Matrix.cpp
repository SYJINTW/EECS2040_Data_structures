#include <iostream>

using namespace::std;

struct Triple {
    int row, col, value;
};

class Matrix;

class MatrixNode {
    friend class Matrix;
    friend istream& operator >>(istream&, Matrix&);
    friend ostream& operator <<(ostream&, Matrix&);
private:
    MatrixNode* down, * right;
    bool head;
    union {
        MatrixNode* next;
        Triple triple;
    };
public:
    MatrixNode(bool b, Triple* t) {
        head = b;
        if (b) { right = down = this; }
        else triple = *t;
    }
};

class Matrix {
    friend istream& operator >>(istream&, Matrix&);
    friend ostream& operator <<(ostream&, Matrix&);
private:
    MatrixNode* headnode;
    static MatrixNode* av;
public:
    Matrix() {}
    Matrix(const Matrix&);
    ~Matrix();
    Matrix operator +(const Matrix&) const;
    Matrix operator *(const Matrix&) const;
    Matrix operator =(const Matrix& m) {
        headnode = m.headnode;
        return *this;
    }
    Matrix Transpose();
};

MatrixNode* Matrix::av = NULL;

int main() {
    try {
        cout << "Enter a sparse matrix M1:\n";
        Matrix M1;
        cin >> M1;
        cout << "M1 = " << M1;
        while (1) {
            cout << "0: Exit; 1: Addition; 2: Production; 3: Transpose; Choose a function: ";
            int fun = 0;
            cin >> fun;
            if (fun == 1) {
                cout << "Enter a sparse matrix M2 for M1 + M2:\n";
                Matrix M2;
                cin >> M2;
                Matrix M3 = M1 + M2;
                cout << "M2 = " << M2;
                cout << "M1 + M2 = " << M3;
            } else if (fun == 2) {
                cout << "Enter a sparse matrix M2 for M1 x M2:\n";
                Matrix M2;
                cin >> M2;
                Matrix M3 = M1 * M2;
                cout << "M2 = " << M2;
                cout << "M1 x M2 = " << M3;
            } else if (fun == 3) {
                Matrix MT = M1.Transpose();
                cout << "The tranpose of M1 = " << MT;
            } else {
                return 0;
            }
        }
    } catch (exception& errow) {
        cout << errow.what() << endl;
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& m) {
    MatrixNode* ahead = m.headnode -> right;
    MatrixNode* aptr = ahead -> right;
    if (aptr == ahead) {
        ahead = ahead -> next;
        aptr = ahead -> right;
    }
    Triple s;
    s.row = m.headnode -> triple.row;
    s.col = m.headnode -> triple.col;
    s.value = m.headnode -> triple.value;
    int p = max(s.row, s.col);
    headnode = new MatrixNode(false, &s);
    MatrixNode** head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) head[i] = new MatrixNode(true, 0);
    headnode -> right = head[0];
    int currentRow = 0;
    MatrixNode* last = head[0];
    for (int i = 0; i < s.value; i++) {
        Triple t;
        t.row = aptr -> triple.row;
        t.col = aptr -> triple.col;
        t.value = aptr -> triple.value;
        aptr = aptr -> right;
        if (aptr == ahead) {
            ahead = ahead -> next;
            aptr = ahead -> right;
        }
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
    head[p - 1] -> next = headnode;
    delete [] head;
}

// Desctructor, return all nodes to available-space list
Matrix::~Matrix() {
    if (!headnode) return;
    MatrixNode* x = headnode -> right;
    headnode -> right = av;
    av = headnode;
    while (x != headnode) {
        MatrixNode* y = x -> right;
        x -> right = av;
        av = y;
        x = x -> next;
    }
    headnode = 0;
}

// Read in a matrix and set up its linked representation
istream& operator >>(istream& is, Matrix& matrix) {
    Triple s;
    is >> s.row >> s.col >> s.value;
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

// Output the matrix
ostream& operator <<(ostream& out, Matrix& matrix) {
    MatrixNode* head = matrix.headnode -> right;
    MatrixNode* ptr = head -> right;
    while (head != matrix.headnode) {
        while (ptr != head) {
            out << "(" << ptr -> triple.row << ", " << ptr -> triple.col << ", " << ptr -> triple.value << ") ";
            ptr = ptr -> right;
        }
        head = head -> next;
        ptr = head -> right;
    }
    return out << endl;
}

// Return matrix *this + b
Matrix Matrix::operator +(const Matrix &b) const {
    if (headnode -> triple.row != b.headnode -> triple.row || headnode -> triple.col != b.headnode -> triple.col) throw invalid_argument("Two matrix must be the same size!");
    MatrixNode* ahead = headnode -> right;
    MatrixNode* aptr = ahead -> right;
    if (aptr == ahead) {
        ahead = ahead -> next;
        aptr = ahead -> right;
    }
    MatrixNode* bhead = b.headnode -> right;
    MatrixNode* bptr = bhead -> right;
    if (bptr == bhead) {
        bhead = bhead -> next;
        bptr = bhead -> right;
    }
    Matrix matrix;
    Triple s;
    s.row = headnode -> triple.row;
    s.col = headnode -> triple.col;
    s.value = headnode -> triple.value + b.headnode -> triple.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    MatrixNode** head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) head[i] = new MatrixNode(true, 0);
    matrix.headnode -> right = head[0];
    int currentRow = 0;
    MatrixNode* last = head[0];
    for (int i = 0; i < s.value; i++) {
        Triple t;
        if (aptr -> triple.row == bptr -> triple.row) {
            if (aptr -> triple.col == bptr -> triple.col) {
                matrix.headnode -> triple.value -= 1;
                s.value -= 1;
                t.row = aptr -> triple.row;
                t.col = aptr -> triple.col;
                t.value = aptr -> triple.value + bptr -> triple.value;
                aptr = aptr -> right;
                while (aptr == ahead) {
                    ahead = ahead -> next;
                    aptr = ahead -> right;
                }
                bptr = bptr -> right;
                while (bptr == bhead) {
                    bhead = bhead -> next;
                    bptr = bhead -> right;
                }
            } else if (aptr -> triple.col < bptr -> triple.col) {
                t.row = aptr -> triple.row;
                t.col = aptr -> triple.col;
                t.value = aptr -> triple.value;
                aptr = aptr -> right;
                while (aptr == ahead) {
                    ahead = ahead -> next;
                    aptr = ahead -> right;
                }
            } else {
                t.row = bptr -> triple.row;
                t.col = bptr -> triple.col;
                t.value = bptr -> triple.value;
                bptr = bptr -> right;
                while (bptr == bhead) {
                    bhead = bhead -> next;
                    bptr = bhead -> right;
                }
            }
        } else if (aptr -> triple.row < bptr -> triple.row) {
            t.row = aptr -> triple.row;
            t.col = aptr -> triple.col;
            t.value = aptr -> triple.value;
            aptr = aptr -> right;
            while (aptr == ahead) {
                ahead = ahead -> next;
                aptr = ahead -> right;
            }
        } else {
            t.row = bptr -> triple.row;
            t.col = bptr -> triple.col;
            t.value = bptr -> triple.value;
            bptr = bptr -> right;
            while (bptr == bhead) {
                bhead = bhead -> next;
                bptr = bhead -> right;
            }
        }
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
    return matrix;
}

// Return matrix *this * b
Matrix Matrix::operator *(const Matrix &b) const {
    if (headnode -> triple.col != b.headnode -> triple.row) throw invalid_argument("Incompatible matrixs!");
    Matrix matrix;
    MatrixNode* ahead = headnode -> right;
    MatrixNode* aptr = ahead -> right;
    while (aptr == ahead) {
        ahead = ahead -> next;
        aptr = ahead -> right;
    }
    MatrixNode* bhead = b.headnode -> right;
    MatrixNode* bptr = bhead -> down;
    while (bptr == bhead) {
        bhead = bhead -> next;
        bptr = bhead -> down;
    }
    Triple s;
    s.row = headnode -> triple.row;
    s.col = b.headnode -> triple.col;
    s.value = 0;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    MatrixNode** head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) head[i] = new MatrixNode(true, 0);
    matrix.headnode -> right = head[0];
    int currentRow = 0;
    MatrixNode* last = head[0];
    while (ahead != headnode) {
        while (bhead != b.headnode) {
            double sum = 0;
            while (bptr != bhead) {
                if (aptr -> triple.col == bptr -> triple.row) {
                    sum += aptr -> triple.value * bptr -> triple.value;
                    aptr = aptr -> right;
                    bptr = bptr -> down;
                }
                else if (aptr -> triple.col < bptr -> triple.row) aptr = aptr -> right;
                else bptr = bptr -> down;
                if (aptr == ahead) bptr = bhead;
            }
            aptr = ahead -> right;
            bptr = bhead -> down;
            if (sum) {
                matrix.headnode -> triple.value += 1;
                Triple t;
                t.row = aptr -> triple.row;
                t.col = bptr -> triple.col;
                t.value = sum;
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
            bhead = bhead -> next;
            bptr = bhead -> down;
            while (bptr == bhead) {
                bhead = bhead -> next;
                bptr = bhead -> down;
            }
        }
        ahead = ahead -> next;
        aptr = ahead -> right;
        while (aptr == ahead) {
            ahead = ahead -> next;
            aptr = ahead -> right;
        }
        bhead = b.headnode -> right;
        bptr = bhead -> down;
        while (bptr == bhead) {
            bhead = bhead -> next;
            bptr = bhead -> down;
        }
        
    }
    last -> right = head[currentRow];
    for (int i = 0; i < s.col; i++) {
        if (head[i] -> down != head[i]) head[i] -> next -> down = head[i];
    }
    for (int i = 0; i < p - 1; i++) head[i] -> next = head[i + 1];
    head[p - 1] -> next = matrix.headnode;
    delete [] head;
    return matrix;
}

// Transpose a matrix
Matrix Matrix::Transpose() {
    Matrix matrix;
    MatrixNode* ahead = headnode -> right;
    MatrixNode* aptr = ahead -> down;
    if (aptr == ahead) {
        ahead = ahead -> next;
        aptr = ahead -> down;
    }
    Triple s;
    s.row = headnode -> triple.col;
    s.col = headnode -> triple.row;
    s.value = headnode -> triple.value;
    int p = max(s.row, s.col);
    matrix.headnode = new MatrixNode(false, &s);
    MatrixNode** head = new MatrixNode* [p];
    for (int i = 0; i < p; i++) head[i] = new MatrixNode(true, 0);
    matrix.headnode -> right = head[0];
    int currentRow = 0;
    MatrixNode* last = head[0];
    for (int i = 0; i < s.value; i++) {
        Triple t;
        t.row = aptr -> triple.col;
        t.col = aptr -> triple.row;
        t.value = aptr -> triple.value;
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
        aptr = aptr -> down;
        while (aptr == ahead) {
            ahead = ahead -> next;
            aptr = ahead -> down;
        }
    }
    last -> right = head[currentRow];
    for (int i = 0; i < s.col; i++) {
        if (head[i] -> down != head[i]) head[i] -> next -> down = head[i];
    }
    for (int i = 0; i < p - 1; i++) head[i] -> next = head[i + 1];
    head[p - 1] -> next = matrix.headnode;
    delete [] head;
    return matrix;
}
