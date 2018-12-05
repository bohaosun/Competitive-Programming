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

const int N = 31234;
const int INF = int(1e9);

int n, tot;
int dep[N], fa[N], son[N], sz[N], pos[N], top[N], w[N];
vector<int> G[N];

int dfs(int u, int pa, int depth) {
    dep[u] = depth;
    fa[u] = pa;
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

int sum[N * 4], maxm[N * 4];

void update(int o, int l, int r, int loc, int val) {
    if (l == r) {
        sum[o] = maxm[o] = val;
        return;
    }

    int mid = (l + r) >> 1;
    if (loc <= mid) update(o * 2, l, mid, loc, val);
    else update(o * 2 + 1, mid + 1, r, loc, val);
    sum[o] = sum[o * 2] + sum[o * 2 + 1];
    maxm[o] = max(maxm[o * 2], maxm[o * 2 + 1]);
}

void query(int o, int l, int r, int ql, int qr, int& rmaxm, int& rsum) {
    if (ql <= l && r <= qr) {
        rmaxm = max(rmaxm, maxm[o]);
        rsum += sum[o];
        return;
    }

    int mid = (l + r) >> 1;
    if (ql <= mid) query(o * 2, l, mid, ql, qr, rmaxm, rsum);
    if (qr > mid) query(o * 2 + 1, mid + 1, r, ql, qr, rmaxm, rsum);
}

void solve(int x, int y, int& rmaxm, int& rsum) {
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] < dep[ty]) {
            swap(x, y);
            swap(tx, ty);
        }

        query(1, 1, n, pos[tx], pos[x], rmaxm, rsum);
        x = fa[tx];
    }

    if (dep[x] > dep[y]) swap(x, y);
    query(1, 1, n, pos[x], pos[y], rmaxm, rsum);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }
    for (int i = 1; i <= n; i++) cin >> w[i];

    dfs(1, 0, 0);
    dfs2(1, 0);


    for (int i = 1; i <= n; i++) update(1, 1, n, pos[i], w[i]);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s[0] == 'Q') {
            int sum = 0;
            int maxm = -INF;
            int x, y;
            cin >> x >> y;
            solve(x, y, maxm, sum);
            if (s[1] == 'S') cout << sum << '\n';
            else cout << maxm << '\n';
        } else {
            int x, y;
            cin >> x >> y;
            update(1, 1, n, pos[x], y);
        }
    }
    return 0;
}
