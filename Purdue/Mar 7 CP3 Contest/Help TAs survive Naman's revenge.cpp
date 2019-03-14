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

const int N = 50000 + 10;
const int INF = int(1e9);

int n, m, k, s, t;
int ans;

struct Edge {
    int from, to, cap, flow, cost;  
    Edge(int u, int v, int c, int f, int w): from(u), to(v), cap(c), flow(f), cost(w) {}
};

struct MCMF {            
    int n, m;
    vector<Edge> edges;
    vector<int> G[N];
    bool inq[N];
    int d[N];
    int p[N];
    int a[N];            

    void init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int& flow, LL& cost) {
        for(int i = 0; i < n; i++) { d[i] = INF; inq[i] = false; }
        d[s] = 0; inq[s] = true; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = false;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) { inq[e.to] = true; Q.push(e.to); }
                }
            }
        }
        if(d[t] == INF) return false;
        flow += a[t];
        cost += (LL)d[t] * (LL)a[t];
        //cout << d[t] << ' ' << a[t] << endl;
        ans = max(ans, d[t]);
        for(int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
        }
        return true;
    }

    int MincostMaxflow(int s, int t, LL& cost) {
        int flow = 0; cost = 0;
        while(BellmanFord(s, t, flow, cost));
        return flow;
    }
};

MCMF solver;

const int T = 105;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> s >> t;
    --s; --t;

    solver.init(n * T + 5);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < T; j++) {
            solver.AddEdge(i * T + j, i * T + j + 1, 100, 1);
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        for (int j = 0; j < T; j++) {
            solver.AddEdge(x * T + j, y * T + j + 1, 1, 1);
            solver.AddEdge(y * T + j, x * T + j + 1, 1, 1);
        }
    }


    int S = n * T;
    int SS = n * T + 1;

    solver.AddEdge(S, s * T, k, 0);

    for (int i = 0; i < T; i++) solver.AddEdge(t * T + i, SS, 100, 0);

    LL cost = 0;
    solver.MincostMaxflow(S, SS, cost);
    cout << ans << '\n';
    return 0;
}
