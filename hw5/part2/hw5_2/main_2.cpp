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
    // DONE:
    void Path(int n);
    // DONE:
    int Choose(int n);
    void ShortestPath(const int n, const int v);
    // DONE:
    int Vertex();
    // DONE:
    void BellmanFord(const int n, const int v);
    // DONE:
    void AllLength(const int n); // Floyd–Warshall algorithm
private:
    int vertex, edge;
    vector<vector<int>> length, a;
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
                break;
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

    // print process
    cout << "     ";
    for(int h = 0; h < n; h++)
        cout << "  [" << h << "]";
    cout << endl;
    cout << "0" << "  --";
    for(int h = 0; h < n; h++)
    {
        if(dist[h] == MAX) cout << setw(5) << 'X';
        else cout << setw(5) << dist[h];
    }
    cout << endl;
    // end of print process

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

        // print process
        cout << i+1 << setw(4) << u;
        for(int h = 0; h < n; h++)
        {
            if(dist[h] == MAX) cout << setw(5) << 'X';
            else cout << setw(5) << dist[h];
        }
        cout << endl;
        // end of print process

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
}

int
Graph::Vertex()
{
    return vertex;
}

void 
Graph::BellmanFord(const int n, const int v)
{
    for(int i = 0; i < n; i++)
        dist[i] = length[v][i]; // initialize
    
    // print process
    cout << "    ";
    for(int h = 0; h < n; h++)
    {
        cout << " [" << h << "]";
    }
    cout << endl;
    cout << "(" << "0" << "):";
    for(int h = 0; h < n; h++)
    {
        if(dist[h] == MAX) cout << setw(4) << 'X'; 
        else cout << setw(4) << dist[h];
    }
    cout << endl;
    // end of print process 

    for(int k = 2; k <= n-1; k++)
    {
        for(int u = 0; u < n; u++)
        {
            if(u != v)
            {
                for(int i = 0; i < n; i++)
                {
                    if(length[i][u] == MAX) continue;
                    if(dist[u] > dist[i] + length[i][u]) dist[u] = dist[i] + length[i][u];
                }
            }
        }

        // print process
        cout << "(" << k-1 << "):";
        for(int h = 0; h < n; h++)
        {
            if(dist[h] == MAX) cout << setw(4) << 'X'; 
            else cout << setw(4) << dist[h];
        }
        cout << endl;
        // end of print process

    }
}

void
Graph::AllLength(const int n)
{
    a = length;

    // print process
    cout << "Process 0" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "[" << i << "] ";
        for(int j = 0; j < n; j++)
        {
            if(a[i][j] == MAX) cout << setw(4) << "X";
            else cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
    // end print process


    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(a[i][k] == MAX || a[k][j] == MAX) continue;
                if((a[i][k] + a[k][j]) < a[i][j]) a[i][j] = a[i][k] + a[k][j];
            }
        }
        // print process
        cout << "Process "<< k+1 << endl;
        for(int i = 0; i < n; i++)
        {
            cout << "[" << i << "] ";
            for(int j = 0; j < n; j++)
            {
                if(a[i][j] == MAX) cout << setw(4) << "X";
                else cout << setw(4) << a[i][j];
            }
            cout << endl;
        }
        // end print process
    }
}

int main()
{
    // (a)
    cout << "Part a" << endl;
    Graph G1(8);
    G1.Setup();
    G1.ShortestPath(8, 4);
    cout << endl;
    Graph G2(6);
    G2.Setup();
    G2.ShortestPath(6, 0);
    cout << endl;
    Graph G3(6);
    G3.Setup();
    G3.ShortestPath(6, 0);
    cout << endl;    
    // (b)
    cout << "Part b" << endl; 
    Graph G4(7);
    G4.Setup();
    G4.BellmanFord(7, 0);
    cout << endl; 
    Graph G5(3);
    G5.Setup();
    G5.BellmanFord(3, 0);
    cout << endl; 
    // (c)
    cout << "Part c" << endl;
    Graph G6(3);
    G6.Setup();
    G6.AllLength(3);
    cout << endl;
    Graph G7(7);
    G7.Setup();
    G7.AllLength(7);
    cout << endl;
}