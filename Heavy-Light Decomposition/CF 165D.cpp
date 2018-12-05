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

const int N = 112345;

int n, tot;
int dep[N], fa[N], sz[N], son[N], pos[N], top[N];
vector<int> G[N];

int dfs(int u, int pa, int depth) {
    fa[u] = pa;
    dep[u] = depth;
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
}

int sum[N * 4];
vector<pii> edges;

void update(int o, int l, int r, int loc, int val) {
    if (l == r) {
        sum[o] = val;
        return;
    }

    int mid = (l + r) >> 1;
    if (loc <= mid) update(o * 2, l, mid, loc, val);
    else update(o * 2 + 1, mid + 1, r, loc, val);
    sum[o] = sum[o * 2] + sum[o * 2 + 1];
}

int query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum[o];
    int mid = (l + r) >> 1;

    int ans = 0;
    if (ql <= mid) ans += query(o * 2, l, mid, ql, qr);
    if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr);
    return ans;
}

int solve(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(tx, ty);
            swap(x, y);
        }

        if (query(1, 1, n, pos[tx], pos[x])) return -1;
        ans += pos[x] - pos[tx] + 1;
        x = fa[tx];
    }

    if (x == y) return ans;
    if (dep[x] > dep[y]) swap(x, y);
    if (query(1, 1, n, pos[son[x]], pos[y])) return -1;
    ans += pos[y] - pos[x];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        edges.pb({ x, y });
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs(1, 0, 0);
    dfs2(1, 0);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k == 1 || k == 2) {
            int id;
            cin >> id;
            id--;
            int x = edges[id]._1, y = edges[id]._2;
            if (dep[x] < dep[y]) swap(x, y);

            if (k == 1) update(1, 1, n, pos[x], 0);
            else update(1, 1, n, pos[x], 1);
        } else {
            int x, y;
            cin >> x >> y;
            cout << solve(x, y) << '\n';
        }
    }
    return 0;
}
