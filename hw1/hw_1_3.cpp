//(35%) Write a C++ program to implement the ADT2.5 String (pp.114) (with Find function implemented by FastFind).
// In addition, write two more functions: 
// 1. String::Delete(int start, int length); //remove length characters beginning at start
// 2. String::CharDelete(char c); //returns the string with all occurrence of c removed.
// You should try out at least two runs of your program to demonstrate all those functions.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class String
{
    public:
    String();
    String(int m);
    String(char* init, int m);
    int Length();
    void Delete(int start, int length);
    String CharDelete(char c);
    void Print();
    
    private:
    char* charTerm;
    int myLength;
};

String::String()
{
    myLength = 0;
}


String::String(int m)
{
    charTerm = new char[m];
}

String::String(char* init, int m)
{
    charTerm = new char[m];
    for(int i = 0; i < m; i++)
    {
        charTerm[i] = init[i];
    }
    myLength = m;
}

void
String::Delete(int start, int length)
{
    start = start-1;
    int tmyLength = myLength - length;
    String temp(tmyLength);
    int ti = 0;
    for(int i = 0; i < myLength; i++)
    {
        if(i < start || i > start+length-1)
            temp.charTerm[ti++] = charTerm[i];
    }
    delete [] charTerm;
    charTerm = temp.charTerm;
}

String
String::CharDelete(char c)
{
    String temp;
    for(int i = 0; i < myLength; i++)
    {
        if(charTerm[i] != c)
            temp.charTerm[temp.myLength++] = charTerm[i];
    }
    return temp;
}

void
String::Print()
{
    cout << charTerm << endl;
}

int main()
{
    int n, d, l;
    char dc;
    char c[100];
    cin >> n >> c;
    String S(c, n);
    cout << "String: ";
    S.Print();

    cout << "Start delete from?" << endl;
    cin >> d;
    cout << "Delete length?" << endl;
    cin >> l;
    S.Delete(d, l);
    cout << "String: ";
    S.Print();

    cout << "Delete what char?" << endl;
    cin >> dc;
    String K;
    K = S.CharDelete(dc);
    cout << "String: ";
    K.Print();  
}

/*
Input1:
10 abcabcabca
5
3
a

Input2:
20 abcdefghijabcdefghij
1
5
j
*/