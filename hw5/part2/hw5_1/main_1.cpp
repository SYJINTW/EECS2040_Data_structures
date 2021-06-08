#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;
/*
class Vertex
{
public:
    Vertex(int v) { value = v; next = NULL; };
private:
    int value;
}
*/
class Graph
{
public:
    // DONE:
    Graph(int num);
    // TODO:
    void InsertVertex(int v);
    // TODO:
    void InsertVertex(int u, int v);
    // DONE:
    void DFS_driver(int v);
    void DFS(int v);
    // DONE:
    void BFS(int v);
private:
    int n; // number of vertex
    int e; // number of edge
    bool* visited;
    vector<vector<int>> VertexList;
};

Graph::Graph(int num)
{
    n = num;
    e = 0;
    VertexList = vector<vector<int>>(10);
}

void
Graph::InsertVertex(int v)
{}

void
Graph::InsertVertex(int u, int v)
{
    VertexList[u].push_back(v);
    VertexList[v].push_back(u);
}

void
Graph::DFS_driver(int v)
{
    visited = new bool[n];
    fill(visited, visited+n, false);
    DFS(v);
    delete [] visited;
}

void
Graph::DFS(int v)
{
    visited[v] = true;
    for(auto w = VertexList[v].begin(); w != VertexList[v].end(); w++)
        if(!visited[*w]) DFS(*w);
}

void 
Graph::BFS(int v)
{
    visited = new bool[n];
    fill(visited, visited+n, false); 
    visited[v] = true;
    queue<int> q;
    q.push(v);
    while(!q.empty())
    {
        v = q.front();
        q.pop();
        for(auto w = VertexList[v].begin(); w != VertexList[v].end(); w++)
        {
            if(!visited[*w])
            {
                q.push(*w);
                visited[*w] = true;
            }
        } // for end
    } // while end
    delete [] visited;
}

int main()
{
    
}