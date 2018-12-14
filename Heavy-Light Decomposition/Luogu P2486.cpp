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
#define mp make_pair
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 112345;

int top[N], dep[N], son[N], sz[N], fa[N], pos[N], rpos[N], tot;
vector<int> G[N];
int n, m, col[N];

int dfs(int u, int pa, int depth) {
    fa[u] = pa;
    dep[u] = depth;
    sz[u] = 1;

    for (int v : G[u]) {
        if (v == fa[u]) continue;
        sz[u] += dfs(v, u, depth + 1);
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
    return sz[u];
}

void dfs2(int u, int tp) {
    top[u] = tp;
    pos[u] = ++tot;
    rpos[tot] = u;
    if (son[u]) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

int sum[N * 4], setv[N * 4], lc[N * 4], rc[N * 4];

void maintain(int o) {
    if (setv[o] >= 0) {
        lc[o] = rc[o] = setv[o];
        sum[o] = 1;
    } else {
        lc[o] = lc[o * 2];
        rc[o] = rc[o * 2 + 1];
        sum[o] = sum[o * 2] + sum[o * 2 + 1] - (rc[o * 2] == lc[o * 2 + 1]);
        if (sum[o] == 1) setv[o] = lc[o];
    }
}

void build(int o, int l, int r) {
    if (l == r) {
        sum[o] = 1;
        setv[o] = lc[o] = rc[o] = col[rpos[l]];
        return;
    }

    int mid = (l + r) >> 1;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);

    maintain(o);
}

int query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum[o];
    if (setv[o] >= 0) return 1;

    int mid = (l + r) >> 1;
    int cnt = 0, ans = 0;
    if (ql <= mid) { ans += query(o * 2, l, mid, ql, qr); cnt++; }
    if (qr > mid) { ans += query(o * 2 + 1, mid + 1, r, ql, qr); cnt++; }
    if (cnt == 2 && rc[o * 2] == lc[o * 2 + 1]) ans--;
    return ans;
}

void pushdown(int o) {
    if (setv[o] >= 0) {
        setv[o * 2] = setv[o * 2 + 1] = setv[o];
        setv[o] = -1;
    }
}

void update(int o, int l, int r, int ql, int qr, int color) {
    if (ql <= l && r <= qr) {
        setv[o] = lc[o] = rc[o] = color;
        sum[o] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(o);
    if (ql <= mid) update(o * 2, l, mid, ql, qr, color); else maintain(o * 2);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, color); else maintain(o * 2 + 1);
    maintain(o);
}

void solve(int x, int y, int color) {
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(tx, ty);
            swap(x, y);
        }

        update(1, 1, n, pos[tx], pos[x], color);
        x = fa[tx];
    }

    if (dep[x] > dep[y]) swap(x, y);
    update(1, 1, n, pos[x], pos[y], color);
}

int get_color(int o, int l, int r, int loc) {
    if (setv[o] >= 0) return setv[o];
    int mid = (l + r) >> 1;
    if (loc <= mid) return get_color(o * 2, l, mid, loc);
    else return get_color(o * 2 + 1, mid + 1, r, loc);
}

int solve_query(int x, int y) {
    int ans = 0, lastx = -1, lasty = -1;
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(tx, ty);
            swap(x, y);
            swap(lastx, lasty);
        }

        ans += query(1, 1, n, pos[tx], pos[x]);
        int cur = get_color(1, 1, n, pos[x]);
        if (cur == lastx) ans--;
        lastx = get_color(1, 1, n, pos[tx]);
        x = fa[tx];
    }

    if (dep[x] > dep[y]) { swap(x, y); swap(lastx, lasty); }
    ans += query(1, 1, n, pos[x], pos[y]);
    if (get_color(1, 1, n, pos[x]) == lastx) ans--;
    if (get_color(1, 1, n, pos[y]) == lasty) ans--;
    return ans;
 }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> col[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs(1, 0, 0);
    dfs2(1, 0);
    reset(setv, -1);

    //for (int i = 1; i <= n; i++) cout << i << ": " << fa[i] << ' ' << son[i] << ' ' << pos[i] << ' ' << top[i] << endl;

    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == 'C') {
            int x, y, color;
            cin >> x >> y >> color;
            solve(x, y, color);
        } else {
            int x, y;
            cin >> x >> y;
            cout << solve_query(x, y) << '\n';
        }
    }
    return 0;
}
