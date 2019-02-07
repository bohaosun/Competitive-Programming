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

const int N = 1123455;

LL n, k, m;
LL a[N];

int main() {
    //freopen("/Users/bohaosun/Desktop/input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    double ans = 0;
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);

    LL sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i];
    LL cur = 0;

    for (int i = 0; i <= min(m, n - 1); i++) {
        cur += a[i];
        ans = max(ans, double((sum - cur) + min(m - i, (n - i) * k)) / (n - i));
    }
    cout << fixed;
    cout.precision(10);
    cout << ans << '\n';
    return 0;
}
