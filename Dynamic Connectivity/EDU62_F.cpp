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
const int delta = 300000;

struct dsu_save {
    int x, szx, y, szy;
    pii valx, valy;
};

struct Dsu {
    int fa[N * 2], sz[N * 2];
    stack<dsu_save> s;
    pii val[N * 2];
    LL ans;

    void init() {
        for (int i = 1; i <= delta; ++i) {
            val[i] = { 1, 0 };
            fa[i] = i;
            sz[i] = 1;
        }
        for (int i = delta + 1; i <= 600000; ++i) {
            val[i] = { 0, 1 };
            fa[i] = i;
            sz[i] = 1;
        }
        ans = 0;
    }

    int find(int x) { return x == fa[x] ? x : find(fa[x]); }

    bool unite(int u, int v) {
        int x = find(u), y = find(v);
        if (x == y) return false;

        if (sz[x] > sz[y]) swap(x, y);
        s.push({ x, sz[x], y, sz[y], val[x], val[y] });
        fa[x] = y;
        sz[y] += sz[x];
        ans -= LL(val[x]._1) * val[x]._2;
        ans -= LL(val[y]._1) * val[y]._2;
        val[y]._1 += val[x]._1;
        val[y]._2 += val[x]._2;
        ans += LL(val[y]._1) * val[y]._2;
        return true;
    }

    void roll_back() {
        auto t = s.top(); s.pop();
        fa[t.x] = t.x;
        sz[t.x] = t.szx;
        sz[t.y] = t.szy;
        ans -= LL(val[t.y]._1) * val[t.y]._2;
        val[t.x] = t.valx;
        val[t.y] = t.valy;
        ans += LL(val[t.x]._1) * val[t.x]._2;
        ans += LL(val[t.y]._1) * val[t.y]._2;
    }
};

struct Query {
    bool unite;
    int u, v;
};

LL ans[N];
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

    if (l == r) ans[l] = dsu.ans;
    else {
        int mid = l + (r - l) / 2;
        solve(o * 2, l, mid);
        solve(o * 2 + 1, mid + 1, r);
    }

    for (auto &it : que[o]) {
        if (it.unite) dsu.roll_back();
    }
}

map<pii, int> last;
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dsu.init();

    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        if (!last.count(mp(x, y))) last[mp(x, y)] = i;
        else {
            update(1, 1, n, last[mp(x, y)], i - 1, x, y + delta);
            last.erase(mp(x, y));
        }
    }

    for (auto &it : last) {
        update(1, 1, n, it._2, n, it._1._1, it._1._2 + delta);
    }

    solve(1, 1, n);
    for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
    return 0;
}
