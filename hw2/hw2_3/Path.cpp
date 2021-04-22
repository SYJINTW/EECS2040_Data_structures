#include <iostream>
#include <fstream>
#include "Stack.hpp"
#include "offsets.hpp"
#include "Items.hpp"

using namespace ::std;

#define row 9
#define col 9
//#define row 12
//#define col 15

char maze[row + 2][col + 2];
int mark[row + 2][col + 2];

void Path(const int m, const int p);

int main()
{
    ifstream file("./maze314.txt");
    //ifstream file("./maze311.txt");

    if (!file)
    {
        cout << "Can't open the file!\n";
        return 0;
    }

    // read in maze txt and store in array
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            file >> maze[i][j];

    // set boundary
    for (int j = 0; j < col + 2; j++)
        maze[0][j] = maze[row + 1][j] = '-';
    for (int i = 1; i < row + 1; i++)
        maze[i][0] = maze[i][col + 1] = '-';
    maze[1][0] = 'S';
    maze[row][col + 1] = 'E';

    // close file
    file.close();

    // output maze
    for (int i = 0; i < row + 2; i++)
    {
        for (int j = 0; j < col + 2; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    setmovearray(); // in offset.hpp
    Path(row, col);

    cout << endl;

    //cout << "Show the path: " << endl;
    // output maze
    //for (int i = 0; i < row + 2; i++)
    //{
    //    for (int j = 0; j < col + 2; j++)
    //        cout << maze[i][j] << " ";
    //    cout << endl;
    //}
    return 0;
}

void Path(const int m, const int p)
{
    //maze[1][1] = '*';
    mark[1][1] = '1';
    Stack<Items> stack(m * p);
    Items temp(1, 1, E);
    stack.Push(temp);
    while (!stack.IsEmpty())
    {
        temp = stack.Top();
        stack.Pop();
        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;
        bool havepathflag = false;
        while (d < 8)
        {
            int g = i + movearray[d].a;
            int h = j + movearray[d].b;
            if ((g == m) && (h == p))
            {
                //maze[g][h] = '*';
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                stack.Push(temp);
                cout << stack;
                cout << "The end (" << g << "," << h << ")\n";
                return;
            }

            if ((maze[g][h] == '0') && (mark[g][h] == 0))
            {
                havepathflag = true;
                //maze[g][h] = '*';
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                stack.Push(temp);
                i = g;
                j = h;
                d = N;
            }
            else
            {
                d++;
            }
        }
        //if (!havepathflag)
        //{
            //maze[i][j] = '0';
            //mark[i][j] = 2;
        //}
    }
    cout << "No path in maze." << endl;
}
