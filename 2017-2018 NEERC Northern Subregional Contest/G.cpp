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

vector<int> G[N];
int n, m;

// low[0][u]: The earliest, low[1][u]: the second earliest one
// endd[0][u]: The start point to connect rpre[low[0][u]] in the subtree with root u
// endd[1][u]: The start point to connect rpre[low[1][u]] in the subtree with root u
int pre[N], low[2][N], endd[2][N], fa[N], dfs_clock, rpre[N];
bool vis[N];
bool flag;

void update(int u, int val, int ver) {
    if (val < low[0][u]) {
        low[1][u] = low[0][u];
        endd[1][u] = endd[0][u];
        low[0][u] = val;
        endd[0][u] = ver;
    } else if (val < low[1][u]) {
        low[1][u] = val;
        endd[1][u] = ver;
    }
}

vector<int> path;

void print_path() {
    cout << path.size();
    for (int it : path) cout << ' ' << it;
    cout << '\n';
}

void get_path(int u, int v) {
    while (u != v) {
        path.pb(u);
        u = fa[u];
    }
    path.pb(v);
}

void print(int u) {
    int v = rpre[low[1][u]];
    cout << u << ' ' << v << '\n';

    path.clear();
    get_path(u, v);
    print_path();

    path.clear();
    path.pb(v);
    get_path(endd[1][u], u);
    reverse(all(path));
    print_path();

    path.clear();
    get_path(v, rpre[low[0][u]]);
    get_path(endd[0][u], u);
    reverse(all(path));
    print_path();
}

void dfs(int u, int p) {
    vis[u] = true;
    pre[u] = low[0][u] = low[1][u] = ++dfs_clock;
    rpre[dfs_clock] = endd[0][u] = endd[1][u] = u;
    for (int v : G[u])
        if (v != p) {
            if (!pre[v]) {
                fa[v] = u;
                dfs(v, u);
                update(u, low[0][v], endd[0][v]);
                update(u, low[1][v], endd[1][v]);
            } else {
                update(u, pre[v], u);
            }
        }

    // The first one to satisfy this condition must have either endd[0][u] == u or endd[1][u] == 1
    // Or endd[0][u] and endd[1][u] are in the different substree with root u
    if (!flag && low[1][u] < pre[u]) {
        print(u);
        flag = true;
    }
}

int main() {
    freopen("grand.in", "r", stdin);
    freopen("grand.out", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) G[i].clear();
        fill(pre + 1, pre + n + 1, 0);
        fill(vis + 1, vis + n + 1, 0);
        fill(fa + 1, fa + n + 1, 0);
        for (int i = 0; i < 2; i++) {
            fill(low[i] + 1, low[i] + n + 1, 0);
            fill(endd[i] + 1, endd[i] + n + 1, 0);
        }

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            G[u].pb(v);
            G[v].pb(u);
        }

        flag = false;
        for (int i = 1; i <= n; i++)
            if (!vis[i]) {
                dfs_clock = 0;
                dfs(i, 0);
                if (flag) break;
            }

        if (!flag) cout << -1 << '\n';
    }
    return 0;
}
