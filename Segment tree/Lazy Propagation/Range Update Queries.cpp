#include <bits/stdc++.h>

#define FastIO                  \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0);

using namespace std;

const int N = 2e5;

int n, q;
int arr[N];

struct stree {
    long long tree[4 * N], lazy[4 * N];  

    void push(int node, int l, int r) {
        if (lazy[node] == 0) {
            return;
        }
        tree[node] = lazy[node] * (r - l + 1);
        if (l != r) {
            lazy[2 * node] = lazy[node];
            lazy[2 * node + 1] = lazy[node];
        }
        lazy[node] = 0; 
    }

    void build(int node, int l, int r) {
        lazy[node] = 0;  
        if (l == r) {
            tree[node] = arr[l];  
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int l, int r, int i, int j, int v) {
        push(node, l, r);
        if (r < i || j < l) {
            return;  
        }
        if (i <= l && r <= j) {
            lazy[node] = v;  
            push(node, l, r);
            return;  
        }
        int mid = (l + r) >> 1;
        update(2 * node, l, mid, i, j, v);
        update(2 * node + 1, mid + 1, r, i, j, v);
        tree[node] = tree[2 * node] + tree[2 * node + 1]; 
    }

    long long query(int node, int l, int r, int i, int j) {
        push(node, l, r);
        if (r < i || j < l) {
            return 0; 
        }
        if (i <= l && r <= j) {
            return tree[node]; 
        }
        int mid = (l + r) >> 1;
        long long x = query(2 * node, l, mid, i, j);
        long long y = query(2 * node + 1, mid + 1, r, i, j);
        return x + y;  
    }
};

stree st;

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; 
    }
    st.build(1, 0, n - 1);
    
    while (q--) {
        int tp; 
        cin >> tp;
        if (tp == 1) {
            int idx, val; 
            cin >> idx >> val;
            st.update(1, 0, n - 1, idx - 1, idx - 1, val);  
        } 
        else {
            int x; 
            cin >> x;
            st.update(1, 0, n - 1, 0, n - 1, x); 
        }
        cout << st.query(1, 0, n - 1, 0, n - 1) << '\n';  
    }
}

int32_t main() {
    FastIO;

    int test_case = 1;
    // cin >> test_case; 
    int Case = 1;
    while (test_case--) {
        // cout << "Case " << Case << ": ";
        solve();
        Case++;
    }

    return 0;
}
