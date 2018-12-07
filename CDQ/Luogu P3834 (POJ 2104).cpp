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
int n, m, a[N], c[N], ans[N];

vector<pii> vec;

struct Query {
    int l, r, k;
};
vector<Query> query;
vector<int> q;

int lowbit(int x) { return x & (-x); }
int sum(int pos) {
    int ans = 0;
    while (pos) {
        ans += c[pos];
        pos -= lowbit(pos);
    }
    return ans;
}

void add(int pos, int d) {
    while (pos <= n) {
        c[pos] += d;
        pos += lowbit(pos);
    }
}

void solve(int l, int r, vector<int>& q) {
    if (q.empty() || vec[l]._1 == vec[r]._1) {
        for (int it : q) ans[it] = vec[l]._1;
        return;
    }

    int mid = (l + r) >> 1;
    reset(c, 0);

    for (int i = l; i <= mid; i++) add(vec[i]._2, 1);
    vector<int> ql, qr;
    for (int it : q) {
        int cur = sum(query[it].r) - sum(query[it].l - 1);
        if (cur >= query[it].k) ql.pb(it);
        else {
            query[it].k -= cur;
            qr.pb(it);
        }
    }
    solve(l, mid, ql);
    solve(mid + 1, r, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vec.pb({ a[i], i });
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        query.pb({ l, r, k });
        q.pb(i - 1);
    }

    sort(all(vec));
    solve(0, n - 1, q);

    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
    return 0;
}
