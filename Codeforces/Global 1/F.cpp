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

const int N = 512345;
const LL INF = LL(1e18);

int n, q;
vector<pii> G[N];

struct Query {
    int u, l, r, id;
    bool operator < (const Query &rhs) const {
        return u < rhs.u;
    }
};
vector<Query> query;

LL d[N];
int tail[N], fa[N][2];

LL ans[N];

int dfs(int u, LL acc) {
    if (G[u].empty()) {
        d[u] = acc;
        tail[u] = u;
        return u;
    }

    tail[u] = u;
    d[u] = INF;
    for (pii v : G[u]) {
        tail[u] = max(tail[u], dfs(v._1, acc + v._2));
    }
    return tail[u];
}

LL minm[N * 4], add[N * 4];

void build(int o, int l, int r) {
    if (l == r) {
        minm[o] = add[o] = d[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);
    minm[o] = min(minm[o * 2], minm[o * 2 + 1]);
}

LL ask(int o, int l, int r, int ql, int qr, LL acc) {
    if (ql <= l && r <= qr) {
        return minm[o] + acc;
    }

    int mid = l + (r - l) / 2;
    LL cur = INF;
    if (ql <= mid) cur = min(cur, ask(o * 2, l, mid, ql, qr, acc + add[o]));
    if (qr > mid) cur = min(cur, ask(o * 2 + 1, mid + 1, r, ql, qr, acc + add[o]));
    return cur;
}

void update(int o, int l, int r, int ql, int qr, int addv) {
    if (ql <= l && r <= qr) {
        add[o] += addv;
        minm[o] += addv;
        return;
    }

    int mid = l + (r - l) / 2;
    if (ql <= mid) update(o * 2, l, mid, ql, qr, addv);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, addv);
    minm[o] = min(minm[o * 2], minm[o * 2 + 1]) + add[o];
}

// Important!!! Need a binary search to find the id or TLE!!!
int my_find(int idx, int aim) {  // Find id such that id is the first one id > aim
    int l = 0, r = G[idx].size();
    while (l < r) {
        int mid = (l + r) / 2;
        int id = G[idx][mid].first;
        if (id <= aim) l = mid + 1;
        else r = mid;
    }
    return l - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb({ i, y });
        fa[i][0] = x;
        fa[i][1] = y;
    }

    dfs(1, 0);
    build(1, 1, n);

    //for (int i = 1; i <= n; i++) cout << i << ' ' << tail[i] << endl;


    for (int i = 0; i < q; i++) {
        int u, l, r;
        cin >> u >> l >> r;
        query.pb({ u, l, r, i });
    }

    sort(all(query));
    int cur = 1;
    for (int i = 0; i < query.size(); i++) {
        int u = query[i].u, l = query[i].l, r = query[i].r, id = query[i].id;
        //cout << u << ":\n";
        while (cur != u) {
            //cout << cur << endl;
            if (tail[cur] < u) {
                update(1, 1, n, cur, tail[cur], fa[cur][1]);
                if (1 < cur) update(1, 1, n, 1, cur - 1, -fa[cur][1]);
                if (n > tail[cur]) update(1, 1, n, tail[cur] + 1, n, -fa[cur][1]);
                cur = fa[cur][0];
            } else {
                int idx = my_find(cur, u);
                pii it = G[cur][idx];
                int l2 = it._1, r2 = tail[it._1];

                update(1, 1, n, l2, r2, -it._2);
                if (1 < l2) update(1, 1, n, 1, l2 - 1, it._2);
                if (n > r2) update(1, 1, n, r2 + 1, n, it._2);
                cur = l2;
            }
        }
        ans[id] = ask(1, 1, n, l, r, 0);
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}
