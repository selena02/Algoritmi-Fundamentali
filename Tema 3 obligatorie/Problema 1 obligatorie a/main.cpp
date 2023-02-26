//O(VE^2)
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

int N, M, s, f;
vector<vector<int>> capacitate;
vector<int> tata;
vector<vector<int>> LA;
bool bfs()
{
    vector<bool> viz(N+1);
    queue<int> q;
    q.push(s);
    viz[s] = true;
    tata[s] = -1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(auto v: LA[u])
        {
            if(viz[v]==false && capacitate[u][v]!=0)
            {
                tata[v] = u;
                if(v == f)
                    return true;
                viz[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

int EdmondsKarp()
{
    long max_flow = 0;
    while(bfs()==true)
    {
        int u, v, path_flow = INT_MAX;
        v=f;
        while(v != s)
        {
            u = tata[v];
            if(capacitate[u][v] < path_flow)
                path_flow = capacitate[u][v];
            v = tata[v];
        }
        v=f;
        while(v != s)
        {
            u = tata[v];
            capacitate[u][v] -= path_flow;
            capacitate[v][u] += path_flow;
            v = tata[v];
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main()
{
    fin >> N >> M;
    s = 1;
    f = N;
    LA.resize(N+1);
    tata.resize(N+1);
    capacitate.resize(N+1, vector<int>(N+1));
    for(int i = 1; i <= M; i++)
    {
        int a, b;
        long c;
        fin >> a >> b >> c;
        LA[a].push_back(b);
        LA[b].push_back(a);
        capacitate[a][b] = c;
    }
    fout << EdmondsKarp();
    return 0;
}
