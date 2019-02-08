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

const int N = 312345;

int dp[N];
int n, a[N], sum[N], k;

bool check(int val) {
    reset(dp, 0);
    reset(sum, 0);
    dp[0] = sum[0] = 1;
    int l = 0;

    for (int i = 1; i <= n; i++) {
        while (a[i] - a[l + 1] > val) l++;
        int r = i - k;
        if (l > r) {
            dp[i] = 0;
            sum[i] = sum[i - 1];
            continue;
        } else {
            int cur = sum[r] - sum[l] + dp[l];
            if (cur > 0) dp[i] = 1;
            else dp[i] = 0;

            sum[i] = sum[i - 1] + dp[i];
        }
    }

    return dp[n] > 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[0] = a[1];
    sort(a + 1, a + n + 1);

    int l = 0, r = int(1e9) + 2;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l << '\n';
    return 0;
}
