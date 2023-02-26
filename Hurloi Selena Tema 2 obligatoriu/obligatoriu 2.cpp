// complexitate mlogn

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("disjoint.in");
ofstream fout("disjoint.out");
vector<int>tata,inaltime;
int n,m;
int Find(int u)
{
    if(tata[u]==0)
        return u;
    tata[u]=Find(tata[u]);
    return tata[u];
}
void Union(int u,int v)
{
    int reprezentantU=Find(u);
    int reprezentantV=Find(v);
    if(reprezentantU==reprezentantV)
        return ;
    if(inaltime[reprezentantU]>inaltime[reprezentantV])
    {
        inaltime[reprezentantU]+=inaltime[reprezentantV];
        tata[reprezentantV]=reprezentantU;
    }
    else
    {
        inaltime[reprezentantV]+=reprezentantU;
        tata[reprezentantU]=reprezentantV;
    }

}

int main()
{
    fin>>n;
    fin>>m;
    tata.resize(n+1,0);
    inaltime.resize(n+1,0);
    int cod, x, y;
    for(int i=0; i<m; i++)
    {
        fin>>cod>>x>>y;
        if(cod==1)
            Union(x,y);
        else
        {
            if(Find(y)==Find(x))
                fout<<"DA\n";
            else fout<<"NU\n";
        }
    }
   
    return 0;
}
