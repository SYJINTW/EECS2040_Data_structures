
template <class T>
void Chain<T>::DeleteOdd() {
    if (first == 0) throw "Empty chain cannot delete!"; // chain is empty
    ChainNode<T> *odd;                          // record which Node need to delete deleted
    ChainNode<T> *node = first -> link;         // pointer use to record the left even Node
    delete first;                               // delete the first Node
    first = node;                               // change the first Node
    while (node -> link != 0 && node != 0)      // loop until the end of chain
        odd = node -> link;                     // move to the Node which needs to delete
        node -> link = node -> link -> link;    // link the even Node
        node = node -> link;                    // move to next even Node
        delete odd;                             // delete Node
    }
}
