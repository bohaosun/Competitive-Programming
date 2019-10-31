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

const int N = 112345;
const int Q = 112345;

struct dsu_save {
    int x, szx, y, szy;
};

struct Dsu {
    int fa[N], sz[N];
    stack<dsu_save> s;
    int cnt;

    void init(int n) {
        for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
        cnt = n;
    }

    int find(int x) { return x == fa[x] ? x : find(fa[x]); }

    bool unite(int u, int v) {
        int x = find(u), y = find(v);
        if (x == y) return false;

        if (sz[x] > sz[y]) swap(x, y);
        s.push({ x, sz[x], y, sz[y] });
        fa[x] = y;
        sz[y] += sz[x];
        --cnt;
        return true;
    }

    void roll_back() {
        auto t = s.top(); s.pop();
        fa[t.x] = t.x;
        sz[t.x] = t.szx;
        sz[t.y] = t.szy;
        ++cnt;
    }
};

struct Query {
    bool unite;
    int u, v;
};

int n, m, q;
int last[N];
pii edges[N];
int ans[N];
vector<Query> que[N * 4];
Dsu dsu;

void update(int o, int l, int r, int ql, int qr, int u, int v) {
    if (ql <= l && r <= qr) {
        que[o].pb({ true, u, v });
        return;
    }
    int mid = l + (r - l) / 2;
    if (ql <= mid) update(o * 2, l, mid, ql, qr, u, v);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, u, v);
}

void solve(int o, int l, int r) {
    for (auto &it : que[o]) {
        it.unite = dsu.unite(it.u, it.v);
    }

    if (l == r) ans[l] = dsu.cnt;
    else {
        int mid = l + (r - l) / 2;
        solve(o * 2, l, mid);
        solve(o * 2 + 1, mid + 1, r);
    }

    for (auto &it : que[o]) {
        if (it.unite) dsu.roll_back();
    }
}

int main() {
    freopen("disconnected.in", "r", stdin);
    freopen("disconnected.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    dsu.init(n);
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i]._1 >> edges[i]._2;
    }

    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; ++j) {
            int x;
            cin >> x;
            if (last[x] < i) update(1, 0, q, last[x], i - 1, edges[x]._1, edges[x]._2);
            last[x] = i + 1;
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (last[i] <= q) update(1, 0, q, last[i], q, edges[i]._1, edges[i]._2);
    }

    solve(1, 0, q);

    for (int i = 1; i <= q; ++i) {
        if (ans[i] > 1) cout << "Disconnected\n";
        else cout << "Connected\n";
    }
    return 0;
}
