#include <bits/stdc++.h> 
using namespace std;

const int N = 2e5 + 5;

int a[N];
int tree[4 * N]; 

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);

    // Store the minimum value
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int query(int node, int start, int end, int l, int r) {
    if (start > r or end < l) {
        return INT_MAX; // Return a large value for non-overlapping
    }
    if (l <= start and r >= end) {
        return tree[node]; // Fully overlapping
    }

    // Partially overlapping
    int mid = (start + end) / 2;
    int left_min = query(2 * node, start, mid, l, r);
    int right_min = query(2 * node + 1, mid + 1, end, l, r);

    return min(left_min, right_min);
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    build(1, 0, n - 1);
    while (q--) {
        int l, r; cin >> l >> r;
        l--;
        r--;
        int ans = query(1, 0, n - 1, l, r);
        cout << ans << endl;
    }
    return 0;
}
