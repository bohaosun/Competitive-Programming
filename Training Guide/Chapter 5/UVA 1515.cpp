/*
 * Good problem for Min CUT
 * For the out most vertices, connect s--INF->v.
 * For other '#', connect s--d->v and for other '.', connect v--f->t.
 * Connect adjacent vertices by --b->
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

const int N = 2500 + 10;
const int INF = int(1e9);
const int H = 50 + 10;

struct Dinic { // 不能有负cap
    struct Edge {
        int from, to, cap, flow;

        Edge(int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}
    };

    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    bool vis[N];         
    int d[N];            
    int cur[N];          

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
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
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {  
                    vis[e.to] = true;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {  
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); i++) {  
            Edge &e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
};

Dinic solver;
int w, h, d, f, b;
string s[H];

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, -1, 0, 1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> w >> h >> d >> f >> b;
        int ans = 0;
        for (int i = 0; i < h; i++) cin >> s[i];

        solver.init(w * h + 5);
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (i == 0 || j == 0 || i == h - 1 || j == w - 1) {
                    ans += f * (s[i][j] == '.');
                    solver.AddEdge(w * h, i * w + j, INF);
                }
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++) {
                for (int dir = 0; dir < 4; dir++) {
                    int r = i + dr[dir], c = j + dc[dir];
                    if (r < 0 || c < 0 || r >= h || c >= w) continue;
                    solver.AddEdge(i * w + j, r * w + c, b);
                }

                if (i == 0 || j == 0 || i == h - 1 || j == w - 1) continue;
                if (s[i][j] == '#') solver.AddEdge(w * h, i * w + j, d);
                else solver.AddEdge(i * w + j, w * h + 1, f);
            }
        cout << ans + solver.Maxflow(w * h, w * h + 1) << '\n';
    }
    return 0;
}
