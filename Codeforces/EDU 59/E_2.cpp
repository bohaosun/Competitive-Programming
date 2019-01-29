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

const int N = 112;

int n;
string s;
LL a[N], dp[N][N][N];

// dp[l][r][prefix]: The max value of the substring s[l...r] with an extra string in which each digit is same as s[l]

LL solve(int l, int r, int prefix) {
    if (l > r) return 0;
    LL &ans = dp[l][r][prefix];
    if (ans > -1) return ans;

    ans = solve(l + 1, r, 1) + a[prefix];
    for (int i = l + 1; i <= r; i++) {
        if (s[l] == s[i]) {
            ans = max(ans, solve(l + 1, i - 1, 1) + solve(i, r, prefix + 1));
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++) cin >> a[i];

    reset(dp, -1);
    cout << solve(0, n - 1, 1) << '\n';
    return 0;
}
