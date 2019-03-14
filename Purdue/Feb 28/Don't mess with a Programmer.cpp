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

const int N = 500 * 2 + 10;
const int INF = int(1e9);

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
};

Dinic solver;
int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m && n) {
        solver.init(n * 2 + 5);

        for (int i = 0; i < n - 2; i++) {
            int id, c;
            cin >> id >> c;
            solver.AddEdge(id, id + n, c);
        }

        for (int i = 0; i < m; i++) {
            int x, y, d;
            cin >> x >> y >> d;
            if (x != 1) x += n;
            solver.AddEdge(x, y, d);
            if (x != 1) x -= n;
            if (y != 1) y += n;
            solver.AddEdge(y, x, d);
        }

        cout << solver.Maxflow(1, n) << '\n';
    }
    return 0;
}
