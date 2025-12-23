#include <bits/stdc++.h>
#define FastIO                  \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0); 

using namespace std;
using ll = long long int;
 
const int N = 2e5 + 5;

int par1[N];
int size1[N];
int par2[N];
int size2[N];

void Make(int node) {
    par1[node] = par2[node] = node;
    size1[node] = size2[node] = 1;
}

int Find1(int node) {
    if(node == par1[node]) {
        return node;
    }
    return par1[node] = Find1(par1[node]);
}
void Union1(int u, int v) {
    int a = Find1(u);
    int b = Find1(v);
    if(a != b ) {
        if(size1[a] > size1[b]) {
            swap(size1[a], size1[b]);
        }
        par1[b] = a;
        size1[a] += size1[b];
    }
}
int Find2(int node) {
    if(node == par2[node]) {
        return node;
    }
    return par2[node] = Find2(par2[node]);
}
void Union2(int u, int v) {
    int a = Find2(u);
    int b = Find2(v);
    if(a != b ) {
        if(size2[a] > size2[b]) {
            swap(size2[a], size2[b]);
        }
        par2[b] = a;
        size2[a] += size2[b];
    }
}
void solve() {
    int n, a, b; cin >> n >> a >> b;
    for(int i = 1; i <= n; i++ ) Make(i);
    for(int i = 0; i < a; i++ ) {
        int u, v; cin >> u >> v;
        Union1(u, v);
    }
    for(int i = 0; i < b; i++ ) {
        int u, v; cin >> u >> v;
        Union2(u, v);
    }
    vector<pair<int, int>> ans;
    for(int i = 1; i <= n; i++ ) {
        for(int j = i + 1; j <= n; j++ ) {
            int u1 = Find1(i);
            int v1 = Find1(j);
            int u2 = Find2(i);
            int v2 = Find2(j);
            if(u1 != v1 and u2 != v2) {
                Union1(i, j);
                Union2(i, j);
                ans.push_back({i, j});
            }
        }
    }
    cout << ans.size() << '\n';
    for(auto &[u, v] : ans ) cout << u << " " << v << '\n';    
}

int32_t main() {
    FastIO;
 
    int test_case = 1;
    // cin >> test_case;
    int Case = 1;
    while (test_case--) {
        solve();
        Case++;
    }

    return 0;
}
