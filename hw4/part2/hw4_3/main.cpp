#include <iostream>
#include <iomanip>
#include "function.hpp"

using namespace std;

int main()
{
    int num, key;
    int tmp = 70;
    char value;
    cout << "Create a new empty BST." << endl;
    BST<int, char> T;

    BST<int, char> Small;
    BST<int, char> Big;
    pair<int, char>* Mid;

    if(T.IsEmpty()) cout << "BST is empty." << endl;
    else cout << "BST is not empty." << endl;

    cout << endl;

    cout << "How many elements are in the BST: ";
    cin >> num;
    cout << "Input (key,value): ";
    while(num--)
    {
        cin >> key >> value;
        T.Insert({key, value});
    }

    cout << endl;

    cout << "BST PostOrder: ";
    T.Postorder();
    cout << endl;

    pair<int, char>* getNode = T.Get(tmp);
    cout << "Get(70) = ";
    cout << "(" << getNode->first << "," << getNode->second << ")" << endl;

    getNode = T.RankGet(3);
    cout << "RankGet(3) = ";
    cout << "(" << getNode->first << "," << getNode->second << ")" << endl; 

    cout << endl;

    cout << "Delete(50)." << endl;
    T.Delete(50);
    cout << "Delete(5)." << endl;
    T.Delete(5);
    cout << "Delete(60)." << endl;
    T.Delete(60);

    cout << endl;
    
    cout << "BST PostOrder: ";
    T.Postorder();
    cout << endl;

    getNode = T.Get(tmp);
    cout << "Get(70) = ";
    cout << "(" << getNode->first << "," << getNode->second << ")" << endl;

    getNode = T.RankGet(3);
    cout << "RankGet(3) = ";
    cout << "(" << getNode->first << "," << getNode->second << ")" << endl;

    cout << endl;

    cout << "Split(key = 35)" << endl;
    T.Split(35, Small, Mid, Big);
    cout << "Mid: ";
    cout << "(" << Mid->first << "," << Mid->second << ")" << endl;
    cout << "Small BST PostOrder: ";
    Small.Postorder();
    cout << endl;
    cout << "Big BST PostOrder: ";
    Big.Postorder();
    cout << endl;

    return 0;
}

/*
11
50 a 5 b 30 c 40 d 80 e 35 f 2 g 20 h 15 i 60 j 70 k
*/