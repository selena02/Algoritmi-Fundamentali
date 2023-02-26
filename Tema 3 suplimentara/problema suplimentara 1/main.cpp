//  O(n*m*m*log2n)
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
ifstream f("fmcm.in");
ofstream g("fmcm.out");
int n,s,d,m,tata[351],cost[351][351],capacitate[351][351],flux;
bool inCoada[351];
int distanta[351],distantaInit[351],distantaNoua[351];
queue<int> coada;
vector<int> adiacenta[351];
priority_queue<pair<int,int>> p;
void bellmanford(){
    for (int i = 0; i <= n; ++i) {
        distantaInit[i]=INT_MAX;
    }
    coada.push(s);
    inCoada[s]=true;
    distantaInit[s]=0;
    while(!coada.empty()){
        int nod=coada.front();
        coada.pop();
        inCoada[nod]=false;
        for(int i:adiacenta[nod]){
            if(capacitate[nod][i] && distantaInit[nod]+cost[nod][i] < distantaInit[i]){
                distantaInit[i]=distantaInit[nod]+cost[nod][i];
                if(!inCoada[i]){
                    coada.push(i);
                    inCoada[i]=true;
                }
            }
        }
    }

}
bool dijkstra(){
    for (int i = 0; i <= n; ++i) {
        distanta[i]=INT_MAX;
    }

    distanta[s]=0;
    distantaNoua[s]=0;
    p.push({0,s});
    while (!p.empty()){
        int costCurent = -p.top().first;
        int nod = p.top().second;
        p.pop();
        if(distanta[nod]!=costCurent){
            continue;
        }
        for(int i:adiacenta[nod]){
            if(capacitate[nod][i]){
                int dist=costCurent+cost[nod][i];
                dist+=distantaInit[nod]-distantaInit[i];
                if(dist<distanta[i]){
                    distanta[i]=dist;
                    distantaNoua[i]=distantaNoua[nod]+cost[nod][i];
                    tata[i]=nod;
                    p.push({-distanta[i],i});
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        distantaInit[i]=distantaNoua[i];
    }
    if(distanta[d]==INT_MAX){
        return false;
    }

    int minim=INT_MAX,sol=0;
    int nod=d;
    while(nod!=s){
        minim=min(minim,capacitate[tata[nod]][nod]);
        sol+=cost[tata[nod]][nod];
        nod=tata[nod];
    }
    flux+= sol * minim;
    nod=d;
    while(nod!=s){
        capacitate[tata[nod]][nod]-=minim;
        capacitate[nod][tata[nod]]+=minim;
        nod=tata[nod];
    }
    return true;

}
int main() {

    f>>n>>m>>s>>d;
    int a,b,c,e;
    for (int i = 0; i < m; ++i) {
        f>>a>>b>>c>>e;
        adiacenta[a].push_back(b);
        adiacenta[b].push_back(a);
        capacitate[a][b]=c;
        cost[a][b]=e;
        cost[b][a]=-e;
    }
    bellmanford();
    while (dijkstra());
    g<<flux;
    return 0;
}
