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

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 112345;

LL sumk[N], sumk2[N];
LL a[N], k[N];
int n, q;

LL minm[N * 4], sum[N * 4], setv[N * 4];

void build(int o, int l, int r) {
    if (l == r) {
        minm[o] = sum[o] = setv[o] = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);

    minm[o] = min(minm[o * 2], minm[o * 2 + 1]);
    sum[o] = sum[o * 2] + sum[o * 2 + 1];
    setv[o] = -1;
}

LL query(int o, int l, int r, int ql, int qr) {
    if (setv[o] >= 0) {
        return setv[o] * (min(r, qr) - max(l, ql) + 1);
    } else if (ql <= l && r <= qr) {
        return sum[o];
    } else {
        int mid = l + (r - l) / 2;
        LL ans = 0;
        if (ql <= mid) ans += query(o * 2, l, mid, ql, qr);
        if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr);
        return ans;
    }
}

int find_idx(int o, int l, int r, LL val) {
    if (l == r) return l;
    int mid = l + (r - l) / 2;
    if (minm[o * 2 + 1] <= val) return find_idx(o * 2 + 1, mid + 1, r, val);
    else return find_idx(o * 2, l, mid, val);
}

void pushdown(int o) {
    if (setv[o] >= 0) {
        setv[o * 2] = setv[o * 2 + 1] = setv[o];
        setv[o] = -1;
    }
}

void maintain(int o, int l, int r) {
    if (setv[o] >= 0) {
        minm[o] = setv[o];
        sum[o] = setv[o] * (r - l + 1);
    } else {
        minm[o] = min(minm[o * 2], minm[o * 2 + 1]);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }
}

void update(int o, int l, int r, int ql, int qr, LL val) {
    if (ql <= l && r <= qr) {
        setv[o] = val;
        maintain(o, l, r);
    } else {
        pushdown(o);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update(o * 2, l, mid, ql, qr, val); else maintain(o * 2, l, mid);
        if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, val); else maintain(o * 2 + 1, mid + 1, r);
        maintain(o, l, r);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) cin >> k[i];
    k[0] = sumk[0] = sumk2[0] = a[1];

    for (int i = 1; i < n; i++) sumk[i] = sumk[i - 1] + k[i];
    for (int i = 1; i < n; i++) sumk2[i] = sumk2[i - 1] + sumk[i];
    for (int i = 1; i <= n; i++) a[i] -= sumk[i - 1];

    build(1, 1, n);
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == 's') {
            int l, r;
            cin >> l >> r;
            LL semi = sumk2[r - 1];
            if (l > 1) semi -= sumk2[l - 2];

            //cout << query(1, 1, n, l, r) << ' ' << semi << endl;
            cout << query(1, 1, n, l, r) + semi << '\n';
        } else {
            int id, x;
            cin >> id >> x;
            LL cur = query(1, 1, n, id, id);
            int idx = find_idx(1, 1, n, cur + x);
            //cout << cur << ' ' << idx << endl;
            update(1, 1, n, id, idx, cur + x);
        }
    }
    return 0;
}
