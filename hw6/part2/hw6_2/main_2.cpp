#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// function 

int h(string s)
{
    return s[0] - 'a';
}


// Linear Probing Part

class LinearProbing
{
public:
    LinearProbing()
    {
        cin >> n;
        for(int i = 0; i < n; i++)
        {
            string tmp;
            cin >> tmp;
            Insert(tmp);
        }
    };
    void Insert(string s);
    string Get(const string k);
    void Print()
    {
        for(int i = 0; i < b; i++)
        {
            cout << i << ": " << ht[i] << endl;
        }
    };
private:
    string ht[26] = {""};
    int b = 26;
    int n;
};

void
LinearProbing::Insert(string s)
{
    int i = h(s);
    int j;
    for(j = i; ht[j] != "" && ht[j] != s;)
    {
        j = (j+1) % b;
        if(j == i) return;
    }
    if(ht[j] == "") ht[j] = s;
    return; 
}

string
LinearProbing::Get(const string k)
{
    int i = h(k);
    int j;
    for(j = i; ht[j] != "" && ht[j] != k;)
    {
        j = (j+1) % b;
        if(j == i) return "No search";
    }
    if(ht[j] == k) return ht[j];
    return "No search";
}

// Chain Part

class ChainNode
{
public:
    ChainNode(string k)
    {
        data = k;
        link = NULL;
    };
    string data;
    ChainNode* link; 
};

class Chaining
{
public:
    Chaining()
    {
        int n;
        cin >> n;
        for(int i = 0; i < n; i++)
        {
            string tmp;
            cin >> tmp;
            Insert(tmp);
        }
    };
    void Insert(string k);
    string Get(const string k);
    void Print()
    {
        for(int i = 0; i < 26; i++)
        {
            cout << "[" << i << "] -> ";
            ChainNode* now = ht[i];
            while(now)
            {
                cout << now->data << " -> ";
                now = now->link;
            }
            cout << "0" << endl;
        }
    };
private:
    ChainNode* ht[26] = {NULL};
};

void
Chaining::Insert(string k)
{
    int i = h(k);
    ChainNode* now = new ChainNode(k);
    now->link = ht[i];
    ht[i] = now;     
}

string
Chaining::Get(const string k)
{
    int i = h(k);
    for(ChainNode* current = ht[i]; current != NULL; current = current = current->link)
        if(current->data == k) return current->data;
    return "No search"; 
}

int main()
{
    int num;
    // Part1
    cout << "LinearProbing" << endl;
    LinearProbing d1;
    cout << endl;

    cout << "Demo:" << endl;
    d1.Print();
    cout << endl;

    cout << "Get how many keys: ";
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        string tmp;
        cout << "What do you want to search: ";
        cin >> tmp;
        cout << "d1.Get(" << tmp << ") = " << d1.Get(tmp) << endl;     
    }
    cout << endl;

    // Part2
    cout << "Chaining" << endl; 
    Chaining d2;
    cout << endl;

    d2.Print();
    cout << endl;

    cout << "Get how many keys: ";
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        string tmp;
        cout << "What do you want to search: ";
        cin >> tmp;
        cout << "d2.Get(" << tmp << ") = " << d2.Get(tmp) << endl;     
    }

    cout << endl;

}

/*
12
ga
d
a
g
l
a2
a1
a3
a4
z
za
e
*/