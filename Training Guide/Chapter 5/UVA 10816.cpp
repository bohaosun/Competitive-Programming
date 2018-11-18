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

const int N = 100 + 10;
const int INF = int(1e9);

struct Edge {
    int to;
    double d, t;
};

vector<Edge> edges;
vector<int> G[N];
int p[N];
double d[N];

int n, m, s, t;
vector<double> tem;

struct Node {
    int u;
    double d;
    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

double check(double val) {
    priority_queue<Node> pq;
    fill(d + 1, d + n + 1, INF);
    d[s] = 0;
    p[s] = 0;
    pq.push({ s, 0 });
    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (d[u.u] < u.d) continue;
        for (int i = 0; i < G[u.u].size(); i++) {
            Edge& e = edges[G[u.u][i]];
            if (e.t > val) continue;
            if (d[e.to] > d[u.u] + e.d) {
                d[e.to] = d[u.u] + e.d;
                p[e.to] = u.u;
                pq.push({ e.to, d[e.to]});
            }
        }
    }
    return d[t];
}

void print_path() {
    int cur = t;
    vector<int> ans;
    while (cur != s) {
        ans.pb(cur);
        cur = p[cur];
    }
    ans.pb(s);
    reverse(all(ans));
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++) cout << ' ' << ans[i];
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m) {
        cin >> s >> t;
        edges.clear();
        tem.clear();
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v;
            double t, d;
            cin >> u >> v >> t >> d;
            G[u].pb(edges.size());
            edges.pb({ v, d, t });
            G[v].pb(edges.size());
            edges.pb({ u, d, t });
            tem.pb(t);
        }

        sort(all(tem));
        uni(tem);
        int l = 0, r = tem.size();
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (check(tem[mid]) < INF) r = mid;
            else l = mid + 1;
        }

        double len = check(tem[l]);
        print_path();
        cout << fixed;
        cout.precision(1);
        cout << len << ' ' << tem[l] << '\n';
    }
    return 0;
}
