// Important Problem
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

typedef unsigned long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const LL all0 = 0;
const LL all1 = -1;

const int N = 112345;

int n, m;
int fa[N], son[N], dep[N], pos[N], top[N], sz[N], tot, back[N];
vector<int> G[N];
pair<int, LL> a[N];

int dfs(int u, int pa, int depth) {
    fa[u] = pa;
    sz[u] = 1;
    dep[u] = depth;

    for (int v : G[u])
        if (v != pa) {
            sz[u] += dfs(v, u, depth + 1);
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    return sz[u];
}

void dfs2(int u, int tp) {
    //cout << u << endl;
    top[u] = tp;
    pos[u] = ++tot;
    back[tot] = u;
    if (son[u]) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}

struct Node{
    LL f0, f1, inv0, inv1;
};

Node ans[N * 4];

Node put_val(const Node& l, const Node& r) {
    Node ret;
    ret.f0 = ((l.f0 & r.f1) | ((~l.f0) & r.f0));
    ret.f1 = ((l.f1 & r.f1) | ((~l.f1) & r.f0));
    ret.inv0 = ((r.inv0 & l.inv1) | ((~r.inv0) & l.inv0));
    ret.inv1 = ((r.inv1 & l.inv1) | ((~r.inv1) & l.inv0));
    return ret;
}

LL calc(LL num, pair<int, LL> cur) {
    if (cur._1 == 1) return num & cur._2;
    if (cur._1 == 2) return num | cur._2;
    return num ^ cur._2;
}

void build(int o, int l, int r) {
    if (l == r) {
        ans[o].f0 = ans[o].inv0 = calc(all0, a[back[l]]);
        ans[o].f1 = ans[o].inv1 = calc(all1, a[back[l]]);
        return;
    }

    int mid = (l + r) >> 1;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);
    ans[o] = put_val(ans[o * 2], ans[o * 2 + 1]);
}

void update(int o, int l, int r, int loc, pair<int, LL> change) {
    if (l == r) {
        ans[o].f0 = ans[o].inv0 = calc(all0, change);
        ans[o].f1 = ans[o].inv1 = calc(all1, change);
        return;
    }

    int mid = (l + r) >> 1;
    if (loc <= mid) update(o * 2, l, mid, loc, change);
    else update(o * 2 + 1, mid + 1, r, loc, change);
    ans[o] = put_val(ans[o * 2], ans[o * 2 + 1]);
}

Node query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return ans[o];
    int mid = (l + r) >> 1;
    Node ret;
    Node lans = { all0, all1, all0, all1 };
    Node rans = { all0, all1, all0, all1 };

    if (ql <= mid) lans = query(o * 2, l, mid, ql, qr);
    if (qr > mid) rans = query(o * 2 + 1, mid + 1, r, ql, qr);
    ret = put_val(lans, rans);
    return ret;
}

vector<Node> l;
vector<Node> r;

LL solve_query(int x, int y, LL maxm) {
    l.clear();
    r.clear();
    while (top[x] != top[y]) {
        int tx = top[x], ty = top[y];
        if (dep[tx] > dep[ty]) {
            l.pb(query(1, 1, n, pos[tx], pos[x]));
            x = fa[tx];
        } else {
            r.pb(query(1, 1, n, pos[ty], pos[y]));
            y = fa[ty];
        }
    }

    if (dep[x] < dep[y]) r.pb(query(1, 1, n, pos[x], pos[y]));
    else l.pb(query(1, 1, n, pos[y], pos[x]));
    reverse(all(r));

    LL final0 = all0, final1 = all1;
    for (Node u : l) {
        final0 = (~final0 & u.inv0) | (final0 & u.inv1);
        final1 = (~final1 & u.inv0) | (final1 & u.inv1);
    }
    for (Node u : r) {
        final0 = (~final0 & u.f0) | (final0 & u.f1);
        final1 = (~final1 & u.f0) | (final1 & u.f1);
    }

    LL ret = 0;
    /*while (cur > maxm) {
        ret |= final0 & cur;
        cur >>= 1;
    }
    bool equal = true;
    while (cur) {
        if (!equal) {
            if ((final0 & cur) || (final1 & cur)) ret |= cur;
        } else {
            if (!(cur & maxm)) {
                ret |= (final0 & cur);
            } else {
                if (final0 & cur) {
                    ret |= cur;
                    equal = false;
                } else {
                    if (!(final1 & cur)) equal = false;
                    else ret |= cur;
                }
            }
        }
        cur >>= 1;
    }*/
    for (LL cur = 1ull << 63; cur; cur >>= 1) {
        LL tmp0 = final0 & cur;
        LL tmp1 = final1 & cur;
        if (tmp0 >= tmp1 || cur > maxm) ret |= cur & final0;
        else { ret |= cur; maxm -= cur; }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int k;
    cin >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]._1 >> a[i]._2;
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    dfs(1, 0, 0);
    dfs2(1, 1);
    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        int id, x, y;
        LL z;
        cin >> id >> x >> y >> z;
        if (id == 1) {
            cout << solve_query(x, y, z) << '\n';
        } else {
            update(1, 1, n, pos[x], mp(y, z));
        }
    }
    return 0;
}
