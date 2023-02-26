//O(MN)
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
    int n = str1.length()+1;
    int m = str2.length()+1;
    int matrice [n][m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            if(i==0)matrice[0][j]=0;
            else if(j==0)matrice[i][0]=0;
            else
            {
                if(str2[j-1]==str1[i-1])
                    matrice[i][j]=1+matrice[i-1][j-1];
                else matrice[i][j]=max(matrice[i-1][j],matrice[i][j-1]);
            }
        }
    string scs="";
    int i=n-1,j=m-1;
    while(i>0 && j>0)
    {
        if(str1[i-1]==str2[j-1])
        {
            scs+=str1[i-1];
            i--;
            j--;
        }
        else if(matrice[i-1][j]>matrice[i][j-1])
        {
            scs+=str1[i-1];
            i--;
        }
        else
        {
            scs+=str2[j-1];
            j--;
        }
    }
    while(i>0)
    {
        scs+=str1[i-1];
        i--;
    }
    while(j>0)
    {
        scs+=str2[j-1];
        j--;
    }
    reverse(scs.begin(),scs.end());
    return(scs);
    }
};
