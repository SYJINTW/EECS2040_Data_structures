#ifndef FUNCTION_1_HPP
#define FUNCTION_1_HPP

#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

/*
template <class T>
class BinaryTree
{ // objects: A finite set of nodes either empty or consisting
  // of a root node, left BinaryTree and right BinaryTree
public:
  BinaryTree();   // constructor for an empty binary tree
  bool IsEmpty(); // return true iff the binary tree is empty
  BinaryTree(BinaryTree<T> &bt1, T &item, BinaryTree<T> &bt2);
  // constructor given the root item and left subtrees bt1 and right subtree bt2
  BinaryTree<T> LeftSubtree();  // return the left subtree
  BinaryTree<T> RightSubtree(); // return the right subtree
  T RootData();                 // return the data in the root node of *this
};
*/

template <class T> class Tree;

template <class T>
class TreeNode
{
public:
  friend class Tree <T>;
  TreeNode()
  {
    data = 0;
    leftChild = NULL;
    rightChild = NULL;
  };

  TreeNode(T& d, TreeNode<T>* l, TreeNode<T>* r)
  {
    data = d;
    leftChild = l;
    rightChild = r;
  };

private:
  T data;
  TreeNode<T> *leftChild;
  TreeNode<T> *rightChild;
};

template <class T>
class Tree
{
public:
  // DONE: constructor
  Tree(){root = NULL;};
  // DONE: copy constructor
  TreeNode<T>* Copy(TreeNode<T> *origNode);
  Tree(const Tree<T>& s);
  // DONE: insert a new node
  Tree(Tree<T> &ltr, T &item, Tree<T> &rtr);
  
  // four traversal methods
  // DONE:
  bool IsEmpty();
  // DONE:
  Tree<T> LeftSubtree();
  // DONE:
  Tree<T> RightSubtree();
  // DONE:
  T RootData();

  // DONE:
  void InitTree();
  // DONE:
  void Inorder();
  void Inorder(TreeNode<T>* currentNode);
  // DONE:
  void Preorder();
  void Preorder(TreeNode<T>* currentNode);
  // DONE:
  void Postorder();
  void Postorder(TreeNode<T>* currentNode);
  // DONE:
  void LevelOrder();
  // DONE: none recursive inorder
  void NonrecInorder();
  // DONE: 
  void NoStackInorder();
  // DONE:
  bool operator==(const Tree &t) const;
  bool Equal(const TreeNode<T> *a, const TreeNode<T> *b) const;

private:
  TreeNode<T> *root;
};

template <class T>
Tree<T>::Tree(const Tree<T>& s)
{
  root = Copy(s.root);
}

template <class T>
TreeNode<T>* 
Tree<T>::Copy(TreeNode<T> *origNode)
{
  if(!origNode) return 0;
  return new TreeNode<T>(origNode->data, Copy(origNode->leftChild), Copy(origNode->rightChild));
}

template <class T>
bool
Tree<T>::IsEmpty()
{
  if (root == NULL)
    return true;
  else
    return false;
}

template <class T>
Tree<T>::Tree(Tree<T> &ltr, T &item, Tree<T> &rtr)
{
  TreeNode<T>* ptr = new TreeNode<T>();
  ptr->data = item;
  ptr->leftChild = ltr.root;
  ptr->rightChild = rtr.root; 
  root = ptr;
}

template <class T>
Tree<T>
Tree<T>::LeftSubtree()
{
  Tree<T> *ptr = new Tree<T>;
  ptr->root = root->leftChild;
  return *ptr;
}

template <class T>
Tree<T>
Tree<T>::RightSubtree()
{
  Tree<T> *ptr = new Tree<T>;
  ptr->root = root->rightChild;
  return *ptr;
}

template <class T>
T
Tree<T>::RootData()
{
  return root->data;
}

// 先不管先後順序了！！！！
template <class T>
void
Tree<T>::InitTree()
{
  string s;
  cin >> s;
  
  TreeNode<T>* litemNode = new TreeNode<T>();
  litemNode->data = s[0];
  litemNode->leftChild = NULL;
  litemNode->rightChild = NULL;
  root = litemNode;

  for(int i = 1; i < s.length(); i+=2)
  {
    TreeNode<T>* citemNode = new TreeNode<T>();
    citemNode->data = s[i];
    citemNode->leftChild = NULL;
    citemNode->rightChild = NULL;

    TreeNode<T>* ritemNode = new TreeNode<T>();
    ritemNode->data = s[i+1];
    ritemNode->leftChild = NULL;
    ritemNode->rightChild = NULL;
     
    citemNode->leftChild = root;
    citemNode->rightChild = ritemNode;    
    
    root = citemNode;
  }
}

