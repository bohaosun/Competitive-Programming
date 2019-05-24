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
#include <complex>

#define _1 first
#define _2 second
#define pb push_back
#define mp make_pair
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 212345;

vector<int> G[N];
int n, q;
int fa[N], dep[N], son[N], pos[N], sz[N], top[N], tot;
int cnt[N], ans[N];

int dfs(int u, int pa, int depth) {
    fa[u] = pa;
    dep[u] = depth;
    sz[u] = 1;

    for (int v : G[u]) {
        if (v == pa) continue;
        sz[u] += dfs(v, u, depth + 1);
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
    return sz[u];
}

void dfs(int u, int tp) {
    top[u] = tp;
    pos[u] = ++tot;
    if (son[u]) dfs(son[u], tp);

    for (int v : G[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs(v, v);
    }
}

int setv[N * 4];

void update(int o, int l, int r, int ql, int qr, int c) {
    if (setv[o] == c) return;
    if (ql <= l && r <= qr) {
        if (setv[o] > -1) { // color different
            int origin = setv[o];
            if (origin) {
                --ans[cnt[origin]];
                //cout << origin << ' ' << cnt[origin] << ' ' << ans[cnt[origin]] << endl;
                cnt[origin] -= r - l + 1;
                ++ans[cnt[origin]];
            }
            cnt[c] += r - l + 1;
        } else {
            int mid = l + (r - l) / 2;
            update(o * 2, l, mid, ql, qr, c);
            update(o * 2 + 1, mid + 1, r, ql, qr, c);
        }
        setv[o] = c;
    } else {
        if (setv[o] > -1) { setv[o * 2] = setv[o * 2 + 1] = setv[o]; setv[o] = -1; }
        int mid = l + (r - l) / 2;
        if (ql <= mid) update(o * 2, l, mid, ql, qr, c);
        if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, c);
        if (setv[o * 2] == setv[o * 2 + 1]) setv[o] = setv[o * 2];
    }
}

void solve(int u, int c) {
    --ans[cnt[c]];
    while (top[u] != 1) {
        int tu = top[u];
        update(1, 1, n, pos[tu], pos[u], c);
        u = fa[tu];
    }

    if (u > 1) update(1, 1, n, pos[son[1]], pos[u], c);
    //assert(cnt[c] >= 0);
    ++ans[cnt[c]];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    ans[0] = q;
    cin >> q;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }

    dfs(1, 0, 0);
    dfs(1, 1);

    //for (int i = 1; i <= n; i++) cerr << fa[i] << ' ' << dep[i] << ' ' << son[i] << ' ' << top[i] << ' ' << pos[i] << endl;

    while (q--) {
        int u, c, m;
        cin >> u >> c >> m;
        solve(u, c);
//        for (int i = 0; i < n; i++) cout << cnt[i] << ' ';
//        cout << endl;
//        for (int i = 0; i < n; i++) cout << ans[i] << ' ';
//        cout << endl;
        cout << ans[m] << endl;
    }
    return 0;
}
