#include <bits/stdc++.h>

using namespace std;

#define MAX_N 1650 // maximum vertices
#define INF 0x3f3f3f3f // must be larger than total capacities

struct edge {
	int to, cap, rev;
	edge (int tt, int cc, int rr) : to(tt), cap(cc), rev(rr) {}
	edge () {}
};

struct Dinic {

	// all index begins at 1

	vector<edge> G[MAX_N];
	int level[MAX_N];
	int iter[MAX_N];

	int source, target;

	// initialize the Dinic
	// n is the total vertices excludes source and target
	void init(int n) {
		// set source and target
		source = n + 1;
		target = n + 2;

		// clear the graph
		for (int i = 0; i <= target; ++ i) 
			G[i].clear();
	}

	void addEdge(int from, int to, int cap) {
		G[from].push_back(edge(to, cap, G[to].size()));
		G[to].push_back(edge(from, 0, G[from].size() - 1));
	}

	// set level caption
	void bfs(int s) {
		for (int i = 0; i <= target; ++ i)
			level[i] = -1;
		queue<int> que;
		level[s] = 0;
		que.push(s);

		while (!que.empty()) {
			int v = que.front();
			que.pop();

			for (int i = 0; i < (int) G[v].size(); ++ i) {
				edge &e = G[v][i];
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}

	// find augmenting path
	int dfs(int v, int f) {
		if (v == target) return f;
		for (int &i = iter[v]; i < (int) G[v].size(); ++ i) {
			edge &e = G[v][i];
			if (e.cap > 0 && level[v] < level[e.to]) {
				int d = dfs(e.to, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	int maxFlow() {
		int maxflow = 0;
		while (1) {
			bfs(source);
			if (level[target] < 0) return maxflow;
			for (int i = 0; i <= target; ++ i)
				iter[i] = 0;
			int f;
			while ((f = dfs(source, INF)) > 0)
				maxflow += f;
		}
	}
}dinic;


int main() {
	return 0;
}