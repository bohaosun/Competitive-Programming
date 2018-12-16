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

const int N = 312345;

int n, a[N];

int fa[N], son[N], pos[N], dep[N], top[N], sz[N], rpos[N], tot;
vector<int> G[N];
int ans[N];

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
}

int add[N * 4];

void update(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        add[o] += 1;
        return;
    }

    int mid = (l + r) >> 1;
    if (ql <= mid) update(o * 2, l, mid, ql, qr);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr);
}

void get_ans(int o, int l, int r) {
    if (l == r) {
        ans[rpos[l]] = add[o];
        return;
    }

    int mid = (l + r) >> 1;
    add[o * 2] += add[o];
    add[o * 2 + 1] += add[o];
    get_ans(o * 2, l, mid);
    get_ans(o * 2 + 1, mid + 1, r);
}

void solve(int x, int y) {
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(x, y);
            swap(tx, ty);
        }

        update(1, 1, n, pos[tx], pos[x]);
        x = fa[tx];
    }

    if (dep[x] > dep[y]) swap(x, y);
    update(1, 1, n, pos[x], pos[y]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs(1, 0, 0);
    dfs2(1, 0);

    for (int i = 1; i < n; i++) solve(a[i], a[i + 1]);
    get_ans(1, 1, n);
    for (int i = 1; i <= n; i++) {
        if (a[1] == i) cout << ans[i] << '\n';
        else cout << ans[i] - 1 << '\n';
    }
    return 0;
}
