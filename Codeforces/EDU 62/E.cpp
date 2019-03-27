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

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 212345;
const int MOD = 998244353;

LL dp[N][5];
int n, k, a[N];

vector<int> vec;

void solve(LL &ans) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] != -1) continue;
        int r = i;
        while (r < vec.size() && vec[r] == -1) ++r;

        int num = r - i;
        if (i == 0 && r == vec.size()) ans = ans * dp[num][0] % MOD;
        else if (i == 0 || r == vec.size()) ans = ans * dp[num][1] % MOD;
        else if (vec[i - 1] == vec[r]) ans = ans * dp[num][3] % MOD;
        else ans = ans * dp[num][2] % MOD;

        i = r - 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 2; i < n; i++) {
        if (a[i - 1] != -1 && a[i + 1] != -1 && a[i - 1] == a[i + 1]) {
            cout << 0 << '\n';
            return 0;
        }
    }

    dp[0][0] = dp[0][1] = dp[0][2] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][1] * k % MOD;
        dp[i][1] = dp[i - 1][1] * (k - 1) % MOD;
        dp[i][2] = (dp[i - 1][3] + dp[i - 1][2] * (k - 2)) % MOD;
        dp[i][3] = dp[i - 1][2] * (k - 1) % MOD;
    }

    LL ans = 1;
    for (int i = 1; i <= n; i += 2) vec.pb(a[i]);
    solve(ans);

    vec.clear();
    for (int i = 2; i <= n; i += 2) vec.pb(a[i]);
    solve(ans);

    cout << ans << '\n';
    return 0;
}