template <class T>
void
Tree<T>::Inorder()
{
  Inorder(root);
}

template <class T>
void 
Tree<T>::Inorder(TreeNode<T>* currentNode)
{
  if(currentNode)
  {
    Inorder(currentNode->leftChild);
    cout << currentNode->data;
    Inorder(currentNode->rightChild);
  }
}

template <class T>
void
Tree<T>::Preorder()
{
  Preorder(root);
}

template <class T>
void
Tree<T>::Preorder(TreeNode<T>* currentNode)
{
  if(currentNode)
  {
    cout << currentNode->data;
    Preorder(currentNode->leftChild);
    Preorder(currentNode->rightChild);
  }
}

template <class T>
void
Tree<T>::Postorder()
{
  Postorder(root);
}

template <class T>
void
Tree<T>::Postorder(TreeNode<T>* currentNode)
{
  if(currentNode)
  {
    Postorder(currentNode->leftChild);
    Postorder(currentNode->rightChild);
    cout << currentNode->data;
  }
}

template <class T>
void
Tree<T>::LevelOrder()
{
  queue <TreeNode<T>*> q;
  TreeNode <T> *currentNode = root;
  while(currentNode)
  {
    cout << currentNode->data;
    if(currentNode->leftChild) q.push(currentNode->leftChild);
    if(currentNode->rightChild) q.push(currentNode->rightChild);
    if(q.empty())return;
    currentNode = q.front();
    q.pop();
  }
}

template <class T>
void
Tree<T>::NonrecInorder()
{
  stack<TreeNode<T>*> s;
  TreeNode<T> *currentNode = root;
  while(1)
  {
    while(currentNode)
    {
      s.push(currentNode);
      currentNode = currentNode->leftChild;
    }
    if(s.empty()) return;
    currentNode = s.top();
    s.pop();
    cout << currentNode->data;
    currentNode = currentNode->rightChild;
  }
}

template <class T>
void
Tree<T>::NoStackInorder()
{
  if(!root) return;
  TreeNode<T> *top = 0;
  TreeNode<T> *lastRight = 0;
  TreeNode<T> *p, *q, *r, *r1;
  p = q = root;
  while(1)
  {
    while(1)
    {
      if((!p->leftChild)&&(!p->rightChild))
      {
        cout << p->data;
        break;
      }
      if(!p->leftChild)
      {
        cout << p->data;
        r = p->rightChild;
        p->rightChild = q;
        q = p;
        p = r;
      }
      else
      {
        r = p->leftChild;
        p->leftChild = q;
        q = p;
        p = r;
      }
    }

    TreeNode<T> *av = p;
    while(1)
    {
      if(p == root) return;
      if(!q->leftChild)
      {
        r = q->rightChild;
        q->rightChild = p;
        p = q;
        q = r;
      }
      else if(!q->rightChild)
      {
        r = q->leftChild;
        q->leftChild = p;
        p = q;
        q = r;
        cout << p->data;
      }
      else
      {
        if(q == lastRight)
        {
          r = top;
          lastRight = r->leftChild;
          top = r->rightChild;
          r->leftChild = r->rightChild = 0;
          r = q->rightChild;
          q->rightChild = p;
          p = q;
          q = r;
        }
        else
        {
          cout << q->data;
          av->leftChild = lastRight;
          av->rightChild = top;
          top = av;
          lastRight = q;
          r = q->leftChild;
          q->leftChild = p;
          r1 = q->rightChild;
          q->rightChild = r;
          p = r1;
          break;
        }
      }
    }
  }
}

template <class T>
bool
Tree<T>::operator==(const Tree &t) const
{
  return Equal(root, t.root);
}

template <class T>
bool
Tree<T>::Equal(const TreeNode<T> *a, const TreeNode<T> *b) const
{
  if((!a) && (!b)) return true;
  return (a && b && (a->data == b->data) && Equal(a->leftChild, b->leftChild) && Equal(a->rightChild, b->rightChild));
}





#endif // FUNCTION_1_HPP
