
// (e)
template <class T>
Chain<T> 
Chain<T>::Split(ChainNode<T> *split)
{
    if (first == 0) throw "Empty chain.";   // Empty Chain
    ChainNode<T> *node = first;         // a pointer point to the first
    Chain<T> de;                        // the split chain
    while(node -> link != split)        // loop to find the last Node of first chain
    {     
        node = node -> link;            // move to the next Node
    } 
    node -> link = 0;                   // set the link of the end of first chain to 0
    de.first = split;                   // new second chain start from split
    return de;                          // return the new second chain
}

