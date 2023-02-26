#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin ("bfs.in");
vector <int> group;
vector<vector<int>> repartizari;
vector<vector<int>> la;

void bfs( int s, vector<vector<int>> la, vector<int>& group, int& n)
{
    int u,y;
    queue<int>c;
    c.push(1);
    group[1]=1;
    repartizari[0].push_back(1);
    while(c.size()!=0)
    {
        u=c.front();
        c.pop();
        for(int v=0; v<la[u].size(); v++)
        {
            y=la[u][v];
            if (group[y]==0)
            {
                c.push(y);
                if(group[u]==1)
                {
                    repartizari[1].push_back(y);
                    group[y]=2;
                }

                else if (group[u]==2)
                {
                    repartizari[0].push_back(y);
                    group[y]=1;
                }

            }
            else if(group[y]==group[u])
            {
                cout<<"nu se poate";
            }
            else if(c.size()==0 &&u<n && group[u+1]==0)
            {
                u=u+1;
                group[u]=1;
                c.push(u);

            }

        }
    }

}
int main()
{
    int n, m, x, y;
    fin>>n>>m;

    group.resize(n+1);
    la.resize(n+1);
    for(int i=0; i<n; i++)
    {
        group[i]=0;
    }
    for (int i=0; i<m; i++)
    {
        fin>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }
    repartizari.resize(3);
    bfs(1,la,group,n);

    for(int i=0; i<2; i++)
    {
        cout<<"grupa "<<i+1<<": ";
        for(int j=0; j<repartizari[i].size(); j++)
            cout<<repartizari[i][j]<<" ";
            cout<<endl;
    }

    return 0;
}
