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

const int N = 1123456;

LL add[N * 4], sum[N * 4];
int n;

LL query(int o, int l, int r, int ql, int qr, LL addv) {
    if (ql <= l && r <= qr) return sum[o] + addv * (r - l + 1);
    int mid = l + (r - l) / 2;
    LL ans = 0;
    if (ql <= mid) ans += query(o * 2, l, mid, ql, qr, addv + add[o]);
    if (qr > mid) ans += query(o * 2 + 1, mid + 1, r, ql, qr, addv + add[o]);
    return ans;
}

void maintain(int o, int l, int r) {
    sum[o] = 0;
    if (l < r) sum[o] += sum[o * 2] + sum[o * 2 + 1];
    sum[o] += add[o] * (r - l + 1);
}

void update(int o, int l, int r, int ql, int qr, LL val) {
    if (ql <= l && r <= qr) {
        add[o] += val;
        maintain(o, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    if (ql <= mid) update(o * 2, l, mid, ql, qr, val);
    if (qr > mid) update(o * 2 + 1, mid + 1, r, ql, qr, val);
    maintain(o, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (;;) {
        string s;
        cin >> s;
        if (s[0] == 'I') break;
        if (s[0] == 'A') {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, min(l, r), max(l, r), 0) << '\n';
        } else {
            int l, r;
            LL x;
            cin >> l >> r >> x;
            update(1, 1, n, min(l, r), max(l, r), x);
        }
    }
    return 0;
}
