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

const int N = 5123;
const int K = 1123;
const LL INF = LL(1e15);

LL d[N][K];
int n, k, a[N];

LL dp(int i, int j) {
    if (j == 0) return 0;
    if (i <= 1) return INF;
    if (d[i][j] > -1) return d[i][j];

    int rem = n - i - 3 * (k - j);
    LL &ans = d[i][j] = dp(i - 1, j);
    if (rem > 0) ans = min(ans, dp(i - 2, j - 1) + sqr(a[i] - a[i - 1]));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        reset(d, -1);
        cin >> k >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        k += 8;
        cout << dp(n, k) << '\n';
    }
    return 0;
}
