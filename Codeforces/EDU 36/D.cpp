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
typedef pair <LL, LL> pll;
// Head

const int N = 512;

bool G[N][N];
int n, m;

int vis[N];
bool has_circle;
stack<int> pts;
vector<int> circle;

bool dfs(int u, bool search) {
    vis[u] = -1;
    if (search) pts.push(u);

    for (int v = 1; v <= n; v++) {
        if (G[u][v]) {
            if (!vis[v] && !dfs(v, search)) return false;
            else if (vis[v] == -1) {
                if (search) {
                    circle.pb(v);
                    while (!pts.empty()) {
                        int cur = pts.top(); pts.pop();
                        circle.pb(cur);
                        if (cur == v) break;
                    }
                }
                return false;
            }
        }
    }

    vis[u] = 1;
    if (search) pts.pop();
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        G[x][y] = true;
    }


    for (int i = 1; i <= n; i++) {
        if (!vis[i] && !dfs(i, true)) { has_circle = true; break; }
    }

    if (!has_circle) { cout << "YES\n"; return 0; }

    reverse(all(circle));
    for (int i = 0; i < circle.size() - 1; i++) {
        bool ok = true;
        int u = circle[i], v = circle[i + 1];
        G[u][v] = false;
        reset(vis, 0);

        for (int j = 1; j <= n; j++) {
            if (!vis[j] && !dfs(j, false)) { ok = false; break; }
        }
        if (ok) { cout << "YES\n"; return 0; }
        G[u][v] = true;
    }

    cout << "NO\n";
    return 0;
}
