#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5;
int tree[4 * N]; 
int arr[N]; 

int counting_zeros(int a, int b) {
    return a + b;
}
void build(int node, int st, int en) {
    if(st == en) {  
        if(arr[st] == 0) tree[node] = 1;
        else tree[node] = 0;
        return;
    }
    int mid = (st + en) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, en);
    tree[node] = counting_zeros(tree[2 * node], tree[2 * node + 1]); 
}
long long query(int node, int st, int en, int l, int r) {
    if(st > r or en < l) return 0;
    if(st >= l and en <= r) return tree[node];
    int mid = (st + en) / 2;
    ll l_sum = query(2 * node, st, mid, l, r);
    ll r_sum = query(2 * node + 1, mid + 1, en, l, r);
    return counting_zeros(l_sum, r_sum);
}
void update(int node, int st, int en, int val, int pos) {
    if(st == en) {
        arr[st] = val;
        if(val == 0) {
            tree[node] = 1;
        }
        else {
            tree[node] = 0;
        }
        return;
    }
    int mid = (st + en) / 2;
    if(pos <= mid) update(2 * node, st, mid, pos, val);
    else update(2 * node + 1, mid + 1, en, pos, val);
    tree[node] = counting_zeros(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int test_case = 1;
    // cin >> test_case;

    while (test_case--) {
        int n, q;
        cin >> n >> q; 
        for (int i = 0; i < n; i++) cin >> arr[i]; 
        build(1, 0, n - 1);
      
        while (q--) {
            int type; cin >> type;
            if(type == 1) {
                int l, r; cin >> l >> r;
                l--, r--;
                cout << query(1, 0, n - 1, l, r) << '\n';
            }
            else {
                int val, idx; cin >> val >> idx;
                idx--;
                update(1, 0, n - 1, val, idx);
            }
        }
    }

    return 0;
}
