//  O(m)
#include<fstream>
#include<iostream>
#include<vector>
#define MAXN 50010

using namespace std;

ifstream fin("johnie.in");
ofstream fout("johnie.out");

vector <pair <int, int> > v[MAXN];

int viz[MAXN], grad[MAXN], c[MAXN], cr[MAXN], s[200010], mc[100010];
int  semafor[100010];
int i, j, k, l;
int x, y, t;
int nj, lungime, start, vf;
int nod, nod1, nod2;
int nr, nrr;

int gt[100010], fix[100010];
int gtt[MAXN];

void DFS(int nod, int& k) {
    viz[nod] = 1;
    k++;
    c[k] = nod;
    for (int i = 0; i < v[nod].size(); i++)
        if (viz[v[nod][i].first] == 0)
            DFS(v[nod][i].first, k);
}


int main() {
    int n, m;
    fin >> n >> m;
    for (i = 1; i <= m; i++) {
        fin >> x >> y;
        v[x].push_back(make_pair(y, i));
        v[y].push_back(make_pair(x, i));
        grad[x]++;
        grad[y]++;
    }


    for (k = 1; k <= n; k++) {
        if (viz[k] == 0) {
            nr = 0;
            DFS(k, nr);
            j = 0;
            nj = 0;
            for (i = 1; i <= nr; i++) {
                if (grad[c[i]] == 0)
                    nj++;
                if (grad[c[i]] % 2 == 1)
                    j++;
            }
            j = j / 2;
            if (j == 0 && nj != nr)
                j++;
            nrr = nrr + j;
        }
    }
    fout << nrr << '\n';


    for (i = 1; i <= n; i++)
        viz[i] = 0;

    int nr_muchii;
    for (k = 1; k <= n; k++) {
        if (viz[k] == 0) {
            nr_muchii = m;
            nr = 0;
            DFS(k, nr);
            i = 1;
            start = -1;
            nod = -1;
            while (i <= nr) {
                while (i <= nr && grad[c[i]] % 2 == 0)
                    i++;
                nod1 = c[i];
                i++;
                while (i <= nr && grad[c[i]] % 2 == 0)
                    i++;
                nod2 = c[i];
                i++;
                nr_muchii++;
                if (i - 1 <= nr) {
                    v[nod1].push_back(make_pair(nod2, nr_muchii));
                    v[nod2].push_back(make_pair(nod1, nr_muchii));
                    nod = nod1;
                }
            }
            vf = 1;
            if (nod == -1)
                nod = k;
            s[vf] = nod;
            j = 0, t = 0;
            if (nr > 1) {
                while (vf > 0) {
                    x = s[vf];
                    while (cr[x] < v[x].size() && semafor[v[x][cr[x]].second] == 1)
                        cr[x]++;
                    if (cr[x] >= v[x].size()) {
                        j++;
                        gt[j] = x;
                        if (mc[vf] > m) {
                            t++;
                            fix[t] = j;
                            start = 1;
                        }
                        vf--;
                    }
                    else {
                        semafor[v[x][cr[x]].second] = 1;
                        vf++;
                        s[vf] = v[x][cr[x]].first;
                        mc[vf] = v[x][cr[x]].second;
                    }
                }
                if (start == -1) {
                    fout << j << " ";
                    for (i = 1; i <= j; i++)
                        fout << gt[i] << " ";
                    fout << endl;
                }
                else {
                    for (i = 2; i <= t; i++) {
                        lungime = fix[i] - fix[i - 1];
                        fout << lungime << " ";
                        for (l = fix[i - 1] + 1; l <= fix[i]; l++)
                            fout << gt[l] << " ";
                        fout << '\n';
                    }
                    fout << j - fix[t] << " ";
                    for (l = fix[t] + 1; l <= j; l++)
                        fout << gt[l] << " ";
                    fout << '\n';
                }
            }
        }
    }
    return 0;
}
