// Important Problem
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
#define sqr(x) ((x) * (x))
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 212345;

int n, q, a[N];
vector<int> G[N];
int fa[N], son[N], dep[N], sz[N], top[N], pos[N], tot;

int dfs(int u, int pa, int depth) {
    fa[u] = pa;
    dep[u] = depth;
    sz[u] = 1;

    for (int v : G[u])
        if (v != pa) {
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

LL ss[N * 4], ss2[N * 4], addv[N * 4];

void maintain(int o, int l, int r) {
    ss[o] = addv[o] * (r - l + 1);
    ss2[o] = sqr(addv[o]) * (r - l + 1);
    if (l < r) {
        ss[o] += ss[o * 2] + ss[o * 2 + 1];
        ss2[o] += ss2[o * 2] + ss2[o * 2 + 1] + (ss[o * 2] + ss[o * 2 + 1]) * addv[o] * 2;
    }
}

void pushdown(int o) {
    addv[o * 2] += addv[o];
    addv[o * 2 + 1] += addv[o];
    addv[o] = 0;
}

void update(int o, int l, int r, int ql, int qr, int add) {
    if (ql <= l && r <= qr) {
        addv[o] += add;
        maintain(o, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(o);
    if (ql <= mid) update(o * 2, l, mid, ql, qr, add); else maintain(o * 2, l, mid);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, add); else maintain(o * 2 + 1, mid + 1, r);
    maintain(o, l, r);
}

void solve_update(int x, int add) {
    while (top[x] != 1) {
        int tx = top[x];
        update(1, 1, n, pos[tx], pos[x], add);
        x = fa[tx];
    }
    update(1, 1, n, 1, pos[x], add);
}

LL query(int o, int l, int r, int ql, int qr, LL add) {
    if (ql <= l && r <= qr) return ss[o] + add * (r - l + 1);
    int mid = (l + r) >> 1;
    LL ans = 0;
    if (ql <= mid) ans += query(o * 2, l, mid, ql, qr, add + addv[o]);
    if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr, add + addv[o]);
    return ans;
}

LL sum;

LL solve_query(int x) {
    LL ans = ss2[1] + sqr(sum) * dep[x];
    LL cur = 0;
    while (top[x] != 1) {
        int tx = top[x];
        cur += query(1, 1, n, pos[tx], pos[x], 0);
        x = fa[tx];
    }
    if (x != 1) cur += query(1, 1, n, pos[son[1]], pos[x], 0);

    //cout << ans << ' ' << cur << endl;

    return ans - sum * cur * 2;
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

    for (int i = 1; i <= n; i++) { cin >> a[i]; sum += a[i]; }
    dfs(1, 0, 0);
    dfs2(1, 1);

    for (int i = 1; i <= n; i++) solve_update(i, a[i]);

    while (q--) {
        int id;
        cin >> id;
        if (id == 1) {
            int x, y;
            cin >> x >> y;
            solve_update(x, y - a[x]);
            sum += y - a[x];
            a[x] = y;
        } else {
            int x;
            cin >> x;
            cout << solve_query(x) << '\n';
        }
    }
    return 0;
}
