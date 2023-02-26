#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;
ifstream fin("curs.in");
vector <vector<int>>la;
vector <int> d;
vector <int> order;
vector <int> viz;
vector <int> tata;
vector <int> finalizare;
vector <int> ciclu;
int numCourses;
void dfs(int x)
{
    viz[x]=1;
    for(int i=0; i<la[x].size(); i++)
    {
        int y = la[x][i];
        if(viz[y]==0)
        {
            tata[y]=x;
            dfs(y);
        }

        else
        {
            if(finalizare[y]==0) // se gaseste o muchie de intoarcere y gri de explorare in stiva
            {
                int v=x;
                while(v!=y)
                {

                    ciclu.push_back(v);
                    v=tata[v];
                }
                ciclu.push_back(y);
                ciclu.push_back(x);
            }
        }
    }
    finalizare[x]=1;
}

vector<int>cicluri()
{
    dfs(0);
    if(ciclu.size()==0) return ciclu;

    for(int i=ciclu.size()-1; i>=0; i--)
    {
        cout<<ciclu[i]<<" ";

        if(ciclu[i]==ciclu[ciclu.size()-1]&&i!=ciclu.size()-1)
            break;
    }

    return ciclu;
}
int main()
{
    int x,y;
    fin>>numCourses;
    la.resize(numCourses+1);
    viz.resize(numCourses+1);
    tata.resize(numCourses+1);
    finalizare.resize(numCourses+1);
    for(int i=0; i<=numCourses; i++)
    {
        tata[i]=-1;
        viz[i]=0;
        finalizare[i]=0;
    }
    while(fin>>x>>y)
    {
        la[y].push_back(x);
    }
    cicluri();
    return 0;
}
