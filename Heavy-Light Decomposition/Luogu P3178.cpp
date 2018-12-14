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

int fa[N], son[N], sz[N], pos[N], rpos[N], endd[N], dep[N], top[N], tot;
vector<int> G[N];
int n, m, weight[N];

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
    rpos[tot] = u;
    if (son[u]) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
    endd[u] = tot;
}

LL sum[N * 4], add[N * 4];

void build(int o, int l, int r) {
    if (l == r) {
        sum[o] = add[o] = weight[rpos[l]];
    } else {
        int mid = (l + r) >> 1;
        build(o * 2, l, mid);
        build(o * 2 + 1, mid + 1, r);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }
}

void maintain(int o, int l, int r) {
    sum[o] = LL(r - l + 1) * add[o];
    if (l < r) sum[o] += sum[o * 2] + sum[o * 2 + 1];
}

void update(int o, int l, int r, int ql, int qr, int addv) {
    if (ql <= l && r <= qr) {
        add[o] += addv;
        maintain(o, l, r);
        return;
    }

    int mid = (l + r) >> 1;
    if (ql <= mid) update(o * 2, l, mid, ql, qr, addv);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, addv);
    maintain(o, l, r);
}

LL query(int o, int l, int r, int ql, int qr, LL addv) {
    if (ql <= l && r <= qr) return sum[o] + addv * (r - l + 1);

    int mid = (l + r) >> 1;
    LL ans = 0;
    if (ql <= mid) ans += query(o * 2, l, mid, ql, qr, addv + add[o]);
    if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr, addv + add[o]);
    return ans;
}

LL solve(int x) {
    LL ans = 0;
    while (top[x]) {
        int tx = top[x];
        ans += query(1, 1, n, pos[tx], pos[x], 0);
        x = fa[tx];
    }
    ans += query(1, 1, n, 1, pos[x], 0);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> weight[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs(1, 0, 0);
    dfs2(1, 0);

    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int id;
        cin >> id;
        if (id == 1) {
            int x, a;
            cin >> x >> a;
            update(1, 1, n, pos[x], pos[x], a);
        } else if (id == 2) {
            int x, a;
            cin >> x >> a;
            update(1, 1, n, pos[x], endd[x], a);
        } else {
            int x;
            cin >> x;
            cout << solve(x) << '\n';
        }
    }
    return 0;
}
