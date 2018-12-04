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
#define left lef

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

struct Node {
    pii val;
    int l, r;
};

const int N = 512345;
const int INF = int(1e9);

Node node[N * 50];
int root[N], a[N], n, left[N], last[N], size;

int build(int l, int r) {
    int cur = size++;
    node[cur].l = l; node[cur].r = r;
    node[cur].val = mp(INF, 0);
    return cur;
}

int update(int o, int l, int r, int pos, pii val) {
    int cur = size++;
    node[cur] = node[o];
    if (l == r) {
        node[cur].val = val;
        return cur;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid) node[cur].l = update(node[o].l, l, mid, pos, val);
    else node[cur].r = update(node[o].r, mid + 1, r, pos, val);
    node[cur].val = min(node[node[cur].l].val, node[node[cur].r].val);
    return cur;
}

pii query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return node[o].val;
    pii ans(INF, 0);
    int mid = l + (r - l) / 2;
    if (ql <= mid) ans = min(ans, query(node[o].l, l, mid, ql, qr));
    if (qr > mid) ans = min(ans, query(node[o].r, mid + 1, r, ql, qr));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        left[i] = last[a[i]];
        last[a[i]] = i;
    }

    root[0] = build(1, n);

    for (int i = 1; i <= n; i++) {
        if (left[i]) {
            root[i] = update(root[i - 1], 1, n, left[i], mp(INF, 0));
            root[i] = update(root[i], 1, n, i, mp(left[i], a[i]));
        } else {
            root[i] = update(root[i - 1], 1, n, i, mp(left[i], a[i]));
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        pii ans = query(root[r], 1, n, l, r);
        if (ans._1 >= l) cout << 0 << '\n';
        else cout << ans._2 << '\n';
    }
    return 0;
}
