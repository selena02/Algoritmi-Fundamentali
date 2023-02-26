// complexitate: mlogn

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end)
    {
        vector<vector<pair<int,double>>> lista_adiacenta;
        lista_adiacenta.resize(n);
        for(int i=0; i<edges.size(); i++)
        {
            lista_adiacenta[edges[i][0]].push_back({edges[i][1], succProb[i]});
            lista_adiacenta[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        vector<double>distanta{};
        distanta.resize(n);
        distanta[start]=1;
        priority_queue<pair<double,int>> pq;
        pq.push({1,start});
        while (pq.empty()==false)
        {
            int u = pq.top().second;
            double probabilitate =pq.top().first;
            pq.pop();
            if (u==end)
                return(probabilitate);
            for(auto i:lista_adiacenta[u])
            {
                int nod =i.first;
                double probabilitate_nod =i.second;
                if(distanta[u]*probabilitate_nod > distanta[nod])
                {
                    distanta[nod]=distanta[u]*probabilitate_nod;
                    pq.push({distanta[nod],nod});
                }
            }

        }
        return 0;
    }

};
