class Solution
{
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {
        vector<vector<int>> la;
        la.resize(n+1);
        for (int i=0; i<dislikes.size(); i++)
        {
            int a = dislikes[i][0];
            int b = dislikes[i][1];
            la[a].push_back(b);
            la[b].push_back(a);
        }

        vector <int> group;
        group.resize(n+1);
        for(int i=0; i<n; i++)
        {
            group[i]=0;
        }
        int u,y;
        queue<int>c;
        c.push(1);
        group[1]=1;
        while(c.size()!=0)
        {
            u=c.front();
            c.pop();
            for(int v=0; v<la[u].size(); v++)//bfs
            {
                y=la[u][v];
                if (group[y]==0) // daca nu face parte din niciun grup
                {
                    c.push(y);
                    if(group[u]==1) // daca tatal lui face parte din grupul 1, atunci nodul y va fi repartizat in grupul 2
                        group[y]=2;
                    else if (group[u]==2) // invers
                        group[y]=1;
                }
                else if(group[y]==group[u]) // se gasesc doua noduri de tipul tata-fiu care fac parte din acelasi grup => nu se poate
                {
                    return false;
                }
                else if(c.size()==0 &&u<n && group[u+1]==0) // trece la urmatoarea componenta conexa, in cazul in care mai sunt noduri fara repartitie in grup
            {
                u=u+1;
                group[u]=1;
                c.push(u);

            }
               

            }
        }
        return true;


    }
};
