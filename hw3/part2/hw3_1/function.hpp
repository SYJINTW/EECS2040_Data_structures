#ifndef FUNCTION_HPP
#define FUNCTION_HPP

using namespace std;


template <class T> class Chain;  // 前向宣告

template <class T>
class ChainNode
{
    public:
        friend class Chain<T>;
        friend ostream& operator<<(ostream& os, Chain<T>& C);

    private:
        T data;
        ChainNode<T>* link;
};

template <class T>
class Chain 
{
    public:
        Chain() {first = NULL;} // 建構子將first初始化成0
        void InsertFront(T& value);
        void DeleteFront();
        void DeleteBack();
        T Front();
        T Back();
        T Get(int i);
        void Delete(int i);
        void Insert(int i, T& value);
        friend ostream& operator<<(ostream& os, Chain<T>& C)
        {
            ChainNode<T>* now = C.first;
            now = now->link;
            os << "First";
            while(now != NULL)
            {
                os << " -> " << now->data;
                now = now->link;
            }
            os << " -> " << "End\n";
            return os;
        }
        

    private:
        ChainNode<T>* first;
};


template <class T>
void
Chain<T>::InsertFront(T& value)
{
    ChainNode<T>* tmp = new ChainNode<T>();
    tmp->data = value;
    tmp->link = NULL;
    if(first == NULL) // there is no element in the Chain
    {   
        first = new ChainNode<T>();
        first->link = tmp;
        return;
    }
    tmp->link = first->link;
    first->link = tmp;
    return;
}

template <class T>
void
Chain<T>::DeleteFront()
{
    ChainNode<T>* tmp = this->first->link;
    first->link = first->link->link;
    delete tmp;
}

template <class T>
void
Chain<T>::DeleteBack()
{
    ChainNode<T>* tmp = first;
    while(tmp->link->link != NULL)
    {
        tmp = tmp->link;
    }
    delete tmp->link;
    tmp->link = NULL;
}

template <class T>
T
Chain<T>::Front()
{
    return first->link->data;
}

template <class T>
T
Chain<T>::Back()
{
    ChainNode<T>* tmp = first;
    while(tmp->link != NULL)
    {
        tmp = tmp->link;
    }
    return tmp->data;
}

template <class T>
T
Chain<T>::Get(int i)
{
    int count = i;
    ChainNode<T>* tmp = first;
    while(count--)
    {
        tmp = tmp->link;
    }
    return tmp->data;
}

template <class T>
void
Chain<T>::Delete(int i)
{
    int count = i - 1;
    ChainNode<T>* now = first;
    while(count--)
    {
        now = now->link;
    }
    ChainNode<T>* tmp = now->link;
    now->link = now->link->link;
    delete tmp;
}

template <class T>
void
Chain<T>::Insert(int i, T& value)
{
    int count = i - 1;
    ChainNode<T>* now = first;
    while(count--)
    {
        now = now->link;
    }
    ChainNode<T>* tmp = new ChainNode<T>;
    tmp->data = value;
    tmp->link = now->link;
    now->link = tmp;
}



#endif // FUNCTION_HPP