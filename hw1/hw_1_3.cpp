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

    String Concat(const String &t);
    String Substr(int i, int j);
    void Delete(int start, int length);
    String CharDelete(char c);
    
    int Length();
    void Print();
    int FastFind(String pat);
    void FailureFunction();
    
    private:
    int myLength;
    char* charTerm;
    int* failureList;
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
    failureList = new int[m];
    FailureFunction();
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
    char temp[myLength];
    int tmpPos = 0;
    for(int i = 0; i < myLength; i++)
    {
        if(charTerm[i] != c)
            temp[tmpPos++] = charTerm[i];
    }
    String result(temp, tmpPos+1); 
    return result;
}

void
String::Print()
{
    cout << "String: " << charTerm << endl;
}

void
String::FailureFunction() {
    int l = Length();
    failureList[0] = -1;
    for (int i = 1; i < l; i++) {
        int j = failureList[i - 1];
        while ((*(charTerm + i) != *(charTerm + j + 1)) && (j >= 0))
            j = failureList[j];
        if (*(charTerm + i) == *(charTerm + j + 1))
            failureList[i] = j + 1;
        else
            failureList[i] = -1;
    }
}

String
String::Substr(int i, int j) {
    if (i + j >= Length()) throw invalid_argument("Out of string!!");
    char *init = new char[j];
    for (int k = 0; k < j; k++, i++)
        init[k] = charTerm[i - 1];
    String substr(init, j);
    return substr;
}

int String::FastFind(String pat) {
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    while ((posP < lengthP) && (posS < lengthS)) {
        if (pat.charTerm[posP] == charTerm[posS]) {
            posP++;
            posS++;
        } else if (posP == 0) posS++;
        else posP = pat.failureList[posP - 1] + 1;
    }
    if (posP < lengthP) return -1;
    return posS - lengthP;
}

int main()
{
    int n, d, l;
    char dc;
    char c[100];
    cout << "How many char are in the string: ";
    cin >> n;
    cout << "Input " << n << " char: ";
    cin >> c;
    String S(c, n);
    S.Print();

    cout << "Start delete from: ";
    cin >> d;
    cout << "Delete length: ";
    cin >> l;
    S.Delete(d, l);
    S.Print();

    cout << "Delete which char: ";
    cin >> dc;
    String K;
    K = S.CharDelete(dc);
    K.Print();  
}

int
String::Length()
{
    return myLength;
}

/*
Input1:
10
abcabcabca
5
3
a

Input2:
20
abcdefghijabcdefghij
1
5
j
*/