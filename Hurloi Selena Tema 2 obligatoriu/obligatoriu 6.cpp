// complexitate: O(t(n+m))

#include <fstream>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("easygraph.in");
ofstream fout("easygraph.out");
vector<vector<int>>lista_adiacenta;
long long v[17000],cost_lant[17000];
vector<bool>viz;
void dfs(int x)
{
    viz[x] = 1;
    cost_lant[x] = v[x];

    for (auto nod: lista_adiacenta[x])
    {
        if (!viz[nod])
            dfs(nod);
        cost_lant[x] = max(v[x]+cost_lant[nod],cost_lant[x]);
    }
}
int main()
{
    int t;
    fin>>t;
    for(int i=0;i<t;i++)
    {
        int n,m;
        fin>>n>>m;
        viz.resize(n+1);
        lista_adiacenta.resize(n+1);
        for (int i=1;i<=n;i++)

        {

            lista_adiacenta[i].clear();
            viz[i] = false;
            fin >> v[i];
        }

        for (int i=1;i<=m;i++)

        {
            int x,y;
            fin>>x>>y;
            lista_adiacenta[x].push_back(y);
        }

        for (int i = 1; i<=n; i++)
            if (!viz[i])
                dfs(i);

        long long maxim = LLONG_MIN;
        for (int i = 1; i<=n; i++)
            maxim = max(maxim,cost_lant[i]);
        fout<<maxim<<"\n";
    }



    return 0;
}
