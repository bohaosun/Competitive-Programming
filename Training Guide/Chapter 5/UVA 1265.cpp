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

const int N = 5123;
const int INF = int(1e9);

int n, m, fa[N], sz[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

struct Edge {
    int u, v, w;
    bool operator < (const Edge& rhs) const {
        return w > rhs.w;
    }
};
vector<Edge> edges;

bool judge(int id) {
    int minm = INF;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int x = find(u), y = find(v);
        if (x == id && y == id) minm = min(minm, w);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int x = find(u), y = find(v);
        if (x == id && y == id) continue;
        if ((x == id || y == id) && w >= minm) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) { fa[i] = i; sz[i] = 1; }
        edges.clear();
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.pb({ u, v, w });
        }

        sort(all(edges));

        //for (int i = 0; i < edges.size(); i++) cout << edges[i].w << endl;
        int ans = 0;
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i].u, v = edges[i].v;
            int x = find(u), y = find(v);
            if (x == y) continue;
            fa[x] = y;
            sz[y] += sz[x];
            if (judge(y)) {
                //cout << x << ' ' << y << endl;
                ans += sz[y];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
