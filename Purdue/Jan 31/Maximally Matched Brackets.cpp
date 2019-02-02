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

const int N = 1123;

LL dp[N][N];
int n, k, a[N], b[N];
bool vis[N][N];

LL solve(int l, int r) {
    if (l >= r) return 0;
    if (dp[l][r] > -1) return dp[l][r];
    
    LL &ans = dp[l][r];
    ans = 0;
    for (int i = l + 1; i <= r; i++) ans = max(ans, solve(l, i - 1) + solve(i, r));
    if (a[l] + k == a[r]) ans = max(ans, solve(l + 1, r - 1) + b[l] + b[r]);

    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    
    reset(dp, -1);
    cout << solve(1, n) << '\n';
    return 0;
}
