#include <bits/stdc++.h> 
using namespace std;

const int N = 2e5 + 5;

int a[N];
long long tree[4LL * N];
void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
long long query(int node, int start, int end, int l, int r) {
    if(start > r or end < l) { // In case of non - overlapping
        return 0;
    }
    if(l <= start and r >= end) {
        return tree[node]; // In case of fully overlapping 
    } 

    // In case of partially overlapping
    int mid = (start + end) / 2;

    long long left_sum = query(2 * node, start, mid, l, r);
    long long right_sum = query(2 * node + 1, mid + 1, end, l, r);

    return left_sum + right_sum;
}
int32_t main() {
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++ ) cin >> a[i];
    build(1, 0, n - 1);
    while(q-- ) {
        int l, r; cin >> l >> r;
        l--;
        r--;
        long long ans = query(1, 0, n - 1, l, r);
        cout << ans << endl;
    }
    return 0;
} 
