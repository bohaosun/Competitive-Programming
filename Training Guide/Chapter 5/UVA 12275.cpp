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

const int N = 350 + 10;
const int M = N * N;

int n, m, fa[N], sz[N];
bool vis[M];
multiset<int> val;

struct Edge {
    int u, v, w;
    bool operator < (const Edge& rhs) const {
        return w < rhs.w;
    }
};
vector<Edge> edges;
vector<int> G[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int solve_MST() {
    for (int i = 0; i < n; i++) { fa[i] = i; sz[i] = 1; }
    int maxm = 0;
    for (int i = 0; i < m; i++) {
        int x = find(edges[i].u), y = find(edges[i].v), w = edges[i].w;
        if (x == y) continue;

        if (sz[x] < sz[y]) fa[x] = y;
        else fa[y] = x;
        maxm = max(maxm, w);
        vis[i] = true;
        G[edges[i].u].pb(i);
        G[edges[i].v].pb(i);
        val.insert(w);
    }
    return maxm - edges[0].w;
}

int dfs(int u, int aim, int pa) {
    if (u == aim) return -5;
    for (int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        int v = e.v;
        if (v == u) v = e.u;
        if (v == pa) continue;

        int tmp = dfs(v, aim, u);
        if (tmp == -1) continue;

        if (tmp == -5) return G[u][i];
        else {
            if (e.w < edges[tmp].w) return G[u][i];
            else return tmp;
        }
    }
    return -1;
}

int solve(int id) {
    int u = edges[id].u, v = edges[id].v, w = edges[id].w;
    int del = dfs(u, v, -1);
    //cout << id << ' ' << del << endl;
    int x = edges[del].u, y = edges[del].v;
    G[x].erase(find(all(G[x]), del));
    G[y].erase(find(all(G[y]), del));
    G[u].pb(id);
    G[v].pb(id);
    val.erase(val.find(edges[del].w));
    val.insert(w);

    return *prev(val.end()) - *val.begin();
}

// 类似尺取法
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        cin >> m;

        edges.clear();
        val.clear();
        for (int i = 0; i < n; i++) G[i].clear();

        for (int i = 0; i < m; i++) {
            vis[i] = false;
            int x, y, z;
            cin >> x >> y >> z;
            edges.pb({ x, y, z });
        }
        sort(all(edges));

        //for (int i = 0; i < m; i++) cout << edges[i].u << ' ' << edges[i].v << ' ' << edges[i].w << endl;

        int ans = solve_MST();
        for (int i = 0; i < m; i++) {
            if (vis[i]) continue;
            ans = min(ans, solve(i));
        }
        cout << ans << '\n';
    }
    return 0;
}
