//O((N∗(2N))∗N)
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {

        int n= graph.size();
        int final_mask=(1<<n)-1;
        int i,j,ans=0;
        queue<vector<int>>q; // pentru bfs
        set<pair<int,int>>s; // un fel de viz
        vector<int>v(3,0);
        //pornim cu bfs din toate nodurile
        for(i=0;i<n;i++)
        {
            int mask=(1<<i); // scriem in binar
            int node=i;
            int cost=0;      // lungimea path ului
            v[0]=cost;
            v[1]=node;
            v[2]=mask;
            q.push(v);
            s.insert({node,mask});
        }

        //bfs
        while(q.size()>0)
        {
            auto curent=q.front();
            q.pop();

            if(curent[2]==final_mask)  // am vizitat toate nodurile stim cand ajungem la 11...11 in functie de n
            {
                ans=curent[0];         // lungimea drumului
                break;
            }

            for(auto j:graph[curent[1]])  //vecinii nodului in graf
            {
                int mask=curent[2]|(1<<j); // actualizam state ul dupa ce vizitam inca un nod

                if(s.find({j,mask})==s.end())  // verificam daca state ul asta a mai fost vizitat ca sa nu avem cicluri un fel de viz mai inteligent
                {
                    s.insert({j,mask});
                    vector<int>v(3,0);
                    v[0]=curent[0]+1;
                    v[1]=j;
                    v[2]=mask;
                    q.push(v);
                }
            }
        }
        return ans;
    }
};
