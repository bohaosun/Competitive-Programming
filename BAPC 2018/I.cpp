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

const int N = 212345;
const LL INF = LL(1e18);

int n, m, s, ppl[N];
vector<pii> source;
vector<pii> G[N];

LL d[N][15], tot;

struct Node {
    int u;
    LL d;
    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

void Dijkstra(int id) {
    int s = source[id]._1;
    for (int i = 1; i <= n; i++) d[i][id] = INF;
    d[s][id] = 0;
    priority_queue<Node> pq;
    pq.push({ s, 0 });
    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (d[u.u][id] < u.d) continue;
        for (int i = 0; i < G[u.u].size(); i++) {
            int v = G[u.u][i]._1;
            LL dis = G[u.u][i]._2;
            if (d[u.u][id] + dis < d[v][id]) {
                d[v][id] = d[u.u][id] + dis;
                pq.push({ v, d[v][id] });
            }
        }
    }
}

struct Dinic { // 不能有负cap
    struct Edge {
        int from, to;
        LL cap, flow;
        Edge(int from, int to, LL cap, LL flow): from(from), to(to), cap(cap), flow(flow) {}
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

    void AddEdge(int from, int to, LL cap) {
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

    LL DFS(int x, LL a) {  
        if(x == t || a == 0) return a;
        LL flow = 0, f;
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

    LL Maxflow(int s, int t) {
        this->s = s; this->t = t;
        LL flow = 0;
        while(BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
};
Dinic solver;

LL cap[1 << 11];
bool check(LL val) {
    reset(cap, 0);
    solver.init(2000);
    int ALL = (1 << s);
    int S = ALL + s, T = ALL + s + 1;

    for (int i = 0; i < s; i++) solver.AddEdge(S, ALL + i, source[i]._2);
    for (int mask = 0; mask < ALL; mask++)
        for (int j = 0; j < s; j++)
            if ((1 << j) & mask) {
                solver.AddEdge(ALL + j, mask, INF);
            }

    for (int i = 1; i <= n; i++) {
        int cur = 0;
        for (int j = 0; j < s; j++)
            if (d[i][j] <= val) cur |= (1 << j);
        cap[cur] += ppl[i];
    }

    for (int mask = 0; mask < ALL; mask++)
        if (cap[mask]) solver.AddEdge(mask, T, cap[mask]);
    return solver.Maxflow(S, T) == tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) { cin >> ppl[i]; tot += ppl[i]; }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].pb({ v, w });
        G[v].pb({ u, w });
    }
    for (int i = 0; i < s; i++) {
        int si, ci;
        cin >> si >> ci;
        source.pb({ si, ci });
    }

    for (int i = 0; i < source.size(); i++) {
        Dijkstra(i);
    }

    LL l = 0, r = LL(1e15);
    while (l < r) {
        LL mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
    return 0;
}
