// complexitate: O(mlogn)

vector <int> tata(100001,-1);
int find(int x)
{
    if(tata[x]==x) return x;
    return tata[x] = find(tata[x]);
}
void union(int a, int b)
{
    a = find(a);
    b = find(b);

    if(a!=b) tata[b] = a;
}
bool sort_distanta( vector<int>& v1,vector<int>& v2)
{
    return v1[2] < v2[2];
}
class Solution
{
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edges, vector<vector<int>>& queries)
    {
        for(int i = 0; i<=n; i++) tata[i] = i;

        sort(edges.begin(),edges.end(),sort_distanta);
        for(int i = 0; i<queries.size(); i++)
            queries[i].push_back(i);
        sort(queries.begin(),queries.end(),sort_distanta);
        vector <bool> rezultat(queries.size(),false);
        int poz = 0;
        for(int i = 0; i<queries.size(); i++)
        {

            while(poz<edges.size() and edges[poz][2]<queries[i][2])
            {
                union(edges[poz][0],edges[poz][1]);
                poz++;
            }

            if(find(tata[queries[i][0]]) == find(tata[queries[i][1]]))
             rezultat[queries[i][3]] = true;
        }
        return rezultat;
    }

};
