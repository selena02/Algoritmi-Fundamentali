#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin ("bfs.in");
using namespace std;
vector<vector<int>> la;
vector<int> viz;
vector<int>d;
vector<int> puncte;
vector<int>minim;
void bfs( int &s, vector<vector<int>>la)
{

    int u,y;
    queue<int>c;
    c.push(s);
    viz[s]=1;
    d[s]=0;
    while(c.size()!=0)
    {

        u=c.front();
        c.pop();
        for(int v=0; v<la[u].size(); v++)
        {
            y=la[u][v];
            if (viz[y]==0)
            {
                c.push(y);
                viz[y]=1;
                d[y]=d[u]+1;
            }
        }
    }
}

int main()
{
    int n, m, x, y, s;
    fin>>n>>m;
    puncte.reserve(n+1);
    viz.resize(n+1);
    la.resize(n+1);
    d.resize(n+1);
    minim.resize(n+1);
    for(int i=0; i<=n; i++)
    {
        minim[i]=n;
    }
    for (int i=0; i<m; i++)
    {
        fin>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }
    while(fin>>x)
    {

        puncte.push_back(x);

    }

    for(int i=0; i<puncte.size(); i++)
    {
        bfs(puncte[i],la);
        for(int i = 1; i<=n; i++)
            if(d[i]<minim[i])
                minim[i]=d[i];
        for(int i=0; i<n; i++)
        {
            d[i]=0;
            viz[i]=0;
        }
    }
    for(int i=1; i<=n; i++)
        cout<<minim[i]<<" ";

    return 0;
}
