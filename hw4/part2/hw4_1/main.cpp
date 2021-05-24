#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include "function.hpp"

using namespace std;

int main()
{
    cout << "Construct a new empty Tree." << endl;
    Tree<char> t;

    if(t.IsEmpty()) cout << "The Tree is empty." << endl;
    else cout << "The Tree is not empty." << endl;
    
    cout << endl;

    cout << "Give the Tree some value: " << endl;
    t.InitTree();

    cout << endl;

    cout << "Construct a new CopyTree by copy constructor." << endl;
    Tree<char> copyt(t);

    if(t == copyt) cout << "Tree is equal to CopyTree." << endl;
    else cout << "Tree is not equal to the CopyTree." << endl;

    cout << endl;

    cout << "Inorder: ";
    t.Inorder();
    cout << endl;
    cout << "Inorder(copy): ";
    copyt.Inorder();
    cout << endl;
    
    cout << endl;

    cout << "NonrecInorder: "; 
    t.NonrecInorder();
    cout << endl;
    cout << "NonrecInorder(copy): "; 
    copyt.NonrecInorder();
    cout << endl;

    cout << endl;

    cout << "Preorder: "; 
    t.Preorder();
    cout << endl;
    cout << "Preorder(copy): "; 
    copyt.Preorder();
    cout << endl;

    cout << endl;

    cout << "Postorder: "; 
    t.Postorder();
    cout << endl;
    cout << "Postorder(copy): "; 
    copyt.Postorder();
    cout << endl;
    
    cout << endl;

    cout << "LevelOrder: "; 
    t.LevelOrder();
    cout << endl;
    cout << "LevelOrder(copy): "; 
    copyt.LevelOrder();
    cout << endl;

    cout << endl;

    cout << "NoStackInorder: ";
    t.NoStackInorder();
    cout << endl; 
    cout << "NoStackInorder(copy): ";
    copyt.NoStackInorder();
    cout << endl;

    cout << endl;

    cout << "The data of root: ";
    cout << t.RootData() << endl;

    Tree<char> lt = t.LeftSubtree();
    Tree<char> rt = t.RightSubtree();
    cout << "The left tree of the Tree (Inorder): ";
    lt.Inorder();
    cout << endl;
    cout << "The right tree of the Tree (Inorder): ";
    rt.Inorder();
    cout << endl;
    cout << endl;
}

// test input
/*
textbook input: 
A/B*C*D+E
*/