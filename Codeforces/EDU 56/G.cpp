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

const int N = 212345;
const int M = 50;
const int INF = int(1e9);

int a[N][M], n, k, q, ALL, b[10];
int maxm[N * 4][M], minm[N * 4][M];
int qmaxm, qminm;

void build(int o, int l, int r, int mask) {
    if (l == r) {
        int cur = 0;
        for (int i = 0; i < k; i++) {
            if ((1 << i) & mask) cur += a[l][i];
            else cur -= a[l][i];
        }
        maxm[o][mask] = minm[o][mask] = cur;
        return;
    }
    int mid = (l + r) >> 1;
    build(o * 2, l, mid, mask);
    build(o * 2 + 1, mid + 1, r, mask);
    maxm[o][mask] = max(maxm[o * 2][mask], maxm[o * 2 + 1][mask]);
    minm[o][mask] = min(minm[o * 2][mask], minm[o * 2 + 1][mask]);
}

void query(int o, int l, int r, int ql, int qr, int mask) {
    if (ql <= l && r <= qr) {
        qmaxm = max(qmaxm, maxm[o][mask]);
        qminm = min(qminm, minm[o][mask]);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) query(o * 2, l, mid, ql, qr, mask);
    if (qr > mid) query(o * 2 + 1, mid + 1, r, ql, qr, mask);
}

void update(int o, int l, int r, int pos, int mask) {
    if (l == r) {
        int cur = 0;
        for (int i = 0; i < k; i++) {
            if ((1 << i) & mask) cur += b[i];
            else cur -= b[i];
        }
        maxm[o][mask] = minm[o][mask] = cur;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(o * 2, l, mid, pos, mask);
    if (pos > mid) update(o * 2 + 1, mid + 1, r, pos, mask);
    maxm[o][mask] = max(maxm[o * 2][mask], maxm[o * 2 + 1][mask]);
    minm[o][mask] = min(minm[o * 2][mask], minm[o * 2 + 1][mask]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    ALL = (1 << k);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < k; j++) cin >> a[i][j];

    for (int i = 0; i < ALL; i++) build(1, 1, n, i);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int sym;
        cin >> sym;
        if (sym == 1) {
            int pos;
            cin >> pos;
            for (int j = 0; j < k; j++) cin >> b[j];
            for (int j = 0; j < ALL; j++) update(1, 1, n, pos, j);
        } else {
            int l, r;
            cin >> l >> r;
            int ans = -INF;
            for (int j = 0; j < ALL; j++) {
                qmaxm = -INF;
                qminm = INF;
                query(1, 1, n, l, r, j);
                ans = max(ans, qmaxm - qminm);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
