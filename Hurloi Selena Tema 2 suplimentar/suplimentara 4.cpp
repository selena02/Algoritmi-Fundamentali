// Complexitate: O(mlogn)

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

struct Muchie
{
    int nodSursa, nodDest, taxa;
};

vector<Muchie> rezultat;
int n, m,cost1 = 0, cost2 = 0, q;
vector <int> tata,inaltime;


bool ordCost(Muchie m1, Muchie m2)
{
    return m1.taxa < m2.taxa;
}
int find(int x)
{
    if(tata[x] == x)
        return x;
    tata[x] = find(tata[x]);
    return tata[x];
}

void Union(int x, int y)
{
    int a=find(x);
    int b=find(y);
    if(inaltime[a]<inaltime[b])
    {
        inaltime[b]+=inaltime[a];
        tata[a]=b;
    }
    else
    {
        inaltime[a]+=inaltime[b];
        tata[b]=a;
    }
}


void Kruskal(Muchie muchii[])
{
    for(int i = 1; i <= m; i++)
    {
        if(find(muchii[i].nodSursa) != find(muchii[i].nodDest))
        {
            Union(muchii[i].nodSursa, muchii[i].nodDest);
            cost1 += muchii[i].taxa;
            rezultat.push_back({muchii[i].nodSursa, muchii[i].nodDest, muchii[i].taxa});

        }
    }
}


int main()
{
    int x, y;
    fin>>n>>m>>q;


    tata.resize(n);
    inaltime.resize(n);
    for(int i=1; i<=n; i++)
    {
        tata[i]=i;
        inaltime[i]=0;
    }

    Muchie muchii[100005];

    for(int i = 1; i <= m; i++)
        fin>>muchii[i].nodSursa>>muchii[i].nodDest>>muchii[i].taxa;

    sort(muchii + 1, muchii + m + 1, ordCost);

    Kruskal(muchii);

    while(q--)
    {
        fin>>x>>y;
        cost2 = 0;
        tata.resize(n);
        inaltime.resize(n);
        for(int i=1; i<=n; i++)
        {
            tata[i]=i;
            inaltime[i]=0;
        }

        Union(x, y);

        for(int i = 0; i < rezultat.size(); i++)

            if(find(rezultat[i].nodSursa) != find(rezultat[i].nodDest))
            {
                Union(rezultat[i].nodSursa, rezultat[i].nodDest);
                cost2 += rezultat[i].taxa;
            }

        fout<<cost1 - cost2 - 1<<endl;
    }
    return 0;
}
