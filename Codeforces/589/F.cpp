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

const int N = (1u << 18u);

vector<int> G[N];
int n, dis[N];

void dfs(int u, int fa, int h) {
    dis[u] = h;
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u, h + 1);
    }
}

bool dfs2(int u, int fa, int h, int id, bool pass) {
    dis[u] = h;
    if (u == id) pass = true;
    if (G[u].size() == 1 && !pass) {
        if (dis[u] < n - 1) return false;
    }

    for (int v : G[u]) {
        if (v == fa) continue;
        if (!dfs2(v, u, h + 1, id, pass)) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    if (n == 2) {
        cout << "2\n1 2\n";
        return 0;
    }

    for (int i = 0; i < (1 << n) - 3; ++i) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    int tot = (1 << n) - 2;
    vector<int> d2;
    for (int i = 1; i <= tot; ++i) {
        if (G[i].size() > 4) {
            cout << 0 << '\n';
            return 0;
        }
        if (G[i].size() == 2) d2.pb(i);
    }

    if (d2.size() > 2) {
        cout << 0 << '\n';
        return 0;
    }

    if (d2.size() == 2) {
        int leaves = 0;
        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() == 1) ++leaves;
            if (G[i].size() > 3) {
                cout << 0 << '\n';
                return 0;
            }
        }
        if (leaves != (1 << (n - 1)) - 1) {
            cout << 0 << '\n';
            return 0;
        }

        for (int j = 0; j < 2; ++j) {
            int it = d2[j];
            dfs(it, 0, 0);
            bool ok = true;
            for (int i = 1; i <= tot; ++i) {
                if (G[i].size() == 1 && dis[i] != n - 1) { ok = false; break; }
            }
            if (ok) {
                cout << 1 << '\n' << d2[j ^ 1] << '\n';
                return 0;
            }
        }
        cout << 0 << '\n';
    } else if (d2.size() == 1) {
        int leaves = 0;
        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() == 1) ++leaves;
        }
        if (leaves != (1 << (n - 1))) {
            cout << 0 << '\n';
            return 0;
        }

        int cnt4 = 0;
        int id = -1;
        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() == 4) {
                ++cnt4;
                id = i;
            }
        }

        if (!dfs2(d2[0], 0, 0, id, false)) {
            cout << 0 << '\n';
            return 0;
        }

        int cnt = 0;
        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() > 1) continue;
            if (dis[i] == n - 2) ++cnt;
        }
        if (cnt == (1 << (n - 2 - dis[id]))) cout << "1\n" << id << '\n';
        else cout << 0 << '\n';
    } else {
        // check leaves
        int leaves = 0;
        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() == 1) ++leaves;
        }
        if (leaves != (1 << (n - 1))) {
            cout << 0 << '\n';
            return 0;
        }

        // check deg
        for (int i = 1; i <= n; ++i) {
            if (G[i].size() != 1 && G[i].size() != 3) {
                cout << 0 << '\n';
                return 0;
            }
        }

        // check dis
        reset(dis, -1);
        queue<int> q;

        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() == 1) {
                q.push(i);
                dis[i] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : G[u]) {
                if (dis[v] > -1) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }

        vector<int> vec;
        int maxm = -1;
        for (int i = 1; i <= tot; ++i) maxm = max(maxm, dis[i]);
        for (int i = 1; i <= tot; ++i) {
            if (dis[i] == maxm) vec.pb(i);
        }
        if (vec.size() != 2) {
            cout << 0 << '\n';
            return 0;
        }

        for (int v : G[vec[0]]) {
            if (v != vec[1]) dfs(v, vec[0], 0);
        }
        for (int v : G[vec[1]]) {
            if (v != vec[0]) dfs(v, vec[1], 0);
        }

        for (int i = 1; i <= tot; ++i) {
            if (G[i].size() > 1) continue;
            if (dis[i] != n - 3) {
                cout << 0 << '\n';
                return 0;
            }
        }

        cout << "2\n" << vec[0] << ' ' << vec[1] << '\n';
    }
    return 0;
}
