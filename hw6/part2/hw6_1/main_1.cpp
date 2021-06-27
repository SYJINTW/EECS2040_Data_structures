
// DONE: insertion sort
// DONE: median-of-three quick sort
// DONE: iterative merge sort
// DONE: recursive merge sort
// DONE: heap sort

#include <iostream>
#include <iomanip>
#include <string>

#define ARRAYSIZE 50

using namespace std;

int s = 20;
char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                        'h', 'i', 'j', 'k', 'l', 'm', 'n',
                        'o', 'p', 'q', 'r', 's', 't', 'u',
                        'v', 'w', 'x', 'y', 'z' };


// insertion sort

template <class T>
void Insert(const T& e, T *a, int i)
{
    a[0] = e;
    while(e < a[i])
    {
        a[i+1] = a[i];
        i--;
    }
    a[i+1] = e;
}

template <class T>
void InsertionSort(T *a, const int n)
{
    for(int j = 2; j <= n; j++)
    {
        T temp = a[j];
        Insert(temp, a, j-1);
    }
}

// median-of-three quick sort
template <class T>
void QuickSort(T *a, const int left, const int right)
{
    if(left < right)
    {
        int i = left, j = right + 1;
        T pivot = a[left];
        do
        {
            do i++; while(a[i] < pivot);
            do j--; while(a[j] > pivot);
            if(i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[left], a[j]);
        QuickSort(a, left, j-1);
        QuickSort(a, j+1, right);
    }
}

// merge sort

template <class T>
void Merge(T *initList, T *mergedList, const int l, const int m, const int n)
{
    int i1, iResult, i2;
    for(i1 = l, iResult = l, i2 = m+1; i1 <= m && i2 <= n; iResult++)
    {
        if(initList[i1] <= initList[i2])
        {
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else
        {
            mergedList[iResult] = initList[i2];
            i2++;
        }
    }
    copy(initList + i1, initList + m + 1, mergedList + iResult);
    copy(initList + i2, initList + n + 1, mergedList + iResult);
}

template <class T>
void MergePass(T *initList, T *resultList, const int n, const int s)
{
    int i;
    for(i = 1; i <= n-2*s+1; i += 2*s)
    {
        Merge(initList, resultList, i, i+s-1, i+2*s-1);
    }
    if((i+s-1) < n) Merge(initList, resultList, i, i+s-1, n);
    else copy(initList + i, initList + n + 1, resultList + i);
}

template <class T>
void MergeSort(T *a, const int n)
{
    T *tempList = new T[n+1];
    for(int l = 1; l < n; l *= 2)
    {
        MergePass(a, tempList, n, l);
        l *= 2;
        MergePass(tempList, a, n, l);
    }
    delete [] tempList;
}

// Recursive Merge Sort

template <class T>
int ListMerge(T *a, int *link, const int start1, const int start2)
{
    int iResult = 0;
    int i1, i2;
    for(i1 = start1, i2 = start2; i1 && i2;)
    {
        if(a[i1] <= a[i2])
        {
            link[iResult] = i1;
            iResult = i1;
            i1 = link[i1];
        }
        else
        {
            link[iResult] = i2;
            iResult = i2;
            i2 = link[i2];
        }       
    }
    if(i1 == 0) link[iResult] = i2;
    else link[iResult] = i1;
    return link[0];
}

template <class T>
int rMergeSort(T *a, int *link, const int left, const int right)
{
    if(left >= right) return left;
    int mid = (left + right)/2;
    return ListMerge(a, link, rMergeSort(a, link, left, mid), rMergeSort(a, link, mid+1, right));
}

template <class T>
void PrintRMergeSort(T *a, int *link)
{
    int n = link[0];
    while(n)
    {
        cout << a[n] << " "; 
        n = link[n];
    }
    cout << endl;  
}

// heap sort

template <class T>
void Adjust(T *a, const int root, const int n)
{
    T e = a[root];
    int j;
    for(j = 2*root; j <= n; j *= 2)
    {
        if(j < n && a[j] < a[j+1]) j++;
        if(e >= a[j]) break;
        a[j/2] = a[j];
    }
    a[j/2] = e;
}

template <class T>
void HeapSort(T *a, const int n)
{
    for(int i = n/2; i >= 1; i--)
    {
        Adjust(a, i, n);
    }
    for(int i = n-1; i >= 1; i--)
    {
        swap(a[1], a[i+1]);
        Adjust(a, 1, i);
    }
}


// function

template <class T>
void copyArray(T *copy, T *base)
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        copy[i] = base[i];
    }
}

template <class T>
void printArray(T *arr)
{
   for(int i = 1; i <= s; i++)
        cout << arr[i] << " ";
    cout << endl; 
}

void Index(int *arr)
{
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        arr[i] = 0;
    }
}


