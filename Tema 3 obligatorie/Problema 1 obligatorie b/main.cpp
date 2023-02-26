//O(n^2*m^2)
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>
#include<string.h>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

int N, M, s, f;
vector<vector<int>> capacitate;
vector<int> tata;
vector<vector<int>> LA;
vector<vector<int>> capacitate_rez;
vector<vector<int>> LA_rez;
vector<bool>visited;
bool bfs(int s, int t)
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
        for(auto v: LA_rez[u])
        {
            if(viz[v]==false && capacitate_rez[u][v]!=0)
            {
                tata[v] = u;
                if(v == t)
                    return true;
                viz[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}
void dfs(int s)
{
    visited[s] = true;
    for (int i = 0; i < N; i++)
        if (capacitate_rez[s][i] && !visited[i])
            dfs(i);
}
void mincut(int s, int t)
{

    LA_rez=LA;
    capacitate_rez=capacitate;
    while(bfs(s,t)==true)
    {
        int u, v, path_flow = INT_MAX;
        v=t;
        while(v != s)
        {
            u = tata[v];
            if(capacitate[u][v] < path_flow)
                path_flow = capacitate_rez[u][v];
            v = tata[v];
        }
        v=t;
        while(v != s)
        {
            u = tata[v];
            capacitate_rez[u][v] -= path_flow;
            capacitate_rez[v][u] += path_flow;
            v = tata[v];
        }
    }
    visited.resize(N+1);
    for(int i=0; i<=N;i++)
        visited[i]=false;
     dfs(s);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
                if (visited[i] && !visited[j] && capacitate[i][j])
                cout << i << " -> " << j << endl;

}

int main()
{
    fin >> N >> M;
    s = 1;
    f = N;
    LA.resize(N+1);
    tata.resize(N+1);
    capacitate.resize(N+1, vector<int>(N+1));
    LA_rez.resize(N+1);
    capacitate_rez.resize(N+1, vector<int>(N+1));
    for(int i = 1; i <= M; i++)
    {
        int a, b;
        long c;
        fin >> a >> b >> c;
        LA[a].push_back(b);
        LA[b].push_back(a);
        capacitate[a][b] = c;
    }
    int sursa=1;
    for(int nod=2; nod<=N; nod++)
        {
            cout<<"Pentru a ajunge la nodul : "<<nod<<endl;
            mincut(sursa, nod);
        }
    return 0;
}
