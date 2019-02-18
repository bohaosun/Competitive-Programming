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

const int N = 1000000 + 5;

int a[N], n, m, dp[N][3][3];

// Sufficient to assume there are at most two times operation "a[i], a[i + 1], a[i + 2]"

int solve(int now, int t1, int t2) {
    if (now > m) return 0;
    int &ans = dp[now][t1][t2];
    if (ans > -1) return ans;

    ans = 0;
    int rem = min(a[now] - t1 - t2, min(a[now + 1] - t2, a[now + 2]));
    for (int i = 0; i <= min(rem, 2); i++) {
        int num = a[now] - t1 - t2 - i;
        ans = max(ans, solve(now + 1, t2, i) + i + num / 3);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }

    reset(dp, -1);
    cout << solve(1, 0, 0) << '\n';

    return 0;
}
