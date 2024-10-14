#include <bits/stdc++.h>
#define FastIO                  \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0); 

using namespace std;
using ll = long long int;
const int N = 2e5 + 5;

ll tree[N * 4], lazy[N * 4];
int arr[N];
void build(int node, int st, int en) {
   if(st == en) {
      tree[node] = arr[st];
      return;
   }
   int mid = (st + en) / 2;
   build(2 * node, st, mid);
   build(2 * node + 1, mid + 1, en);
   tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void propagate(int node, int st, int en) {
    if (lazy[node] != 0) { 
        tree[node] += (en - st + 1) * lazy[node];
        if (st != en) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}
void lazy_update(int node, int st, int en, int l, int r, ll val) {
    propagate(node, st, en); // Apply any pending updates

    if (st > r or en < l) return; // No overlap

    if (st >= l and en <= r) { // Full overlap
        lazy[node] += val;
        propagate(node, st, en);
        return;
    }
 
    int mid = (st + en) / 2;
    lazy_update(2 * node, st, mid, l, r, val);
    lazy_update(2 * node + 1, mid + 1, en, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];  
}
ll query(int node, int st, int en, int idx) {
    propagate(node, st, en); 
    if (st == en) return tree[node]; 
    int mid = (st + en) / 2;
    if (idx <= mid) return query(2 * node, st, mid, idx);
    else return query(2 * node + 1, mid + 1, en, idx);
}
void solve() {
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++ ) {
        cin >> arr[i];
    }
    build(1, 0, n - 1);
    while(q-- ) {
        int tp, l, r, val;  
        cin >> tp;
        if(tp == 2) {
            cin >> l;
            l--;
            ll ans = query(1, 0, n - 1, l);
            cout << ans << "\n";
        }
        else {
            cin >> l >> r >> val;
            l--;
            r--;
            lazy_update(1, 0, n - 1, l, r, val);
        }
    }
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
