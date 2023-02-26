#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("dfs.in");
vector<vector<int>>la;
bool check_dfs (int x,int n, int viz2[], int per[])
{
    viz2[x]=1;
    for(int i=1; i<n; i++)
    {

        if (viz2[per[i]]==0 && count(la[x].begin(), la[x].end(), per[i])>0)
        {
            check_dfs(per[i],n,viz2, per);
        }

        else if(viz2[per[i]]==0 && count(la[x].begin(), la[x].end(), per[i])==0) return false;
    }

    return true;
}
int main()
{
    int n,m,x,y,nr;
    fin>>n>>m;
    int *viz2,*per;
    viz2=new int[n+1];
    per=new int[n+1];
    for(int i=0;i<=n; i++)
        viz2[i]=0;
    for(int i=0; i<n; i++)
    {
        fin>>nr;
        per[i]=nr;
    }
    la.resize(n+1);
    for(int i=1; i<=m; i++)
    {
        fin>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }

    if(check_dfs(1,n,viz2,per)==true)
        cout<<1;
    else cout<<0;

    return 0;
}
