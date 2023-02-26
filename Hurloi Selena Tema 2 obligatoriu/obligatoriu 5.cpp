// complexitate: mlogn

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
ifstream fin("catun.in");
ofstream fout("catun.out");
vector<vector<pair<int,int>>>lista_adiacenta;
int fortarete[36005];
int distanta[36005];
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
void dijkstra()
{
    while(!pq.empty())
    {
        int u = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        for(auto i : lista_adiacenta[u])
        {
            int cost_vecin = i.first;
            int vecin = i.second;
            if(cost+cost_vecin<distanta[vecin])
            {
                distanta[vecin]=cost+cost_vecin;
                fortarete[vecin]=fortarete[u];
                pq.push({distanta[vecin],vecin});
            }
            else if(cost+cost_vecin == distanta[vecin])
            {
                fortarete[vecin]=min(fortarete[u],fortarete[vecin]);
            }
        }

    }


}
int main()
{
    int n,m,k;
    fin>>n>>m>>k;
    lista_adiacenta.resize(n+1);
    for(int i=1; i<=n; i++)
    {
        distanta[i]=INT_MAX;
    }

    for(int i=0;i<k;i++){
        int fort;
        fin>>fort;
        distanta[fort] = 0;
        fortarete[fort] = fort;
        pq.push({0,fort});
    }

    for(int i=0;i<m;i++){
        int x,y,z;
        fin>>x>>y>>z;
        lista_adiacenta[x].push_back({z,y});
        lista_adiacenta[y].push_back({z,x});
    }

  dijkstra();

    for(int i=1; i<=n; i++)
        if(fortarete[i]!=i)
            fout<<fortarete[i]<<" ";
        else fout<<0<<" ";


    return 0;
}
