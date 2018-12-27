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

const int N = 3123;
const int INF = int(2e9);

int n, m, d[N][N], g[N][N];
bool in[N][N];
vector<int> G[N];  // MST

struct Edge {
    int u, v, w;
    bool operator < (const Edge& rhs) const {
        return w < rhs.w;
    }
};

vector<Edge> edges;

void init() {
    reset(d, 0x3f);
    reset(g, 0x3f);
    reset(in, 0);
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
}

int fa[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int solve_MST() {
    for (int i = 0; i < n; i++) fa[i] = i;
    sort(all(edges));
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int x = find(u), y = find(v);
        if (x == y) continue;
        fa[x] = y;
        G[u].pb(v);
        G[v].pb(u);
        in[u][v] = in[v][u] = true;
        ans += w;
    }
    return ans;
}

// Return the minm edge connects root and the subtree of u  ***Important Method***
int dfs(int root, int u, int pa) {
    int ret = INF;

    for (int v : G[u])
        if (v != pa) {
            int tmp = dfs(root, v, u);
            ret = min(ret, tmp);
            g[u][v] = g[v][u] = min(g[u][v], tmp);
        }

    if (pa != root) ret = min(ret, d[root][u]);
    return ret;
}

/*
 * 1. One observation: Denote the MST found by Kruskal's Algorithm by M. Then for a MST not passing an edge in M can be
 * calculated by delete that edge and add the minm edge cross the two sets.
 * 2. The remaining problem is to calculate the minm edge cross every two sets separated by deleting an edge in M, which
 * can be done by DP with O(n^2). ***Important Method***
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m && n) {
        init();
        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            d[x][y] = d[y][x] = z;
            edges.pb({ x, y, z });
        }

        int MST = solve_MST();

        for (int i = 0; i < n; i++) {
            dfs(i, i, -1);
        }

        int q;
        cin >> q;
        LL ans = 0;
        for (int i = 0; i < q; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            if (!in[x][y]) ans += MST;
            else ans += MST - d[x][y] + min(z, g[x][y]);
        }

        cout << fixed;
        cout.precision(4);
        assert(q != 0);
        cout << double(ans) / q << '\n';
    }
    return 0;
}
