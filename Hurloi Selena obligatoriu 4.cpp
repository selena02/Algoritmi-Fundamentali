#include <iostream>
#include <vector>
#include <stack>
#include<fstream>
using namespace std;
ifstream fin("ctc.in");
ofstream fout ("ctc.out");
vector<vector<int>> la1;
vector<vector<int>> la2;
vector<int>viz;
stack<int>stiva;
vector<vector<int>>CTC;
int NrCTC;
void DFS(int x)
{
    viz[x]=1;
    for(int i=0; i<la1[x].size(); i++)
    {
        int y = la1[x][i];
        if(viz[y]==0)
        {
            DFS(y);
        }
    }
    stiva.push(x);

}
void DFS_2(int Nod)
{
    viz[Nod] = 2;
    CTC[NrCTC].push_back(Nod);
    for(unsigned int i=0; i<la2[Nod].size(); i++)
    {
        int Vecin = la2[Nod][i];
        if(viz[Vecin]==1)
            DFS_2(Vecin);
    }
}
int main()
{
    int n,m,x,y;
    fin>>n>>m;
    la1.resize(n+1);
    la2.resize(n+1);
    viz.resize(n+1);
    CTC.resize(n+1);
    for(int i=0; i<m; i++)
    {
        fin>>x>>y;
        la1[x].push_back(y);
        la2[y].push_back(x); // construim transpusa
    }

    for(int i=0; i<n; i++)
        viz[i]=0;
    for(int i = 1; i <= n; i++)
    {
        if(!viz[i])
            DFS(i);
    }

    while(!stiva.empty())
    {
        int Nod = stiva.top();
        if (viz[Nod] == 1)
        {
            NrCTC++;
            DFS_2(Nod);
        }
        stiva.pop();
    }

    fout << NrCTC <<"\n";
    for(int i = 1; i <= NrCTC; i++)
    {
        for(int j = 0; j < CTC[i].size(); j++)
            fout << CTC[i][j] <<" ";
        fout<<"\n";
    }

    return 0;
}
