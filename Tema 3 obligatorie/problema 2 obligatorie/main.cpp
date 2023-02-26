//O(VE^2)
#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;
ifstream fin("cuplaj.in");
ofstream fout ("cuplaj.out");
vector<vector<int>> LA;
vector<vector<int>> capacitate;
vector<int> tata;
int s,t,N,M,E;
bool bfs()
{
    vector<bool> viz(M+N+2);
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
    int a,b;
    fin>>N>>M>>E;
    LA.resize(N+M+2);
    tata.resize(N+M+2);
    capacitate.resize(N+M+2, vector<int>(N+M+2));
    for(int i=1; i<=E; i++)  // creez lista de adiacenta pt graf fara punctele s si t notand elementele din stanga ca fiind b+N pt a le diferentia
        {
            fin>>a>>b;
            LA[a].push_back(b+N);
            LA[b+N].push_back(a);
            capacitate[a][b+N]=1;
        }
        s=0; // punctul de start
        for(int i=1; i<=N; i++)  //adaug punctul de start si muchiile corespunzatoare cate fiecare varf din partea staga si capacitatile
        {
            LA[s].push_back(i);
            LA[i].push_back(s);
            capacitate[s][i]=1;
        }
         t=M+N+1;     // punctul de sink
        for(int i=1; i<= M; i++)
            {
                LA[i+N].push_back(t);
                LA[t].push_back(i+N);
                capacitate[i+N][t]=1;
            }
        fout << EdmondsKarp()<<"\n";
        for(int i=1; i<=N; i++)
        for(int j=N+1;j<=N+M; j++)
            {
                    if(capacitate[j][i]==1)
                     fout<<i<<" "<<j-N<<"\n";
            }
    return 0;
}
