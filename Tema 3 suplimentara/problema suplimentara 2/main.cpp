// O(M* (N+M) )
#include <queue>
#include <vector>
#include <cstring>
#include <climits>
#include <fstream>

using namespace std;

ifstream fin("drumuri2.in");
ofstream fout("drumuri2.out");

#define N_MAX  202
#define M_MAX  5001
#define INFINITY INT_MAX

int N, M, src, dest, max_flux;
bool visited[N_MAX];
vector<int> neighbors[N_MAX];
int parent[N_MAX], flux[N_MAX][N_MAX], capacity[N_MAX][N_MAX];

bool BFS() {
	int node;
	queue<int> queue;

	memset(visited, false, N_MAX * sizeof(visited[0]));
	queue.push(src);

	while (!queue.empty()) {
		node = queue.front();
		queue.pop();

		for (auto neigh : neighbors[node]) {
			if (!visited[neigh] && capacity[node][neigh] - flux[node][neigh] > 0) {
				queue.push(neigh);
				parent[neigh] = node;
				visited[neigh] = true;
			}
		}
	}

	return visited[dest];
}

int main() {
	int x, y;

	fin >> N >> M;
	src  = 0;
	dest = 2 * N + 1;

	for (int i = 0; i < M; ++i) {
		fin >> x >> y;

		capacity[x][N + y] = 1;
		neighbors[x].push_back(N + y);
		neighbors[N + y].push_back(x);
	}

	for (int i = 1; i <= N; ++i) {
         capacity[src][i] = 1;
		neighbors[src].push_back(i);

		 capacity[N + i][dest] = 1;
		neighbors[N + i].push_back(dest);

         capacity[N + i][i] = 1;
        neighbors[N + i].push_back(i);
		neighbors[i].push_back(N + i);
    }

	for (max_flux = 0; BFS();) {
		int min_flux = INFINITY;

		for (int node = dest; node != src; node = parent[node]) {
			min_flux = min(min_flux, capacity[parent[node]][node] - flux[parent[node]][node]);
		}

		for (int node = dest; node != src; node = parent[node]) {
			flux[parent[node]][node] += min_flux;
			flux[node][parent[node]] -= min_flux;
		}

		max_flux += min_flux;
	}

	fout << N - max_flux;

	return 0;
}
