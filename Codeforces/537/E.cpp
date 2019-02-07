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
const int M = 312;
const int MOD = int(1e9) + 7;

int n, q;
vector<int> G[N];  // tree
int a[N], h[N], mark[N];  // query

int dep[N], fa[N][30], st[N], en[N], dfs_tot;  // dfs, LCA related

int c[N * 2];  // BIT

LL dp[M];

void dfs(int u, int pa, int depth) {
    fa[u][0] = pa;
    dep[u] = depth;
    st[u] = ++dfs_tot;

    for (int v : G[u]) {
        if (v == pa) continue;
        dfs(v, u, depth + 1);
    }
    en[u] = ++dfs_tot;
}

void preprocess() {
    for (int j = 1; j < 18; j++) {
        for (int i = 1; i <= n; i++) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
}

int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 18; i >= 0; i--) {
        if (dep[x] - (1 << i) >= dep[y]) x = fa[x][i];
    }

    if (x == y) return x;

    for (int i = 18; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }

    return fa[x][0];
}

int lowbit(int x) { return x & (-x); }

void add(int x, int val) {
    while (x <= 2 * n) {
        c[x] += val;
        x += lowbit(x);
    }
}

int sum(int x) {
    int ans = 0;
    while (x) {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

/**
 * Key points:
 * 1. Suppose the root doesn't change, find an order to DP: with the order that the number of selected ancestor increasing
 * 2. Use BIT to find the updated value when the root is not fixed.
 * 3. Use dp to solve the situation under 2
 */

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

    dfs(1, 0, 0);
    preprocess();

    for (int i = 0; i < q; i++) {
        int num, m, r;
        cin >> num >> m >> r;
        for (int j = 0; j < num; j++) {
            cin >> a[j];
            mark[a[j]] = 1;
            add(st[a[j]], 1);
            add(en[a[j]], -1);
        }

        int sum_root = sum(st[r]);
        for (int j = 0; j < num; j++) {
            int x = a[j];
            int lca = LCA(x, r);
            h[x] = sum(st[x]) + sum_root - 2 * sum(st[lca]) + mark[lca] - 1;
        }

        sort(a, a + num, [](int x, int y) { return h[x] < h[y]; });

        reset(dp, 0);
        dp[1] = 1;
        for (int j = 1; j < num; j++) {
            int x = a[j];
            for (int k = m; k >= 1; k--) {
                if (k <= h[x]) { dp[k] = 0; continue; }
                dp[k] = (dp[k] * (k - h[x]) + dp[k - 1]) % MOD;
            }
        }
        LL ans = 0;
        for (int j = 1; j <= m; j++) ans = (ans + dp[j]) % MOD;
        cout << ans << '\n';

        for (int j = 0; j < num; j++) {
            mark[a[j]] = 0;
            add(st[a[j]], -1);
            add(en[a[j]], 1);
        }
    }
    return 0;
}
