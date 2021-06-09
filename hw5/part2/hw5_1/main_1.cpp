#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

class Graph
{
public:
    // DONE:
    Graph(int num);
    // DONE:
    ~Graph() {};
    // DONE:
    void Setup();
    // DONE:
    void InsertVertex(int v);
    // DONE:
    void InsertVertex(int u, int v);
    // DONE:
    void DFS_driver(const int v);
    void DFS(const int v);
    // DONE:
    void BFS(int v);
    // DONE:
    void Components();
    // TODO:
    void DfnLow(const int x);
    void DfnLow(const int u, const int v);

private:
    int n; // number of vertex
    int e; // number of edge
    bool* visited;
    vector<vector<int>> VertexList;
    int* dfn;
    int* low;
    int num;
};

Graph::Graph(int num)
{
    n = num;
    e = 0;
    VertexList = vector<vector<int>>(10);
}

void
Graph::Setup()
{
    int edge, type, u, v;
    cout << "How many edges: ";
    cin >> edge;
    if(edge <= 0)
    {
        e = 0;
        return;
    }
    else
    {
        e = edge;
        while(edge--)
        {
            cin >> type;
            if(type)
            {
                cin >> u >> v;
                InsertVertex(u,v);
            }
            else
            {
                cin >> u;
                InsertVertex(u);
            }
        }
    }
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
Graph::DFS_driver(const int v)
{
    visited = new bool[n];
    fill(visited, visited+n, false);
    DFS(v);
    cout << endl;
    delete [] visited;
}

void
Graph::DFS(const int v)
{
    cout << v << " ";
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
        cout << v << " ";
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
    cout << endl;
    delete [] visited;
}

void
Graph::Components()
{
    visited = new bool[n];
    fill(visited, visited+n, false);
    for(int i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            DFS(i);
            cout << endl;
        }
    }
    delete [] visited;
}

void
Graph::DfnLow(const int x)
{
    num = 1;
    dfn = new int[n];
    low = new int[n];
    fill(dfn, dfn+n, 0);
    fill(low, low+n, 0);
    DfnLow(x, -1);
    for(int i = 0; i < n; i++)
        cout << dfn[i] << " ";
    cout << endl;
    for(int i = 0; i < n; i++)
        cout << low[i] << " ";
    cout << endl;
     
    delete [] dfn;
    delete [] low;
}

void
Graph::DfnLow(const int u, const int v)
{
    dfn[u] = low[u] = num++;
    for(auto w = VertexList[u].begin(); w != VertexList[u].end(); w++)
    {
        if(dfn[*w] == 0)
        {
            DfnLow(*w,u);
            low[u] = min(low[u], low[*w]);
        }
        else if(*w != v)
            low[u] = min(low[u],dfn[*w]);
    }

}

int main()
{
    Graph g1(8), g2(8), g3(10);
    g1.Setup();
    // BFS
    cout << "g1.BFS(0): "; 
    g1.BFS(0);
    cout << "g1.BFS(3): ";
    g1.BFS(3);
    cout << "g1.BFS(7): ";
    g1.BFS(7);
    // DFS
    cout << "g1.DFS(0): ";
    g1.DFS_driver(0);
    cout << "g1.DFS(3): ";
    g1.DFS_driver(3);
    cout << "g1.DFS(7): ";
    g1.DFS_driver(7);
    // Components & DfnLow
    cout << "g1's components: " << endl;
    g1.Components();
    cout << "g1's dfn & low: " << endl;
    g1.DfnLow(3);

    g2.Setup();
    // BFS
    cout << "g2.BFS(0): ";
    g2.BFS(0);
    cout << "g2.BFS(3): ";
    g2.BFS(3);
    cout << "g2.BFS(7): ";
    g2.BFS(7);
    // DFS
    cout << "g2.DFS(0): ";
    g2.DFS_driver(0);
    cout << "g2.DFS(3): ";
    g2.DFS_driver(3);
    cout << "g2.DFS(7): ";
    g2.DFS_driver(7);
    // Components & DfnLow
    cout << "g2's components: " << endl;
    g2.Components();
    cout << "g2's dfn & low: " << endl;
    g2.DfnLow(3);

    g3.Setup();
    // BFS
    cout << "g3.BFS(0): "; 
    g3.BFS(0);
    cout << "g3.BFS(3): ";
    g3.BFS(3);
    cout << "g3.BFS(7): ";
    g3.BFS(7);
    // DFS
    cout << "g3.DFS(0): ";
    g3.DFS_driver(0);
    cout << "g3.DFS(3): ";
    g3.DFS_driver(3);
    cout << "g3.DFS(7): ";
    g3.DFS_driver(7);
    // Components & DfnLow
    cout << "g3's components: " << endl; 
    g3.Components();
    cout << "g3's dfn & low: " << endl;
    g3.DfnLow(3);
}

