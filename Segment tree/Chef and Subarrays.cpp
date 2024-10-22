#include <bits/stdc++.h>
#define FastIO                  \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0);
using namespace std;
using ll = long long;

const ll N = 1LL * (2e5 + 3);
ll tree[4 * N];
 
void build(ll node, ll start, ll end, vector<ll> &v) {
    if (start == end) {
        tree[node] = v[start];   
        return;
    }
    ll mid = (start + end) / 2;
    build(2 * node, start, mid, v);
    build(2 * node + 1, mid + 1, end, v);
    tree[node] = tree[2 * node] | tree[2 * node + 1];   
} 
ll query(ll node, ll st, ll en, ll l, ll r) {
    if (r < st or en < l) {
        return 0;   
    }
    if (l <= st and en <= r) {
        return tree[node];   
    }
    ll mid = (st + en) / 2;
    ll leftQuery = query(2 * node, st, mid, l, r);
    ll rightQuery = query(2 * node + 1, mid + 1, en, l, r);
    return leftQuery | rightQuery;   
}

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> v(n);
    for(ll i = 0; i < n; i++ ) cin >> v[i];
    build(1, 0, n - 1, v);
    ll ans = 0;
    for(ll i = 0; i < n; i++ ) {
        ll lo = i, hi = n - 1;
        ll idx = -1;
        while(lo <= hi) {
            ll mid = (hi + lo) / 2;
            ll curr = query(1, 0, n - 1, i, mid);
            if(curr >= k) {
                idx = mid;
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
        if(idx != -1) {
            ans += (n - idx);
        }
    }
    cout << ans << '\n';
}
int32_t main() {
    FastIO;
 
    int test_case = 1;
    cin >> test_case;
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
