#include <bits/stdc++.h>

using namespace std;

#define MAX_N 1650 // maximum vertices
#define INF 0x3f3f3f3f // must be larger than total capacities and total costs

struct edge {
	int to, cap, rev, cost;
	edge (int tt, int cc, int rr, int co) : to(tt), cap(cc), rev(rr), cost(co) {}
	edge () {}
};

struct ZKW {

	// all index begins at 1

	vector<edge> G[MAX_N];
	bool vis[MAX_N];

	int source, target;

	// the final cost and flow
	int cost, flow;

	// maintain the distance between source and target
	int pi;

	// initialize the Dinic
	// n is the total vertices excludes source and target
	void init(int n) {
		// set source and target
		source = n + 1;
		target = n + 2;

		// clear the graph
		for (int i = 0; i <= target; ++ i) {
			G[i].clear();
			vis[i] = 0;
		}

		cost = flow = 0;
		pi = 0;
	}

	// set source and target by yourself
	// call after init
	void setSourceTarget(int s, int t) {
		source = s;
		target = t;
	}

	void addEdge(int from, int to, int cap, int cost) {
		G[from].push_back(edge(to, cap, G[to].size(), cost));
		G[to].push_back(edge(from, 0, G[from].size() - 1, -cost));
	}

	// find new augment path
	int augment(int v, int nowFlow) {
		if (v == target) return cost += pi * nowFlow, flow += nowFlow, nowFlow;
		vis[v] = 1;

		int newFlow = nowFlow;
		for (int i = 0; i < (int)G[v].size(); ++ i) {
			edge &e = G[v][i];
			if (e.cap && !e.cost && !vis[e.to]) {
				int d = augment(e.to, min(newFlow, e.cap));
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				newFlow -= d;
				if (!newFlow) return nowFlow;
			}
		}
		return nowFlow - newFlow;
	}

	// modify costs
	bool modify() {
		int d = INF;
		for (int v = 1; v <= target; ++ v) {
			if (vis[v]) for (int i = 0; i < (int)G[v].size(); ++ i) {
				edge &e = G[v][i];
				if (e.cap && !vis[e.to]) d = min(d, e.cost);
			}
		}

		if (d == INF) return false;
		for (int v = 1; v <= target; ++ v) {
			if (vis[v]) for (int i = 0; i < (int)G[v].size(); ++ i) {
				edge &e = G[v][i];
				e.cost -= d;
				G[e.to][e.rev].cost += d;
			}
		}
		pi += d;
		return true;
	}

	int minCost() {
		do {
			do {
				for (int v = 1; v <= target; ++ v) 
					vis[v] = false;
			} while (augment(source, INF));
		} while (modify());
		return cost;
	}
}zkw;

int main() {
	return 0;
}