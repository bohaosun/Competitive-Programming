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
#define ends endd

const int N = 112345;

int n;
vector<int> G[N];
int fa[N], son[N], dep[N], pos[N], ends[N], top[N], sz[N], tot;

int dfs(int u, int pa, int depth) {
    sz[u] = 1;
    fa[u] = pa;
    dep[u] = depth + 1;
    son[u] = -1;

    for (int v : G[u]) {
        sz[u] += dfs(v, u, depth + 1);
        if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
    }
    return sz[u];
}

void dfs2(int u, int tp) {
    top[u] = tp;
    pos[u] = ++tot;
    if (son[u] > -1) dfs2(son[u], tp);

    for (int v : G[u])
        if (v != son[u]) dfs2(v, v);
    ends[u] = tot;
}

int setv[N * 4], sum[N * 4];

int query(int o, int l, int r, int ql, int qr, int val) {
    if (setv[o] > -1) {
        if (setv[o] == val) return min(qr, r) - max(ql, l) + 1;
        else return 0;
    }
    if (ql <= l && r <= qr) {
        if (val == 1) return sum[o];
        else return r - l + 1 - sum[o];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) ans += query(o * 2, l, mid, ql, qr, val);
    if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr, val);
    return ans;
}

void maintain(int o, int l, int r) {
    if (setv[o] == 0) sum[o] = 0;
    else if (setv[o] == 1) sum[o] = r - l + 1;
    else sum[o] = sum[o * 2] + sum[o * 2 + 1];
}

void pushdown(int o) {
    if (setv[o] > -1) {
        setv[o * 2] = setv[o * 2 + 1] = setv[o];
        setv[o] = -1;
    }
}

void update(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        setv[o] = val;
        maintain(o, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(o);
    if (ql <= mid) update(o * 2, l, mid, ql, qr, val); else maintain(o * 2, l, mid);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, val); else maintain(o * 2 + 1, mid + 1, r);
    maintain(o, l, r);
}

int solve(int x) {
    int ans = 0;
    while (top[x]) {
        ans += query(1, 1, n, pos[top[x]], pos[x], 0);
        update(1, 1, n, pos[top[x]], pos[x], 1);
        x = fa[top[x]];
    }
    ans += query(1, 1, n, 1, pos[x], 0);
    update(1, 1, n, 1, pos[x], 1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        G[x].pb(i);
    }
    dfs(0, -1, 0);
    dfs2(0, 0);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        int id;
        cin >> s >> id;
        if (s[0] == 'i') {
            cout << solve(id) << '\n';
        } else {
            cout << query(1, 1, n, pos[id], ends[id], 1) << '\n';
            update(1, 1, n, pos[id], ends[id], 0);
        }
    }
    return 0;
}
