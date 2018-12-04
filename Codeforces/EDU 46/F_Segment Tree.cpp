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

const int N = 512345;
const int INF = int(1e9);

int n, a[N], lef[N], last[N], ret[N];
pii val[N * 4];

struct Query {
    int l, r, id;
    bool operator < (const Query& rhs) const {
        return r < rhs.r;
    }
};
vector<Query> Q;

void build(int o, int l, int r) {
    val[o] = mp(INF, 0);
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);
}

void update(int o, int l, int r, int pos, pii change) {
    //cout << o << ' ' << l << ' ' << r << endl;
    if (l == r) {
        val[o] = change;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(o * 2, l, mid, pos, change);
    else update(o * 2 + 1, mid + 1, r, pos, change);

    val[o] = min(val[o * 2], val[o * 2 + 1]);
}

pii query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return val[o];
    int mid = (l + r) >> 1;
    pii ans(INF, 0);
    if (ql <= mid) ans = min(ans, query(o * 2, l, mid, ql, qr));
    if (qr > mid) ans = min(ans, query(o * 2 + 1, mid + 1, r, ql, qr));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        lef[i] = last[a[i]];
        last[a[i]] = i;
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        Q.pb({ l, r, i });
    }
    sort(all(Q));

    build(1, 1, n);
    int cur = 0;
    for (int i = 0; i < q; i++) {
        int pos = Q[i].r;
        while (cur < pos) {
            if (lef[cur + 1]) update(1, 1, n, lef[cur + 1], mp(INF, 0));
            update(1, 1, n, cur + 1, mp(lef[cur + 1], a[cur + 1]));
            cur++;
        }

        pii ans = query(1, 1, n, Q[i].l, Q[i].r);
        if (ans._1 >= Q[i].l) ret[Q[i].id] = 0;
        else ret[Q[i].id] = ans._2;
    }

    for (int i = 0; i < q; i++) cout << ret[i] << '\n';
    return 0;
}
