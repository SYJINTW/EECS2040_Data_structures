#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void Path(const int m, const int p)
{   // 輸出迷宮的一個路徑（如果有的話）； maze[0][i] = maze[m+1][i] =
    //  maze[j][0] = maze[j][p+1] = 1, 0  i  p+1, 0  j  m+1。
    // 從 (1, 1) 開始
    mark[1][1] = 1;
    Stack<Items> stack(m * p);
    Items temp(1, 1, E);
    // 設定 temp.x、temp.y、與temp.dir
    Stack.Push(temp);
    while (!stack.IsEmpty())
    { // 堆疊不是空的
        temp = stack.Top();
        stack.Pop(); // 彈出
        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;
        while (d < 8) // 往前移動
        {
            int g = i + move[d].di;
            int h = j + move[d].dj;
            if ((g = = m) && (h = = p))
            { // 抵達出口
                 
                {
                    cout << stack;                 // 輸出路徑
                    cout << i << " " << j << endl; // 路徑上的上兩個方塊
                    cout << m << " " << p << endl;
                    return;
                }
                  if ((!maze[g][h]) && (!mark[g][h])) // 新位置
                {
                    mark[g][h] = 1;
                    temp.x = i;
                    temp.y = j;
                    temp.dir = d + 1; //try new direction
                    stack.Push(temp); // 加入堆疊
                    i = g;
                    j = h;
                    d = N; // 移到 (g, h)
                }
                else d++; // 試下一個方向
            }
        }
        cout << "No path in maze." << endl;
    }
