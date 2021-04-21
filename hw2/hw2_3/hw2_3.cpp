#include <iostream>
#include <iomanip>
#include <string>
#include "function.hpp"
#include "offsets.hpp"

#define row 9
#define col 9

using namespace std;


int maze311[12][15] = {
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
    {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
    {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0}};

int maze314[11][11] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int mark[11][11];

void Path(const int m, const int p) {
    mark[1][1] = 1;
    Stack<Items> stack(m * p);
    Items temp(1, 1, E);
    stack.Push(temp);
    while (!stack.IsEmpty()) {
        temp = stack.Top();
        stack.Pop();
        int i = temp.x, j = temp.y, d = temp.dir;
        while(d < 8) {
            int g = i + movearray[d].a, h = j + movearray[d].b;
            if ((g == m) && (h == p)) {
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                stack.Push(temp);
                cout << stack;
                cout << "The end (" << m << "," << p << ")\n";
                return;
            }
            if ((!maze[g][h]) && (!mark[g][h])) {
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                stack.Push(temp);
                i = g;
                j = h;
                d = N;
            }
            else d++;
        }
    }
    cout << "No path in maze." << endl;
}

int main()
{
    for (int i = 0; i < row + 2; i++)
    {
        for (int j = 0; j < col + 2; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }
    setmovearray();
    Path(row, col);
    return 0
}
