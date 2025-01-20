#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5;
pair<int, int> tree[4 * N]; 
int arr[N]; 
void printTree(int n) {
    cout << "Segment Tree:\n";
    for (int i = 1; i < 4 * n; i++) {
        if (tree[i].first != 0 or tree[i].second != 0) { 
            cout << "Node " << i << ": (" << tree[i].first << ", " << tree[i].second << ")\n";
        }
    }
}
pair<int, int> combine(pair<int, int> &a, pair<int, int> &b) {
    if (a.first > b.first) return a;
    else if (a.first < b.first) return b;
    return make_pair(a.first, a.second + b.second);
} 
void build(int node, int st, int en) {
    if (st == en) {
        tree[node] = make_pair(arr[st], 1);
        return;
    }
    int mid = (st + en) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, en);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]); 
} 
pair<int, int> query(int node, int st, int en, int l, int r) {
    if (st > r or en < l) return make_pair(INT_MIN, 0);
    if (st >= l and en <= r) return tree[node];
    int mid = (st + en) / 2;
    auto left = query(2 * node, st, mid, l, r);
    auto right = query(2 * node + 1, mid + 1, en, l, r);
    return combine(left, right);
}
void update(int node, int st, int en, int val, int idx) {
    if(st == en) {
        arr[idx] = val;
        tree[node] = make_pair(val, 1);
        return;
    }
    int mid = (st + en) / 2;
    if(idx <= mid) update(2 * node, st, mid, val, idx);
    else update(2 * node, mid + 1, en, val, idx); 
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
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
        cout << "After Building:\n";
        printTree(n);
        while (q--) {
            int type; cin >> type;
            if(type == 1) {
                int l, r; cin >> l >> r;
                l--, r--;
                auto [a, b] = query(1, 0, n - 1, l, r);
                cout << a << ' ' << b << '\n';
            }
            else {
                int val, idx; cin >> val >> idx;
                idx--;
                update(1, 0, n - 1, val, idx);
                cout << "After Update:\n";
                printTree(n);
            }
        }
    }

    return 0;
}
