// (c)
template <class T>
int 
List<T>::Calculate() 
{
    Iterator Pos = Begin();                 // from i = 1
    int result = 0;                         // reset result to 0
    while ((Pos + 5) != End())              // loop for i from 1 to n-5
    {            
        result += (*Pos) * (*(Pos + 5));    // sum x[i] * x[i + 5] for every possible i
        Pos++;                              // move to next i
    }
    result += (*Pos) * (*(Pos + 5));        // add the x[n - 5] * x[n] to result
    return result;                          // return the sum
}