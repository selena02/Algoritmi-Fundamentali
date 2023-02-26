// complexitate: O(mlogn)

#include <iostream>
#include <vector>
#include <fstream>
#include<algorithm>
using namespace std;

ifstream fin("online.in");
ofstream fout("online.out");

int n, m, k, costMin = 0;
vector<int>tata,inaltime;
struct Muchie
{
    int nodSursa, nodDest, distanta;
};
vector<Muchie> listaAdiacenta,rezultat;

bool ord(Muchie a, Muchie b)
{
    return a.distanta < b.distanta;
}

int find(int x)
{
    if(tata[x] == x)
        return x;
    tata[x] = find(tata[x]);
    return tata[x];
}

void Union(int u, int v)
{
    int reprezentantU=find(u);
    int reprezentantV=find(v);
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


void Kruskal()
{

    for(int i = 0; i < m; i++)
    {
        if(find(listaAdiacenta[i].nodSursa) != find(listaAdiacenta[i].nodDest))
        {
            costMin += listaAdiacenta[i].distanta;
            Union(listaAdiacenta[i].nodSursa, listaAdiacenta[i].nodDest);
            rezultat.push_back({listaAdiacenta[i].nodSursa, listaAdiacenta[i].nodDest, listaAdiacenta[i].distanta});
        }
    }
}


int main()
{
    fin>>n>>m;
    tata.resize(n);
    inaltime.resize(n);
    Muchie muchie;
    for(int i = 1; i <= m; i++)
    {
        fin>>muchie.nodSursa>>muchie.nodDest>>muchie.distanta;
        listaAdiacenta.push_back(muchie);
    }
   
    sort(listaAdiacenta.begin(), listaAdiacenta.end(), ord);

    Kruskal();

    fout<<costMin<<"\n";
    listaAdiacenta = rezultat;

    fin>>k;
    for(int i=0; i<k; i++)
    {
        rezultat.clear();
        fin>>muchie.nodSursa>>muchie.nodDest>>muchie.distanta;
        if(muchie.distanta < listaAdiacenta.back().distanta)
        {
            costMin = 0;

            tata.resize(n);
            inaltime.resize(n);
            for(int i=1; i<=n; i++)
            {
                tata[i]=i;
                inaltime[i]=0;
            }

            listaAdiacenta.push_back(muchie);
            sort(listaAdiacenta.begin(), listaAdiacenta.end(), ord);
            Kruskal();
            listaAdiacenta = rezultat;
        }
        fout<<costMin<<"\n";
    }
    return 0;
}
