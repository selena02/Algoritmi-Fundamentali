//O(V+E)
#include <iostream>
#include <fstream>
#include <vector>
#include<climits>
using namespace std;
ifstream fin("edges.in");
vector<vector<int>> la;
vector <int> in;
vector <int> out;
vector<int> eulerian_path;
void dfs_eulerian(int nod)
{
    while(out[nod]!=0)
    {

        for(auto next:la[nod])
        {
            out[nod]--;
            dfs_eulerian(next);
        }
    }
    eulerian_path.insert(eulerian_path.begin(), nod);
}
int main()
{
    la.resize(100);
    int a,b,start=-1;
    in.resize(100,0);
    out.resize(100,0);
    int max=-1;
    while(fin>>a>>b)
    {
        la[a].push_back(b);
        in[b]+=1;
        out[a]+=1;
        if(a>max)
            max=a;
        if(b>max)
            max=b;
    }
    for(int i=0; i<=max; i++)
    {
        if(out[i]-in[i]==1)
        {
            start=i;
            break;
        }
    }
    if(start==-1)
    {
        start=max;
    }
    dfs_eulerian(start);
    for(auto i: eulerian_path)
        cout<<i<<" ";

    return 0;
}
