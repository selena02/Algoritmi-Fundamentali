//O(VE^2)
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;
ifstream fin("harta.in");
ofstream fout("harta.out");
vector<vector<int>> LA;
int capacitate[201][201];
vector<int> tata;
int n,s,t;
bool bfs()
{
    vector<bool> viz(2*n+1);
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
                if(v == t)
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
        v=t;
        while(v != s)
        {
            u = tata[v];
            if(capacitate[u][v] < path_flow)
                path_flow = capacitate[u][v];
            v = tata[v];
        }
        v=t;
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
    fin>>n;
    int a,b;
    LA.resize(201);
    tata.resize(2*n+1);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            if(i!=j)
            {
                LA[i].push_back(j+n);
                LA[j+n].push_back(i);
                capacitate[i][j+n]=1;
            }
        }
     s=0;
     t=2*n+1;
    for(int i=1;i<=n; i++)
        {
            fin>>a>>b;
            LA[s].push_back(i);
            LA[i].push_back(s);
            capacitate[s][i]=a;
            LA[i+n].push_back(t);
            LA[t].push_back(i+n);
            capacitate[i+n][t]=b;
        }
        fout << EdmondsKarp()<<"\n";
        for(int i=1; i<=n; i++)
        for(int j=n+1;j<=2*n; j++)
            {
                    if(capacitate[j][i]==1)
                     fout<<i<<" "<<j-n<<"\n";
            }
    return 0;
}

