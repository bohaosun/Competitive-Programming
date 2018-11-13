/*
 * d[0][i]: the distance from 1 to i
 * d[1][i]: the distance from i to 2
 * Construct the graph only contains the edges on the shortest paths from 1 to 2 and find the bridges.
 */
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

const int N = 123456;

vector<int> G[2][N];
LL d[2][N];
int n, m;

struct Edge {
    int from, to, w;
};

struct Node {
    int u;
    LL d;

    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

vector<Edge> edges[2];

void add_edge(int u, int v, int dis) {
    G[0][u].pb(edges[0].size());
    edges[0].pb({ u, v, dis });
    G[1][v].pb(edges[1].size());
    edges[1].pb({ v, u, dis });
}

void Dijkstra() {
    reset(d, 0x3f);
    d[0][1] = 0;
    priority_queue<Node> pq;
    pq.push({ 1, 0 });

    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (u.d > d[0][u.u]) continue;
        for (int idx : G[0][u.u]) {
            Edge& e = edges[0][idx];
            if (d[0][e.to] > d[0][u.u] + e.w) {
                d[0][e.to] = d[0][u.u] + e.w;
                pq.push({ e.to, d[0][e.to] });
            }
        }
    }

    d[1][2] = 0;
    pq.push({ 2, 0 });
    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (u.d > d[1][u.u]) continue;
        for (int idx : G[1][u.u]) {
            Edge& e = edges[1][idx];
            if (d[1][e.to] > d[1][u.u] + e.w) {
                d[1][e.to] = d[1][u.u] + e.w;
                pq.push({ e.to, d[1][e.to] });
            }
        }
    }
}

bool in_new[N];
vector<pii> NG[N];

void build_NG() {
    for (int i = 0; i < edges[0].size(); i++) {
        Edge& e = edges[0][i];
        int u = e.from, v = e.to, w = e.w;
        if (d[0][u] + w + d[1][v] == d[0][2]) {
            NG[u].pb({ v, i });
            NG[v].pb({ u, i });
            in_new[i] = true;
        }
    }
}

int pre[N], dfs_clock;
bool bridge[N];

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    for (int i = 0; i < NG[u].size(); i++) {
        int v = NG[u][i]._1;
        if (!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv > pre[u]) bridge[NG[u][i]._2] = true;
        } else if (pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return lowu;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, dis;
        cin >> u >> v >> dis;
        add_edge(u, v, dis);
    }

    Dijkstra();
    build_NG();
    dfs(1, 0);

    for (int i = 0; i < m; i++) {
        int u = edges[0][i].from, v = edges[0][i].to, w = edges[0][i].w;
        if (d[0][v] < d[0][u] + w) {
            if (d[0][v] + w + d[1][u] < d[0][2]) cout << "HAPPY\n";
            else cout << "SOSO\n";
        } else {
            if (!in_new[i]) cout << "SOSO\n";
            else {
                if (bridge[i]) cout << "SAD\n";
                else cout << "SOSO\n";
            }
        }
    }
    return 0;
}
