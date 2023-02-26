// complexitate: n^2

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#define inf 1000001
using namespace std;
ifstream fin("retea2.in");
ofstream fout("retea2.out");
struct punct
{
    double x,y;
};
double calculeaz_distanta(punct a, punct b)
{
    double distanta = sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
    return distanta;
}
int main()
{
    int N,M;
    fin>>N>>M;
    vector <bool> vizitat ;
    vector <double> distanta ;
    vector <punct> centrale;
    vector <punct> blocuri;
    int a,b;
    distanta.resize(M+1);
    vizitat.resize(M+1);
    double total=0;
    for(int i=0; i<M+N; i++)
    {
        fin>>a>>b;

        if (i<N)
        {

            centrale.push_back(punct());
            centrale[i].x=a;
            centrale[i].y=b;
        }
        else
        {

            blocuri.push_back(punct());
            blocuri[i-N].x=a;
            blocuri[i-N].y=b;
            distanta[i-N]=inf;
            vizitat[i-N]=false;
        }
    }

    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            double d=calculeaz_distanta(blocuri[i],centrale[j]);
            if(d<distanta[i])
                distanta[i]=d;
        }
    }
    for(long i=0; i<M; i++)
    {

        double cost = inf;
        long pozitie = 0;
        for(long j=0; j<M; j++)
            if(vizitat[j]==false && distanta[j] < cost)
            {
                cost = distanta[j];
                pozitie = j;
            }
        vizitat[pozitie]=true;
        total+=cost;

        for(long j=0; j<M; j++)
        {
            if(vizitat[j]==false && distanta[j]>calculeaz_distanta(blocuri[pozitie],blocuri[j]))
                distanta[j]=calculeaz_distanta(blocuri[pozitie],blocuri[j]);
        }

    }
    fout << fixed << setprecision(6) << total;
    return 0;

}
