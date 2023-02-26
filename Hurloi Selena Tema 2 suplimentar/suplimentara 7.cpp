// Complexitate: O(mlogn)

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector< vector<pair<int,int>>> lista_adiancenta;
        lista_adiancenta.resize(n);
        for(auto i: flights){
            lista_adiancenta[i[0]].push_back({i[1],i[2]});
        }

        queue<pair<int,pair<int,int>>> q;
        q.push({0,{src,0}});
        vector<int> dist(n,INT_MAX);
        dist[src] = 0;

        while(!q.empty()){
            auto it = q.front();
            q.pop();
            int stops = it.first;
            int node = it.second.first;
            int cost = it.second.second;
            for(auto itr: lista_adiancenta[node]){
                int Node = itr.first;
                int dis_min = itr.second;

                if(cost + dis_min < dist[Node] && stops <= k)
                {
                    dist[Node] = cost + dis_min;
                    q.push({stops+1,{Node,cost + dis_min}});
                }
            }
        }

        if(dist[dst] == INT_MAX) return -1;
        return dist[dst];
    }
};
