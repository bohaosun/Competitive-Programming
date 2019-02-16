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

#define Int int

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 412345;
const int X = 312;
const int TOT = 65;
const int MOD = int(1e9) + 7;

struct Node {
    LL val, mask;
} node[N * 4], mul[N * 4];

int prime[TOT], tot;
LL contain[X], inv[X];
int n, q, a[N];

void gen_prime() {
    for (int i = 2; i <= 300; i++) {
        bool ok = true;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) { ok = false; break; }
        }
        if (ok) {
            prime[tot++] = i;
        }
    }

    for (int i = 2; i <= 300; i++) {
        for (int j = 0; j < tot; j++) {
            if (i % prime[j] == 0) contain[i] |= (1ll << j);
        }
    }
}

LL qpow(LL x, int pw) {
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * x % MOD;
        pw >>= 1;
        x = x * x % MOD;
    }
    return ans;
}

void maintain(int o, int l, int r) {
    node[o].val = qpow(mul[o].val, r - l + 1);
    node[o].mask = mul[o].mask;

    if (l < r) {
        node[o].val = node[o].val * node[o * 2].val % MOD;
        node[o].val = node[o].val * node[o * 2 + 1].val % MOD;
        node[o].mask |= node[o * 2].mask;
        node[o].mask |= node[o * 2 + 1].mask;
    }
}

void build(int o, int l, int r) {
    if (l == r) {
        node[o].val = mul[o].val = a[l];
        node[o].mask = mul[o].mask = contain[a[l]];
        return;
    }

    int mid = l + (r - l) / 2;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);
    node[o].val = node[o * 2].val * node[o * 2 + 1].val % MOD;
    node[o].mask = node[o * 2].mask | node[o * 2 + 1].mask;
    mul[o].val = 1;
}

void query(int o, int l, int r, int ql, int qr, Node &ans) {
    if (ql <= l && r <= qr) {
        ans.val = ans.val * node[o].val % MOD;
        ans.mask |= node[o].mask;
        return;
    }

    ans.val = ans.val * qpow(mul[o].val, min(r, qr) - max(l, ql) + 1) % MOD;
    ans.mask |= mul[o].mask;
    int mid = l + (r - l) / 2;
    if (ql <= mid) query(o * 2, l, mid, ql, qr, ans);
    if (qr > mid) query(o * 2 + 1, mid + 1, r, ql, qr, ans);
}

void update(int o, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
        mul[o].val = mul[o].val * x % MOD;
        mul[o].mask |= contain[x];
        maintain(o, l, r);
        return;
    }

    int mid = l + (r - l) / 2;
    if (ql <= mid) update(o * 2, l, mid, ql, qr, x);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, x);
    maintain(o, l, r);
}

void De(int o, int l, int r) {
    cout << l << ' ' << r << ' ' << mul[o].val << endl;
    if (l < r) {
        int mid = l + (r - l) / 2;
        De(o * 2, l, mid);
        De(o * 2 + 1, mid + 1, r);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    gen_prime();
    for (int i = 0; i < tot; i++) inv[i] = qpow(prime[i], MOD - 2);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    while (q--) {
        string s;
        cin >> s;

        if (s[0] == 'T') {
            Node ans{ 1, 0 };
            int l, r;
            cin >> l >> r;
            query(1, 1, n, l, r, ans);
            //cout << ans.val << ' ' << ans.mask << endl;

            for (int i = 0; i < tot; i++) {
                if (ans.mask & (1ll << i)) {
                    ans.val = ans.val * (1 - inv[i] + MOD) % MOD;
                }
            }
            cout << ans.val << '\n';
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x);
        }
    }

    //De(1, 1, n);
    return 0;
}
