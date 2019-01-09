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

const int N = 250 + 10;
const int INF = int(1e9);

int d[N][N], n, sum[N], a[N];

int val(int l, int r) {
    if (l > r) return 0;
    return sum[r] - sum[l - 1];
}

int dp(int l, int r) {
    if (l >= r) return 0;
    int &ans = d[l][r];
    if (ans > -1) return ans;

    ans = INF;
    for (int i = l; i <= r; i++) ans = min(ans, dp(l, i - 1) + dp(i + 1, r) + val(l, i - 1) + val(i + 1, r));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];

        reset(d, -1);
        cout << dp(1, n) << '\n';
    }
    return 0;
}
