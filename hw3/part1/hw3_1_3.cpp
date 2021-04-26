template <class T>
int List<T>::Calculate()
{
    Iterator p = Begin();               
    int result = 0;
    while((p+5)!=End())
    {
        result += (*p) * (*(p + 5));
        p++;
    }
    return result;
}