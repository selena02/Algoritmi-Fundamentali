class Solution
{
    int niv [100005] {};
    int niv_minim [100005] {};
    vector <int> la [100005] {};
    vector <vector<int>> result;
    vector <int> gol {};
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {
        for(int i=0; i<connections.size(); i++)
        {
            int x=connections[i][0];
            int y=connections[i][1];
            la[x].push_back(y);
            la[y].push_back(x);
        }

         dfs(0,la);
        return result;
    }
    void dfs (int  u, vector <int> la [])
    {
        niv_minim[u]=niv[u];
        for(int i=0; i<la[u].size(); i++)
        {
            int v=la[u][i];
            if(niv[v]==0)
            {
                niv[v]=niv[u]+1;
                dfs(v,la);
                if(niv_minim[v]>niv[u])
                {
                    gol.push_back(u);
                    gol.push_back(v);
                    result.push_back(gol);
                    gol.clear();
                }
                niv_minim[u]=min(niv_minim[u],niv_minim[v]);
            }
            else if(niv[v]<niv[u]-1)
                niv_minim[u]=min(niv_minim[u],niv[v]);

        }
    }
};
