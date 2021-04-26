// (a)
template <class T>
int
Chain<T>::CountNode()
{
    int count = 0;              // initialize the count for counting Nodes
    ChainNode<T> *node = first; // node point to first
    while(node != 0)            // counting untill there is no Nodes
    {                       
        count++;                // increase count
        node = node->link;      // point node to the next Node
                                // at the last node will point to NULL
    }
    return count;               // return the number of Nodes
}