int main()
{
    int intArray[ARRAYSIZE];
    int tmpintArray[ARRAYSIZE];
    float floatArray[ARRAYSIZE];
    float tmpfloatArray[ARRAYSIZE];
    char charArray[ARRAYSIZE];
    char tmpcharArray[ARRAYSIZE];
    string stringArray[ARRAYSIZE];
    string tmpstringArray[ARRAYSIZE];
    int indexArray[ARRAYSIZE];
    
    // create random array
    for(int i = 1; i <= s; i++)
        intArray[i] = rand()%100;  //Generate number between 0 to 99

    for(int i = 1; i <= s; i++)
        floatArray[i] = rand()/float(RAND_MAX)*24.f+1.f;
    
    for(int i = 1; i <= s; i++)
        charArray[i] = 'a' + rand()%26;;

    for(int i = 1; i <= s; i++)
        charArray[i] = 'a' + rand()%26;

    for(int i = 1; i <= s; i++)
    {
        int n = rand() % 7 + 1; // limit one string less than 7 char
        string tmp = "";
        for(int i = 0; i < n; i++)
        {
            tmp = tmp + alphabet[rand() % 26];
        }
        stringArray[i] = tmp; 
    }

    // sort array
    // int
    cout << "Original: ";
    printArray(intArray);

    copyArray(tmpintArray, intArray);
    InsertionSort(tmpintArray, s);
    cout << "InsertionSort: ";
    printArray(tmpintArray);

    copyArray(tmpintArray, intArray);
    QuickSort(tmpintArray, 1, s);
    cout << "QuickSort: ";
    printArray(tmpintArray);

    copyArray(tmpintArray, intArray);
    MergeSort(tmpintArray, s);
    cout << "MergeSort: ";
    printArray(tmpintArray);

    copyArray(tmpintArray, intArray);
    Index(indexArray);
    rMergeSort(tmpintArray, indexArray, 1, s);
    cout << "rMergeSort: ";
    PrintRMergeSort(tmpintArray, indexArray);
    
    copyArray(tmpintArray, intArray);
    HeapSort(tmpintArray, s);
    cout << "HeapSort: ";
    printArray(tmpintArray);

    cout << endl;

    // float
    cout << "Original: ";
    printArray(floatArray);

    copyArray(tmpfloatArray, floatArray);
    InsertionSort(tmpfloatArray, s);
    cout << "InsertionSort: ";
    printArray(tmpfloatArray);

    copyArray(tmpfloatArray, floatArray);
    QuickSort(tmpfloatArray, 1, s);
    cout << "QuickSort: ";
    printArray(tmpfloatArray);

    copyArray(tmpfloatArray, floatArray);
    MergeSort(tmpfloatArray, s);
    cout << "MergeSort: ";
    printArray(tmpfloatArray);

    copyArray(tmpfloatArray, floatArray);
    Index(indexArray);
    rMergeSort(tmpfloatArray, indexArray, 1, s);
    cout << "rMergeSort: ";
    PrintRMergeSort(tmpfloatArray, indexArray);

    copyArray(tmpfloatArray, floatArray);
    HeapSort(tmpfloatArray, s);
    cout << "HeapSort: ";
    printArray(tmpfloatArray);

    cout << endl;

    // char
    cout << "Original: ";
    printArray(charArray);

    copyArray(tmpcharArray, charArray);
    cout << "InsertionSort: ";
    InsertionSort(tmpcharArray, s);
    printArray(tmpcharArray);
    
    copyArray(tmpcharArray, charArray);
    cout << "QuickSort: ";
    QuickSort(tmpcharArray, 1, s);
    printArray(tmpcharArray);

    copyArray(tmpcharArray, charArray);
    MergeSort(tmpcharArray, s);
    cout << "MergeSort: ";
    printArray(tmpcharArray);

    copyArray(tmpcharArray, charArray);
    Index(indexArray);
    rMergeSort(tmpcharArray, indexArray, 1, s);
    cout << "rMergeSort: ";
    PrintRMergeSort(tmpcharArray, indexArray);

    copyArray(tmpcharArray, charArray);
    HeapSort(tmpcharArray, s);
    cout << "HeapSort: ";
    printArray(tmpcharArray);

    cout << endl;

    // string
    cout << "Original: ";
    printArray(stringArray);

    copyArray(tmpstringArray, stringArray);
    cout << "InsertionSort: ";
    InsertionSort(tmpstringArray, s);
    printArray(tmpstringArray);
    
    copyArray(tmpstringArray, stringArray);
    cout << "QuickSort: ";
    QuickSort(tmpstringArray, 1, s);
    printArray(tmpstringArray);
    
    copyArray(tmpstringArray, stringArray);
    MergeSort(tmpstringArray, s);
    cout << "MergeSort: ";
    printArray(tmpstringArray);

    copyArray(tmpstringArray, stringArray);
    Index(indexArray);
    rMergeSort(tmpstringArray, indexArray, 1, s);
    cout << "rMergeSort: ";
    PrintRMergeSort(tmpstringArray, indexArray);

    copyArray(tmpstringArray, stringArray);
    HeapSort(tmpstringArray, s);
    cout << "HeapSort: ";
    printArray(tmpstringArray);

    cout << endl;

    return 0;
}





