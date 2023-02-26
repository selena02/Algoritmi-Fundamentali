// complexitate: O(n^2)

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>>& points)
    {
        int n = points.size(), rezultat = 0, i = 0;
        vector<int> distanta_minima(n, 10000000);
        for(int k=1; k<n; k++)
        {
            distanta_minima[i] = INT_MAX;
            int pct_minim= i;
            for (int j = 0; j < n; ++j)
                if (distanta_minima[j] != INT_MAX)
                {
                    distanta_minima[j] = min(distanta_minima[j], abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]));
                    if(distanta_minima[j]<distanta_minima[pct_minim])
                        pct_minim=j;
                }
            rezultat += distanta_minima[pct_minim];
            i = pct_minim;
        }
        return rezultat;
    }
};
