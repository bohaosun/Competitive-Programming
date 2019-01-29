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
typedef pair <LL, LL> pll;
// Head

const LL INF = LL(1e18);
const int N = 112;

int n;
LL a[N], dp[N][N][N][2], ans[N][N];
string s;

// dp[l][r][cnt][0 or 1]: The max value to reduce the substring s[l...r] to cnt 0/1
// ans[l][r]: The max value of substring s[l][r]

LL get_ans(int, int);
LL get_dp(int, int, int, int);

LL get_ans(int l, int r) {
    if (l > r) return 0;
    LL &cur = ans[l][r];
    if (cur != -1) return cur;

    cur = 0;
    for (int cnt = 1; cnt <= r - l + 1; cnt++) {
        cur = max(max(get_dp(l, r, cnt, 0), get_dp(l, r, cnt, 1)) + a[cnt], cur);
        //cout << a[cnt] << endl;
    }
    return cur;
}

LL get_dp(int l, int r, int cnt, int digit) {
    if (cnt == 0) return get_ans(l, r);
    if (l > r) return -INF;

    LL &cur = dp[l][r][cnt][digit];
    if (cur != -1) return cur;

    cur = -INF;
    for (int i = l; i <= r; i++)
        if (s[i] - '0' == digit) {
            cur = max(cur, get_ans(l, i - 1) + get_dp(i + 1, r, cnt - 1, digit));
        }
    return cur;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++) cin >> a[i];
    reset(ans, -1);
    reset(dp, -1);
    cout << get_ans(0, n - 1) << '\n';
    //cout << get_dp(0, 0, 1, 1) << ' ' << get_dp(0, 0, 1, 0) << endl;
    return 0;
}
