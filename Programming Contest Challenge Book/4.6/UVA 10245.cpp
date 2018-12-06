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

const int N = 11234;
const double INF = 1e9;

double dist(pii a, pii b) {
    return sqrt((a._1 - b._1) * (a._1 - b._1) + (a._2 - b._2) * (a._2 - b._2));
}

bool cmp(const pii a, const pii b) { return a._2 < b._2; }

double solve(pii* a, int sz) {
    if (sz <= 1) return INF;
    int m = sz / 2;
    double x = a[m]._1;

    double d = min(solve(a, m), solve(a + m, sz - m));
    inplace_merge(a, a + m, a + sz, cmp);

    vector<pii> b;
    for (int i = 0; i < sz; i++) {
        if (fabs(a[i]._1 - x) >= d) continue;
        for (int j = (int)b.size() - 1; j >= 0; j--) {
            if (a[i]._2 - b[j]._2 >= d) break;
            d = min(d, dist(a[i], b[j]));
        }
        b.pb(a[i]);
    }
    return d;
}

int n;
pii a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> a[i]._1 >> a[i]._2;
        sort(a, a + n);
        double ans = solve(a, n);

        cout << fixed;
        cout.precision(4);
        if (ans > 10000) cout << "INFINITY\n";
        else cout << ans << '\n';
    }
    return 0;
}
