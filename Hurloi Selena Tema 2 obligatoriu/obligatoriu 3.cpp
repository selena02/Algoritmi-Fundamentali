// complexitate: n^2

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <queue>
#define inf 1000001
using namespace std;
ifstream fin("cuvinte.in");
vector <string> cuvinte;
vector <bool>   vizitat;
vector <int>    tata;
vector <int>    distanta;
priority_queue<int>pq;
vector <vector<int>> lista_adiacenta;
vector <bool> vizitat_dfs;
int LevenshteinDistance(string a, string b)
{
    int n=strlen(a.c_str())+1;
    int m=strlen(b.c_str())+1;
    int matrice[n][m] = {};
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            if(i==0)matrice[0][j]=j;
            else  if(j==0)matrice[i][0]=i;
            else
            {
                int sterge, insereaza,inlocuieste,nou;
                insereaza=matrice[i-1][j];
                inlocuieste=matrice[i-1][j-1];
                sterge=matrice[i][j-1];
                int aux=min(insereaza,inlocuieste);
                nou=min(aux,sterge);
                if(b[j-1]==a[i-1])
                    matrice[i][j]=inlocuieste;
                else matrice[i][j]=nou+1;
            }
        }
    return matrice[n-1][m-1];
}
void DFS(int x)
{
    vizitat_dfs[x]=1;
    cout<<cuvinte[x]<<" ";
    for(int i=0; i<lista_adiacenta[x].size(); i++)
    {
        int y = lista_adiacenta[x][i];
        if(vizitat_dfs[y]==0)
        {

            DFS(y);
        }
    }
}
int main()
{
    string cuvant;

    while(fin>>cuvant)
    {
        cuvinte.push_back(cuvant);
        vizitat.push_back(false);
        tata.push_back(0);
        distanta.push_back(inf);
    }
    int k;
    cout<<"In cate clustere se va separa?: ";
    cin>>k;
    distanta[0]=0;
    tata[0]=0;
    for(int i=0; i<cuvinte.size(); i++)
    {
        int distanta_minima=inf;
        int nod_minim;
        for(int j=0; j<cuvinte.size(); j++)
        {
            if(distanta_minima>distanta[j]&&vizitat[j]==false)
            {
                nod_minim=j;
                distanta_minima=distanta[j];
            }
        }
        pq.push(distanta_minima);
        vizitat[nod_minim]=true;
        for(int j=0; j<cuvinte.size(); j++)
        {
            int distanta_curenta=LevenshteinDistance(cuvinte[j],cuvinte[nod_minim]);
            if(distanta_curenta<distanta[j]&&vizitat[j]==false)
            {
                distanta[j]=distanta_curenta;
                tata[j]=nod_minim;

            }
        }
    }
    int cnt=1;
    lista_adiacenta.resize(cuvinte.size());
    for(int i=0; i<cuvinte.size(); i++)
    {
        vizitat_dfs.push_back(false);
        int a = i;
        int b = tata[i];
        if (distanta[i]==pq.top() && cnt<k)
        {
            cnt++;
            pq.pop();
        }
        else
        {
            if(a!=b)
            {
                lista_adiacenta[a].push_back(b);
                lista_adiacenta[b].push_back(a);
            }
        }
    }
    for(int i=0; i<cuvinte.size(); i++)
    {
        if(vizitat_dfs[i]==false)
        {
            DFS(i);
            cout<<"\n";
        }
    }
    int grad_sep=pq.top();
    cout<<grad_sep;

    return 0;
}
