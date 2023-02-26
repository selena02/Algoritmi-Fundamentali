//Time: O( nm )
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {

    int n = text1.length()+1;
    int m = text2.length()+1;
    int matrice [n][m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            if(i==0)matrice[0][j]=0;
            else if(j==0)matrice[i][0]=0;
            else
            {
                if(text2[j-1]==text1[i-1])
                    matrice[i][j]=1+matrice[i-1][j-1];
                else matrice[i][j]=max(matrice[i-1][j],matrice[i][j-1]);
            }
        }
     return(matrice[n-1][m-1]);
    }
};
