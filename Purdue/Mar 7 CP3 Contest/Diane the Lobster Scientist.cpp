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

const int N = 123;

bool G[N][N];
int n, m;

bool vis[N];

vector<pii> vec;

bool dfs(int u, int fa) {
    if (vis[u]) return false;
    vis[u] = true;
    for (int v = 1; v <= n; v++) {
        if (v != fa && G[u][v]) {
            if (!dfs(v, u)) return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (G[x][y]) { cout << "No Lobster\n"; return 0; }
        G[x][y] = G[y][x] = true;
        vec.pb({ x, y });
    }

    for (auto &it : vec) {
        int x = it._1, y = it._2;
        G[x][y] = G[y][x] = false;
        reset(vis, 0);
        if (!dfs(1, 0)) {
            G[x][y] = G[y][x] = true;
            continue;
        }

        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) { ok = false; break; }
        }
        if (ok) {
            cout << "Lobster\n";
            return 0;
        }
        G[x][y] = G[y][x] = true;
    }

    cout << "No Lobster\n";
    return 0;
}
