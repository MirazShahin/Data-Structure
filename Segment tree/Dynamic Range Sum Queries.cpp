#include <bits/stdc++.h> 
using namespace std;

const int N = 2e5 + 5;

int a[N];
long long tree[4 * N]; 

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);

    // Store the minimum value
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

long long query(int node, int start, int end, int l, int r) {
    if (start > r or end < l) {
        return 0; // Return a large value for non-overlapping
    }
    if (l <= start and r >= end) {
        return tree[node]; // Fully overlapping
    }

    // Partially overlapping
    int mid = (start + end) / 2;
    long long left_sum = query(2 * node, start, mid, l, r);
    long long right_sum = query(2 * node + 1, mid + 1, end, l, r);

    return left_sum + right_sum;
}
void update(int node, int start, int end, int idx, int value) {
    if(start == end ) {
        a[start] = value;
        tree[node] = value;
        return;
    }
    int mid = (start + end) / 2;
    if(idx <= mid) {
        update(2 * node, start, mid, idx, value);
    }
    else {
        update(2 * node + 1, mid + 1, end, idx, value);
    }
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    build(1, 0, n - 1);
    while (q--) {
        int a, k, r; cin >> a >> k >> r;
        if(a == 2) {
            k--;
            r--;
            long long ans = query(1, 0, n - 1, k, r);
            cout << ans << endl;
        }
        else {
            k--; 
            update(1, 0, n - 1, k, r);
        }
    }
    return 0;
}
