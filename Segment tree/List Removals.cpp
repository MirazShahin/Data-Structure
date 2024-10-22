#include <bits/stdc++.h>
#define FastIO                  \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0);
using namespace std;
using ll = long long;

const int N = 2e5 + 3;
int tree[4 * N];
void build(int node, int start, int end) {
    if(start == end) {
        tree[node] = 1;
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
void update(int node, int st, int en, int idx) {
    if(st == en) {
        tree[node] = 0;
        return;
    }
    int mid = (st + en) / 2;
    if(idx <= mid) {
        update(2 * node, st, mid, idx);
    }
    else {
        update(2 * node + 1, mid + 1, en, idx);
    }
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
int query(int node, int st, int en, int cnt) {
    if(st == en) {
        return st;
    }
    int mid = (st + en) / 2;
    if(tree[2 * node] >= cnt) {
        auto x = query(2 * node, st, mid, cnt);
        return x;
    }
    else {
        auto x = query(2 * node + 1, mid + 1, en, cnt - tree[2 * node]);
        return x;
    }
}
void solve() {
    int n; cin >> n;
    vector<int> v(n), w(n);
    for(int i = 0; i < n; i++ ) cin >> v[i];
    for(int j = 0; j < n; j++ ) cin >> w[j];
    build(1, 0, n - 1);
    for(int i = 0; i < n; i++ ) {
        int idx = query(1, 0, n - 1, w[i]);
        cout << v[idx] << " ";
        update(1, 0, n - 1, idx);
    }
    cout << '\n';
    

}
int32_t main() {
    FastIO;
 
    int test_case = 1;
    // cin >> test_case;
    int Case = 1;
    while(test_case--) {
//    cout << "Case " << Case << ": ";
        solve();
        Case++;
    }

    return 0;
}
/*
 * do something instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
