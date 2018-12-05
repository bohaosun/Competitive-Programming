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
#define end endd

const int N = 112345;

int dep[N], fa[N], son[N], sz[N], pos[N], top[N], end[N];
int n, q, root, MOD, tot, w[N];
vector<int> G[N];

int dfs(int u, int pa, int depth) {
    dep[u] = depth;
    fa[u] = pa;
    sz[u] = 1;

    for (int v : G[u])
        if (v != fa[u]) {
            sz[u] += dfs(v, u, depth + 1);
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    return sz[u];
}

void dfs2(int u, int tp) {
    top[u] = tp;
    pos[u] = ++tot;
    if (son[u]) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
    end[u] = tot;
}


LL sum[N * 4], add[N * 4];

void pushdown(int o) {
    if (add[o]) {
        add[o * 2] = (add[o * 2] + add[o]) % MOD;
        add[o * 2 + 1] = (add[o * 2 + 1] + add[o]) % MOD;
        add[o] = 0;
    }
}

void maintain(int o, int l, int r) {
    sum[o] = add[o] * (r - l + 1);
    if (l < r) {
        sum[o] = (sum[o] + sum[o * 2]) % MOD;
        sum[o] = (sum[o] + sum[o * 2 + 1]) % MOD;
    }
}

void update(int o, int l, int r, int ql, int qr, LL val) {
    if (ql <= l && r <= qr) {
        add[o] = (add[o] + val) % MOD;
        maintain(o, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(o);
    if (ql <= mid) update(o * 2, l, mid, ql, qr, val); else maintain(o * 2, l, mid);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, val); else maintain(o * 2 + 1, mid + 1, r);
    maintain(o, l, r);
}

LL query(int o, int l, int r, int ql, int qr, LL cur_add) {
    if (ql <= l && r <= qr) return (sum[o] + cur_add * (r - l + 1)) % MOD;
    int mid = (l + r) >> 1;
    LL ans = 0;
    if (ql <= mid) ans = (ans + query(o * 2, l, mid, ql, qr, (cur_add + add[o]) % MOD)) % MOD;
    if (qr > mid) ans = (ans + query(o * 2 + 1, mid + 1, r, ql, qr, (cur_add + add[o]) % MOD)) % MOD;
    return ans;
}

void solve_add(int x, int y, LL val) {
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(x, y);
            swap(tx, ty);
        }
        update(1, 1, n, pos[tx], pos[x], val);
        x = fa[tx];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(1, 1, n, pos[x], pos[y], val);
}

LL query_sum(int x, int y) {
    LL ans = 0;
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(x, y);
            swap(tx, ty);
        }
        ans = (ans + query(1, 1, n, pos[tx], pos[x], 0)) % MOD;
        x = fa[tx];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ans = (ans + query(1, 1, n, pos[x], pos[y], 0)) % MOD;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> root >> MOD;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs(root, 0, 0);
    dfs2(root, 0);
    for (int i = 1; i <= n; i++) update(1, 1, n, pos[i], pos[i], w[i]);

    for (int i = 0; i < q; i++) {
        int id;
        cin >> id;
        if (id == 1) {
            int x, y, z;
            cin >> x >> y >> z;
            solve_add(x, y, z);
        } else if (id == 2) {
            int x, y;
            cin >> x >> y;
            cout << query_sum(x, y) << '\n';
        } else if (id == 3) {
            int x, z;
            cin >> x >> z;
            update(1, 1, n, pos[x], end[x], z);
        } else {
            int x;
            cin >> x;
            cout << query(1, 1, n, pos[x], end[x], 0) << '\n';
        }
    }
    return 0;
}
