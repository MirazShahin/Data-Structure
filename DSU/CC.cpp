#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components, maxSize;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
        components = n;
        maxSize = 1;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];

        components--;
        maxSize = max(maxSize, sz[a]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dsu.unite(a, b);
        cout << dsu.components << " " << dsu.maxSize << "\n";
    }

    return 0;
}
