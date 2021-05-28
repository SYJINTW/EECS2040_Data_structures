#ifndef FUNCTION_3_HPP
#define FUNCTION_3_HPP

using namespace std;

template <class K, class E>
class BST;

template <class K, class E>
class TreeNode
{
public:
    friend class BST<K,E>;

    // DONE: empty TreeNode
    TreeNode()
    {
        key = 0;
        value = 0;
        leftChild = NULL;
        rightChild = NULL;
    };
    TreeNode(const pair<K, E> &thePair)
    {
        key = thePair.first;
        value = thePair.second;
        leftChild = NULL;
        rightChild = NULL;
    }

private:
    K key;
    E value;
    TreeNode<K,E> *leftChild;
    TreeNode<K,E> *rightChild;
};


template <class K, class E>
class BST
{
public:
    // DONE:
    BST() { root = NULL; };
    // DONE: return true if dictionary is empty
    bool IsEmpty() const
    {
        if(root == NULL) return true;
        else return false;
    };
    // DONE: return pointer to the pair w. specified key
    pair<K, E>* Get(const K &);
    pair<K, E>* Get(TreeNode<K,E>* p, const K& k);
    // DONE: insert the given pair; if key ia a duplicate, update associate element 
    void Insert(const pair<K, E> &);
    // DONE: delete pair w. specified key
    void Delete(const K &delKey);
    // DONE:
    TreeNode<K,E>* Root()
    {
        return root;
    };
    // DONE:
    int Size(TreeNode<K,E>* p);
    // DONE:
    pair<K, E>* RankGet(int r);
    // DONE:
    void Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big);
    // DONE: inorder for demo
    void Postorder();
    void Postorder(TreeNode<K,E>* currentNode);

private:
    TreeNode<K, E> *root;
};

template <class K, class E>
pair<K, E>*
BST<K,E>::Get(const K &k)
{
    return Get(root, k);
}

template <class K, class E>
pair<K, E>*
BST<K,E>::Get(TreeNode<K,E>* p, const K& k)
{
    if(!p) return 0;
    if(k < p->key) return Get(p->leftChild, k);
    if(k > p->key) return Get(p->rightChild, k);
    pair<K,E>* result = new pair<K,E>;
    result->first = p->key;
    result->second = p->value;
    return result;
}


template <class K, class E>
void
BST<K,E>::Insert(const pair<K, E> &thePair)
{
    TreeNode<K,E> *p = root;
    TreeNode<K,E> *pp = NULL;
    while(p)
    {
        pp = p;
        if(thePair.first < p->key) // go to left
        {
            p = p->leftChild;
        }
        else if(thePair.first > p->key) // go to right
        {
            p = p->rightChild;
        }
        else // the same -> update the value
        {
            p->value = thePair.second;
        }
    }

    p = new TreeNode<K,E>(thePair);

    if(root)
    {
        if(thePair.first < pp->key) // be right child
        {
            pp->leftChild = p;
        }
        else // be left child
        {
            pp->rightChild = p;
        }
    }
    else
    {
        root = p;
    }
}

