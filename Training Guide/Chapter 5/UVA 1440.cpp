/*
 * Calculate the minimum feasible flow.
 * Cannot assume all flow are from the top to bottom otherwise TLE!
 * Got 2 TLEs.
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

const int N = 200 + 10;
const int INF = int(1e9);
const int VAL = 10000;

struct Dinic {
    struct Edge {
        int from, to, cap, flow;
        Edge(int from, int to, int cap, int flow): from(from), to(to), cap(cap), flow(flow) {}
    };

    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    bool vis[N];
    int d[N];
    int cur[N];

    void init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[to].push_back(m - 1);
        G[from].push_back(m - 2);
    }

    bool BFS() {
        memset(vis, false, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = true;
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = true;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t) {
        this->s = s; this->t = t;
        int flow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }

    void Mincut(vector<int>& ans) {
        BFS();
        for(int i = 0; i < m; i++) {
            Edge& e = edges[i];
            if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
        }
    }

};

Dinic solver;

int n, in[N], out[N], supply[N];
int G[N][N];

void dfs(int u, int val, vector<int>& vec) {
    vec.pb(u);

    for (int i = 1; i <= n; i++) {
        if (!val) break;
        if (!G[u][i]) continue;
        if (G[u][i] < val) {
            dfs(i, G[u][i], vec);
            val -= G[u][i];
            G[u][i] = 0;
        } else {
            dfs(i, val, vec);
            G[u][i] -= val;
            val = 0;
        }
    }

    if (val) {
        cout << vec[0];
        for (int i = 1; i < vec.size(); i++) cout << ' ' << vec[i];
        cout << '\n';
    }
    vec.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        reset(G, 0);
        reset(in, 0);
        reset(supply, 0);
        solver.init(n + 10);
        int s = n + 1, t = n + 2, ss = n + 3, tt = n + 4;
        for (int i = 1; i <= n; i++) {
            int sz;
            cin >> sz;
            out[i] = sz;
            for (int j = 0; j < sz; j++) {
                int x;
                cin >> x;
                in[x]++;
                G[i][x] = 1;
                solver.AddEdge(i, x, VAL);
            }
        }

        for (int i = 1; i <= n; i++) {
            int cur = in[i] - out[i];
            if (cur < 0) solver.AddEdge(i, tt, -cur);
            else if (cur > 0) solver.AddEdge(ss, i, cur);
        }


        for (int i = 1; i <= n; i++) {
            solver.AddEdge(s, i, VAL);
            solver.AddEdge(i, t, VAL);
        }
        solver.AddEdge(t, s, INF);

        solver.Maxflow(ss, tt);
        solver.edges.pop_back();
        solver.edges.pop_back();
        solver.Maxflow(t, s);
        int ans = 0;
        for (int i = 0; i < solver.m; i += 2) {
            int u = solver.edges[i].from, v = solver.edges[i].to, f = solver.edges[i].flow;
            if (u == s && v >= 1 && v <= n) { ans += f; supply[v] += f; }
            else if (u >= 1 && u <= n && v >= 1 && v <= n && f) G[u][v] = f + 1;
        }

        cout << ans << '\n';
        vector<int> vec;

        for (int i = 1; i <= n; i++)
            if (supply[i]) dfs(i, supply[i], vec);
    }
    return 0;
}
