
// (c)
template <class T>
void
Chain<T>::Insertion(int k, T& value)
{
    if(k <= CountNode)
        throw "The Node doesn't exist"
    if(first == 0 && k ==1)
    {
        first = new ChainNode;                      // create a new Node
        first->data = value;                        // input value to the data
        first->link = 0;                             // set this Node as the fist of the link
    }
    else
    {
        int count = 0;                              // for counting the nuber of node
        ChainNode<T> *node = first;                 // node point to the first of the link
        ChainNode<T> *insert = new ChainNode<T>;    // create a new Node
        insert->data = value;                       // set the data of the Node as value
        while(count < k-1)                          // use loop to find the k-1th node
        {
            count++;                                // increase count
            node = node->link;                      // point to the next node
        }
        insert->link = node->link;                  // the Node link with the kth node
        node->link = insert;                        // k-1th node point to insert
    }
}

