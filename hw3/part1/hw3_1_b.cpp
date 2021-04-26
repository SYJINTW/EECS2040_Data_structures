
// (b)
template <class T>
void
Chain<T>::ChangeData(int k, T& Y)       // k for kth node, Y for value
{
    if(first == 0) throw "Empty chain"  // Chain is empty
    int count = 1;                      // set count as a counter
    ChainNode<T> *node = first;         // node point to first
    while(count < k)                    // find the kth-1 node
    {
        count++;                        // increase count
        node = node->link;              // node point to the next one
    }
    node->data = Y;                     // change node data to Y
}

