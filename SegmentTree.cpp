#include <bits/stdc++.h>

#define MAX_N 100005

int N; // the size of the array
int A[MAX_N]; // beginning array together with build function

struct SegmentTree {
	struct Node {
		int sum; // information on each node
		int lazy; // lazy tag on each node
	}Tree[MAX_N << 2];

	// get information from child nodes
	void pushUp(int v) {
		Tree[v].sum = Tree[v << 1].sum + Tree[v << 1 | 1].sum;
	}

	void pushDown(int l, int r, int v) {
		int mid = (l + r) >> 1;

		//update information
		Tree[v << 1].sum += Tree[v].lazy * (mid - l + 1);
		Tree[v << 1 | 1].sum += Tree[v].lazy * (r - mid);

		// update lazy
		Tree[v << 1].lazy += Tree[v].lazy;
		Tree[v << 1 | 1].lazy += Tree[v].lazy;

		// clear lazy
		Tree[v].lazy = 0;
	}

	#define lchild l, mid, v << 1 // lchild maintains [l, mid] with index 2 * v
	#define rchild mid + 1, r, v << 1 | 1 // rchild maintains [mid + 1, r] with index 2 * v + 1

	// call build()
	void build(int l = 1, int r = N, int v = 1) {
		Tree[v].sum = Tree[v].lazy = 0;
		if (l == r) {
			Tree[v].sum = A[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(lchild);
		build(rchild);

		pushUp(v);
	}

	// call update(L, R, x) if you adding each value for x from index L to index R
	void update(int L, int R, int x, int l = 1, int r = N, int v = 1) {
		if (L <= l && r <= R) {
			Tree[v].sum += x;
			Tree[v].lazy += x;
			return;
		}

		if (Tree[v].lazy) pushDown(l, r, v);

		int mid = (l + r) >> 1;
		if (L <= mid) update(L, R, x, lchild);
		if (R > mid) update(L, R, x, rchild);

		pushUp(v);
	}

	// call query(L, R) if you want the information from index L to index R
	int query(int L, int R, int l = 1, int r = N, int v = 1) {
		if (L <= l && r <= R) 
			return Tree[v].sum;

		if (Tree[v].lazy) pushDown(l, r, v);

		int ret = 0; // return value
		int mid = (l + r) >> 1;
		if (L <= mid) ret += query(L, R, lchild);
		if (R > mid) ret += query(L, R, rchild);

		pushUp(v); // sometimes it's no use

		return ret;
	}
}SG;

int Q; // the number of queries

int main() {
	scanf("%d%d", &N, &Q);

	for (int i = 1; i <= N; ++ i)
		scanf("%d", &A[i]);

	SG.build();

	while (Q--) {
		int ty; // query type
		int L, R, x;

		scanf("%d", &ty);

		// update
		if (ty == 1) {
			scanf("%d%d%d", &L, &R, &x);
			SG.update(L, R, x);
		}
		// query
		else {
			scanf("%d%d", &L, &R);
			printf("%d\n", SG.query(L, R));
		}
	}
	return 0;
}