template <class K, class E>
void
BST<K,E>::Delete(const K &delKey)
{
    TreeNode<K,E>* p = root;
    TreeNode<K,E>* pp = NULL;

    while(p->key != delKey)
    {
        pp = p;
        if(delKey < p->key) // find left
            p = p->leftChild;
        else // find right
            p = p->rightChild;
    }

    if(p->leftChild == NULL && p->rightChild == NULL) // no child
    {
        if(pp == NULL) // root
        {
            root = NULL; // no element in BST
        }
        else if(pp->leftChild->key == delKey) // pp leftChild is p
        {
            pp->leftChild = NULL;
        }
        else // pp rightChild is p
        {
            pp->rightChild = NULL;
        }
        delete p;
    }
    else if(p->leftChild != NULL && p->rightChild == NULL) // have one child (left)
    {
        if(pp == NULL) // root
        {
            root = p->leftChild;
        }
        else if(pp->leftChild->key == delKey) // pp leftChild is p
        {
            pp->leftChild = p->leftChild;
        }
        else // pp rightChild is p
        {
            pp->rightChild = p->leftChild;
        }
        delete p;
    }
    else if(p->leftChild == NULL && p->rightChild != NULL) // have one child (right)
    {
        if(pp == NULL) // root
        {
            root = p->rightChild;
        }
        else if(pp->leftChild->key == delKey) // pp leftChild is p
        {
            pp->leftChild = p->rightChild;
        }
        else // pp rightChild is p
        {
            pp->rightChild = p->rightChild;
        }
        delete p;
    }
    else // two child, then replace it by the smallest(left) in the right subtree
    {
        TreeNode<K,E>* last = p;
        TreeNode<K,E>* now = p->rightChild;
        while(now->leftChild)
        {
            last = now;
            now = now->leftChild;
        }

        p->key = now->key;
        p->value = now->value; 

        if(now->rightChild) // have rightChild
            last->leftChild = now->rightChild;
        else // no child
            last->leftChild = NULL;
        delete now;
    }    
}

template <class K, class E>
int
BST<K,E>::Size(TreeNode<K,E>* p)
{
    if(p) return 1 + Size(p->leftChild) + Size(p->rightChild);
    else return 0; // NULL
}


template <class K, class E>
pair<K,E>*
BST<K,E>::RankGet(int r)
{
    TreeNode<K,E>* currentNode = root;
    while(currentNode)
    {
        int leftSize = Size(currentNode->leftChild)+1;
        if(r < leftSize)
            currentNode = currentNode->leftChild;
        else if(r > leftSize)
        {
            r -= leftSize;
            currentNode = currentNode->rightChild;
        }
        else
        {
            pair<K,E>* result = new pair<K,E>;
            result->first = currentNode->key;
            result->second = currentNode->value;
            return result;
        }
    }
    return NULL;
}

template <class K, class E>
void
BST<K,E>::Split(const K& k, BST<K,E>& small, pair<K,E>*& mid, BST<K,E>& big)
{
    if(!root) // empty tree
    {
        small.root = big.root = NULL;
        return;
    }

    TreeNode<K,E>* sHead = new TreeNode<K,E>;
    TreeNode<K,E>* bHead = new TreeNode<K,E>;
    TreeNode<K,E>* s = sHead;
    TreeNode<K,E>* b = bHead;
    TreeNode<K,E>* currentNode = root;
    
    while(currentNode)
    {
        if(k < currentNode->key) // add to big
        {
            b->leftChild = currentNode;
            b = currentNode;
            currentNode = currentNode->leftChild;
        }
        else if(k > currentNode->key) // add to small
        {
            s->rightChild = currentNode;
            s = currentNode;
            currentNode = currentNode->rightChild;
        }
        else // k == currentNode->key (find the mid Node)
        {
            s->rightChild = currentNode->leftChild;
            b->leftChild = currentNode->rightChild;

            small.root = sHead->rightChild;
            delete sHead;
            big.root = bHead->leftChild;
            delete bHead;
            mid = new pair<K,E>(currentNode->key, currentNode->value);
            delete currentNode;
            return;
        }
    }
    // no pair with k
    s->rightChild = b->leftChild = 0;
    small.root = sHead->rightChild;
    delete sHead;
    big.root = bHead->leftChild;
    delete bHead;
    mid = 0;
    return;
}

template <class K, class E>
void
BST<K,E>::Postorder()
{
    Postorder(root);
}

template <class K, class E>
void 
BST<K,E>::Postorder(TreeNode<K,E>* currentNode)
{
    if(currentNode)
    {
        Postorder(currentNode->leftChild);
        Postorder(currentNode->rightChild);
        cout << "(" << currentNode->key << "," << currentNode->value << ") "; 
    }
}








#endif // FUNCTION_3_HPP