
// (f)
template <class T>
Chain<T>
Chain<T>::Merge(Chain<T> &L2)
{
    Chain<T> L3;                        // a new chain L3 for merge L1 & L2
    ChainNode<T> *Pos1 = first;         // recording current position of L1
    ChainNode<T> *Pos2 = L2.first;      // recording current position of L2
    ChainNode<T> *now;                  // pointer to built the new merge chain
    L3.first = Pos1;                    // build the first Node of L3
    now = L3.first;                     // now is at L3 first node
    Pos1 = Pos1 -> link;                // move to next Node of L1
    while (Pos1 != 0 && Pos2 != 0)      // loop to build L3 until one chain ends
    {
        now->link = Pos2;               // merge component of L2 into L3
        Pos2 = Pos2 -> link;            // move to next Node of L2
        now = now -> link;              // move to next Node of L3
        now -> link = Pos1;             // merge component of L1 into L3
        Pos1 = Pos1 -> link;            // move to next Node of L1
        now = now -> link;              // move to next Node of L3
    }
    if (Pos1 != 0)                      // check which chain isn't empty
        now -> link = Pos1;             // link the left Node in L1 to L3
    else
        now -> link = Pos2;             // link the left Node in L2 to L3 
    first = 0;                          // set their first to 0
    L2.first = 0;
    return L3;                          // return the merge chain L3
}
