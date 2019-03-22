#include <bits/stdc++.h>

using namespace std;

#define MAX_N 100005

int a[MAX_N]; // the array of data
int n; // the number of data

int q; // the number of queries

// find the first position where the value >= key 
int lowerBound(int key) {
	// check n
	if (a[n] < key) 
		return n + 1; // n + 1 means all values in the array are smaller than key

	// set two pointers (l, r] // l is an invalid pointer (a[l] < key) and r is a valid pointer (key <= a[r]) 
	int l = 0, r = n;

	while (r - l > 1) {
		int mid = (r + l) >> 1; // pick the middle position
		if (a[mid] >= key) // if mid is a valid pointer (key <= a[mid])
			r = mid;
		else 
			l = mid;
	}

	return r; // the final valid position
}

// find the first position where the value > key
int upperBound(int key) {
	// check n
	if (a[n] <= key)
		return n + 1;

	// set two pointers (l, r] // l is invalid pointer (a[l] <= key) and r is valid pointer (key < a[r]) 
	int l = 0, r = n;

	while (r - l > 1) {
		int mid = (r + l) >> 1;
		if (a[mid] > key) // if mid is a valid pointer (key < a[mid])
			r = mid;
		else 
			l = mid;
	}

	return r; // the final valid position
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
		scanf("%d", &a[i]);

	sort(a + 1, a + 1 + n); // keep the array sorted

	scanf("%d", &q);
	while (q--) {
		int key;
		scanf("%d", &key);

		int lb = lowerBound(key);
		int rb = upperBound(key);

		if (lb == n + 1) printf("No lower bound, all value are < key\n");
		else printf("The Lower bound of key is: %d\n", a[lowerBound(key)]);

		if (rb == n + 1) printf("No upper bound, all values are <= key\n");
		else printf("The Upper Bound of key is: %d\n", a[upperBound(key)]);
		
		printf("The number of values equal to key is: %d\n", upperBound(key) - lowerBound(key));
	}
	return 0;
}