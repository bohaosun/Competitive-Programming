#include <bits/stdc++.h>

#define _1 first
#define _2 second
#define pb push_back
#define mp make_pair
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 312345;

vector<pii> G[N];
LL d[N];
vector<pii> vec[N];

struct Edge {
    int u, v;
    LL e;
    bool operator<(const Edge& rhs) const {
        return e < rhs.e;
    }
};
vector<Edge> edges;

int k, n, m, q;
LL ans[N];
int fa[N], rk[N];

int find(int x) { return fa[x] == x ? x: fa[x] = find(fa[x]); }

struct Node {
    int u;
    LL d;
    bool operator<(const Node &rhs) const {
        return d > rhs.d;
    }
};

void Dijkstra() {
    reset(d, 0x3f);
    priority_queue<Node> pq;
    for (int i = 1; i <= k; ++i) {
        d[i] = 0;
        pq.push({ i, 0 });
    }

    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        for (auto &it : G[u.u]) {
            int v = it._1;
            if (d[v] > d[u.u] + it._2) {
                d[v] = d[u.u] + it._2;
                pq.push({ v, d[v] });
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> q;
    for (int i = 0; i < m; ++i) {
        int x, y, e;
        cin >> x >> y >> e;
        edges.pb({ x, y, e });
        G[x].pb({ y, e });
        G[y].pb({ x, e });
    }

    Dijkstra();

    for (auto &it : edges) {
        it.e = d[it.u] + d[it.v] + it.e;
    }
    sort(all(edges));

    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        vec[x].pb({ y, i });
        vec[y].pb({ x, i });
    }

    for (int i = 1; i <= n; ++i) fa[i] = i, rk[i] = 1;

    for (auto &it : edges) {
        int u = it.u, v = it.v;
        int x = find(u), y = find(v);
        if (x == y) continue;
        if (rk[x] > rk[y]) swap(x, y);

        for (auto &p : vec[x]) {
            if (find(p._1) == y) ans[p._2] = it.e;
        }
        vec[y].insert(vec[y].end(), all(vec[x]));
        fa[x] = y;
        rk[y] += rk[x];
    }

    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}
