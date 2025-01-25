#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5;
int tree[4 * N]; 
int arr[N]; 

int combine(int a, int b) {
    return a + b;
}

void build(int node, int st, int en) {
    if (st == en) {  
        tree[node] = (arr[st] == 0) ? 1 : 0;
        return;
    }
    int mid = (st + en) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, en);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]); 
}

long long query(int node, int st, int en, int l, int r) {
    if (st > r || en < l) return 0;   
    if (st >= l && en <= r) return tree[node];   
    int mid = (st + en) / 2;
    ll l_sum = query(2 * node, st, mid, l, r);
    ll r_sum = query(2 * node + 1, mid + 1, en, l, r);
    return combine(l_sum, r_sum);
}

int finding_kth_zero(int node, int st, int en, int k) {
    if (k > tree[node]) return -1;   
    if (st == en) return st;  
    int mid = (st + en) / 2;
    if (k <= tree[2 * node]) {
        return finding_kth_zero(2 * node, st, mid, k);
    } else {
        return finding_kth_zero(2 * node + 1, mid + 1, en, k - tree[2 * node]);
    }
}

void update(int node, int st, int en, int pos, int val) {
    if (st == en) {
        arr[st] = val;
        tree[node] = (val == 0) ? 1 : 0;
        return;
    }
    int mid = (st + en) / 2;
    if (pos <= mid) update(2 * node, st, mid, pos, val);
    else update(2 * node + 1, mid + 1, en, pos, val);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;  
    for (int i = 0; i < n; i++) cin >> arr[i];

    build(1, 0, n - 1);   

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--, k--;   
            cout << "Total zeros: " << query(1, 0, n - 1, l, r) << '\n';
            int kth_zero = finding_kth_zero(1, 0, n - 1, k + 1);   
            cout << "Kth zero: " << (kth_zero == -1 ? -1 : kth_zero + 1) << '\n';  
        } else {
            int idx, val;
            cin >> idx >> val;
            idx--;  
            update(1, 0, n - 1, idx, val);
        }
    }

    return 0;
}
