// Problem L
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <random>

#define _1 first
#define _2 second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 123456;
const int INF = int(1e9);

struct Query {
    int l, r, sz;
    bool operator < (const Query& rhs) const {
        return sz > rhs.sz;
    }
};
vector<Query> Q;

int dep[N], top[N], son[N], fa[N], sz[N], pos[N], tot;  // position in segment tree
vector<int> G[N];
int n, q;

int dfs1(int u, int pa, int depth) {
    dep[u] = depth;
    fa[u] = pa;

    sz[u] = 1;
    for (int v : G[u])
        if (v != pa) {
            sz[u] += dfs1(v, u, depth + 1);
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    return sz[u];
}

void dfs2(int u, int tp) {
    //cout << u << endl;
    top[u] = tp;
    pos[u] = ++tot;
    if (son[u]) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

int LCA(int x, int y) {
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) y = fa[ty];
        else x = fa[tx];
    }
    return dep[x] < dep[y] ? x : y;
}

int minm[N * 4], maxm[N * 4], setv[N * 4];

void query(int o, int l, int r, int ql, int qr, int& qmin, int& qmax) {
    if (setv[o]) {
        qmin = min(qmin, setv[o]);
        qmax = max(qmax, setv[o]);
    } else if (ql <= l && r <= qr) {
        qmin = min(qmin, minm[o]);
        qmax = max(qmax, maxm[o]);
    } else {
        int mid = (l + r) >> 1;
        if (ql <= mid) query(o * 2, l, mid, ql, qr, qmin, qmax);
        if (qr > mid) query(o * 2 + 1, mid + 1, r, ql, qr, qmin, qmax);
    }
}

void pushdown(int o) {
    if (setv[o]) {
        setv[o * 2] = setv[o];
        setv[o * 2 + 1] = setv[o];
        setv[o] = 0;
    }
}

void maintain(int o, int l, int r) {
    if (setv[o]) {
        minm[o] = maxm[o] = setv[o];
    } else if (l < r) {
        minm[o] = min(minm[o * 2], minm[o * 2 + 1]);
        maxm[o] = max(maxm[o * 2], maxm[o * 2 + 1]);
    }
}

void update(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        setv[o] = val;
        maintain(o, l, r);
        return;
    }

    int mid = (l + r) >> 1;
    pushdown(o);
    if (ql <= mid) update(o * 2, l, mid, ql, qr, val); else maintain(o * 2, l, mid);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, val); else maintain(o * 2 + 1, mid + 1, r);
    maintain(o, l, r);
}

bool solve(int x, int y, int col) {
    //cout << x << ' ' << y << ":\n";
    int maxm = -INF, minm = INF;
    while (top[x] != top[y]) {
        int fx = top[x], fy = top[y];
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        query(1, 1, n, pos[fx], pos[x], minm, maxm);
        if (minm != maxm) return false;
        update(1, 1, n, pos[fx], pos[x], col);
        x = fa[fx];
    }

    if (dep[x] > dep[y]) swap(x, y);
    query(1, 1, n, pos[x], pos[y], minm, maxm);
    if (minm != maxm) return false;
    update(1, 1, n, pos[x], pos[y], col);
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs1(1, 0, 0);
    dfs2(1, 0);

    /*for (int i = 1; i <= n; i++) {
        cout << dep[i] << ' ' << fa[i] << ' ' << son[i] << ' ' << top[i] << ' ' << pos[i] << endl;
    }*/

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        //cout << LCA(x, y) << endl;
        int size = dep[x] + dep[y] - dep[LCA(x, y)] * 2;
        Q.pb({ x, y, size });
    }
    sort(all(Q));

    //for (int i = 0; i < q; i++) cout << Q[i].l << ' ' << Q[i].r << endl;

    for (int i = 0; i < q; i++) {
        int l = Q[i].l, r = Q[i].r;
        if (!solve(l, r, i + 1)) { cout << "No\n"; return 0; }
    }
    cout << "Yes\n";
    return 0;
}
