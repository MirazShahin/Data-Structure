#include <bits/stdc++.h> 
using namespace std;
#define FastIO                  \
  ios_base::sync_with_stdio(0); \
  cin.tie(0);                   \
  cout.tie(0);

const int N = 2e5 + 5, MAX = 1e9 + 4;

int a[N];
pair<int, int> tree[4 * N]; 

void build(int node, int l, int r) {
    if (l == r) {
        tree[node].first = a[l];
        tree[node].second = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);

    // Store the minimum value
    if(tree[2 * node].first < tree[2 * node + 1].first) {
        tree[node].first = tree[2 * node].first;
        tree[node].second = tree[2 * node].second;
    }
    else if(tree[2 * node].first > tree[2 * node + 1].first) {
        tree[node].first = tree[2 * node + 1].first;
        tree[node].second = tree[2 * node + 1].second;
    }
    else {
        tree[node].first = tree[2 * node].first;
        tree[node].second = tree[2 * node].second + tree[2 * node + 1].second;
    }
}

pair<int, int> query(int node, int start, int end, int l, int r) {
    if (start > r or end < l) {
        return {MAX, -1}; // Return a large value for non-overlapping
    }
    if (l <= start and r >= end) {
        return tree[node]; // Fully overlapping
    }

    // Partially overlapping
    int mid = (start + end) / 2;
    pair<int, int> left_min = query(2 * node, start, mid, l, r);
    pair<int, int> right_min = query(2 * node + 1, mid + 1, end, l, r);
    
    pair<int, int> ans;
    if(left_min.first < right_min.first) {
        ans = left_min;
    }
    else if(left_min.first > right_min.first) {
        ans = right_min;
    }
    else {
        ans.first = left_min.first;
        ans.second = left_min.second + right_min.second;
    }
    return ans;
}
void update(int node, int start, int end, int idx, int value) {
    if(start == end ) {
        a[start] = value;
        tree[node].first = value;
        tree[node].second = 1;
        return;
    }
    int mid = (start + end) / 2;
    if(idx <= mid) {
        update(2 * node, start, mid, idx, value);
    }
    else {
        update(2 * node + 1, mid + 1, end, idx, value);
    }
    if(tree[2 * node].first < tree[2 * node + 1].first) {
        tree[node].first = tree[2 * node].first;
        tree[node].second = tree[2 * node].second;
    }
    else if(tree[2 * node].first > tree[2 * node + 1].first) {
        tree[node].first = tree[2 * node + 1].first;
        tree[node].second = tree[2 * node + 1].second;
    }
    else {
        tree[node].first = tree[2 * node].first;
        tree[node].second = tree[2 * node].second + tree[2 * node + 1].second;
    }
}
int main() {
    FastIO;
    int n, q; cin >> n >> q; 
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
    }
    build(1, 0, n - 1);
    while (q--) {
        int a, k, r; cin >> a >> k >> r;
        if(a == 2) { 
            auto ans = query(1, 0, n - 1, k, r - 1);
            cout << ans.first << " " << ans.second << endl;
        }
        else {  
            update(1, 0, n - 1, k, r);
        }
    }
    return 0;
}
