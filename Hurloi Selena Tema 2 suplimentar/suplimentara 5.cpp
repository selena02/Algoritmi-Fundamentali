// Complexitate: O(nm)

#include <fstream>
#include <iostream>
#include <queue>
#include <iomanip>
#define Nmax 100000000
using namespace std;

ifstream fin("ciclu.in");
ofstream fout("ciclu.out");

int n, m;
double stanga=0, dreapta=Nmax, mij;
priority_queue<int> coada;
vector<vector<pair<int, int>>> lista_adiacenta;
bool BellmanFord(double m)
{
    int u, v, w;
    vector<double> dist;
    vector<int> nr;
    dist.resize(n+1);
    nr.resize(n+1);
    for(int i=0; i<=n; i++)
    {
        nr[i]=0;
        dist[i]=0;
    }

    for(int i=1; i<=n; i++)
    {
        coada.push(i);
    }

    while (coada.empty()== false)
    {
        u = coada.top();
        coada.pop();

        for (int j = 0; j < lista_adiacenta[u].size(); j++)
        {
            v = lista_adiacenta[u][j].first;
            w = lista_adiacenta[u][j].second - m;
            if (dist[u] < Nmax)
            {
                if(dist[v]>dist[u]+w)
                {
                    coada.push(v);
                    nr[v] = nr[u] + 1;
                    dist[v] = dist[u] + w;
                    if (nr[v] == n)
                        return true;
                }

            }
        }
    }
    return false;

}

int main()
{
    fin >> n >> m;
    lista_adiacenta.resize(n+1);
    for (int i = 1; i <= m; i++)
    {
        int u, v, cost;
        fin >> u >> v >> cost;
        lista_adiacenta[u].push_back({v, cost*100});
    }
    while (stanga < dreapta)
    {
        mij = (stanga + dreapta) / 2;

        if (BellmanFord(mij))
            dreapta = mij - 1;
        else
            stanga = mij + 1;
    }
    fout << fixed << setprecision(2) << stanga/100;

    return 0;
}
