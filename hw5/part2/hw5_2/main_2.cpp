#include <iostream>
#include <iomanip>
#include <vector>

#define MAX 50000

using namespace std;

class Graph
{
public:
    // DONE:
    Graph(int k);
    ~Graph(){};
    void Setup();
    // TODO:
    void Path(int n);
    // DONE:
    int Choose(int n);
    void ShortestPath(const int n, const int v);
    // DONE:
    int Vertex();
private:
    int vertex, edge;
    vector<vector<int>> length;
    vector<int> dist, s, p;
};

Graph::Graph(int k)
{
    vertex = k;
}

void
Graph::Setup()
{
    int v, u, l;
    length = vector(vertex, vector<int>(vertex, MAX)); // set infinite as 50000
    dist = vector(vertex, 0);
    s = vector(vertex, 0);
    p = vector(vertex, MAX);
    // input number of edge
    cin >> edge;
    for(int i = 0; i < vertex; i++)
        length[i][i] = 0;
    for(int i = 0; i < edge; i++)
    {
        // input source, destination, length
        cin >> v >> u >> l;
        length[v][u] = l;
    }
}

int
Graph::Choose(int n)
{
    int minV = -1;
    int minDist = MAX;
    for(int i = 0; i < n; i++)
    {
        if(s[i] == false && dist[i] <= minDist)
        {
            minV = i;
            minDist = dist[i];
        }
    }
    return minV;
}

void 
Graph::Path(int n)
{
    bool haveInf = false;
    if(p[n] != -1)
    {
        int tmp = n;
        vector<int> path;
        path.push_back(p[tmp]);
        tmp = p[tmp];
        
        do
        {
            if(tmp == MAX)
            {
                haveInf = true;
            }
            path.push_back(p[tmp]);
            tmp = p[tmp];
        } 
        while(tmp != -1 && haveInf == false);

        if(haveInf == true)
        {
            cout << "X";
            return;
        }
        path.pop_back();
        while(!path.empty())
        {
            cout << path.back() << " -> ";
            path.pop_back();
        }
    }
    cout << n;
}

void
Graph::ShortestPath(const int n, const int v)
{
    // initialize
    for(int i = 0; i < n; i++)
    {
        s[i] = false;
        dist[i] = length[v][i];
    }

    s[v] = true;
    dist[v] = 0;
    p[v] = -1;
    int preVertex = v;

    for(int i = 0; i < n-2; i++)
    {
        int u = Choose(n);
        s[u] = true;
        if(i == 0 || p[u] == MAX) p[u] = v;
        preVertex = u;

        for(int w = 0; w < n; w++)
        {
            if(!s[w] && dist[u] + length[u][w] < dist[w])
            {
                dist[w] = dist[u] + length[u][w];
                p[w] = preVertex;
            }
        } // end of for(int w = 0; ...)
    } // end of for(int i = 0; ...)
    for(int i = 0; i < vertex; i++)
    {
        cout << "[" << i << "]: ";
        Path(i);
        if(dist[i] == MAX)
            cout << " / Infinite" << endl;
        else
            cout << " / " << dist[i] << endl;
    }
    /*
    for(int i = 0; i < vertex; i++)
    {
        Path(i);
        cout << endl;
    }
    */
    cout << endl;
}

int
Graph::Vertex()
{
    return vertex;
}


int main()
{
    Graph G1(8);
    G1.Setup();
    G1.ShortestPath(8, 4);

    Graph G2(6);
    G2.Setup();
    G2.ShortestPath(6, 0);

    Graph G3(6);
    G3.Setup();
    G3.ShortestPath(6, 0);
}