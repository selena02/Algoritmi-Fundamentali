class Solution {
public:
    int cnt=0;
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> la;
        vector<int>order;
        vector<int> d;
        d.resize(numCourses);
         for(int i=0; i<numCourses; i++)// grad intern
            d[i]=0; 
    int x,y,ok,apel;
    order.reserve(numCourses);
    if(numCourses>1 && prerequisites.size()!=0)
    {
        la.resize(numCourses+1);
        for(int i=0; i<prerequisites.size(); i++)
        {
            x=prerequisites[i][0];
            y=prerequisites[i][1];
            la[y].push_back(x);
            d[x]++;      // calculez gradul intern al lui x
        }


        queue<int>c;
        for(int i=0; i<numCourses; i++)
            if(d[i]==0)
                c.push(i); // pun in coada toate nodurile cu grad intern 0 adica fara cele dependente, adica cicluri
        cnt=0;
        while(c.size()!=0)
        {
            int node=c.front();
            c.pop();
            cnt++;
            order.push_back(node);
            for(int v=0; v<la[node].size(); v++)
            {
                int y=la[node][v];
                d[y]--;           // de fiecare data cand gasim o muche spre acel nod ii scade gradul, nodul fiind eliminat din graf inainte
                if(d[y]==0)
                    c.push(y);
            }

        }

    }

        else if(numCourses==1)order.push_back(0);

        if(numCourses>1 && order.size()<numCourses && cnt!=numCourses) // au ramas niste cursuri fara dependente, le adaugam si pe acestea in sortarea topologica
        {
            for(int i=0; i<numCourses; i++)
                if (count(order.begin(), order.end(),i)==0)
                    order.push_back(i);

        }
        if(cnt!=numCourses&&prerequisites.size()>1)order.clear(); // nu exista sortare topologica

        return order;
    }
};
