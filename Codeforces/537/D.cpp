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

const int N = 112345;
const int MOD = int(1e9) + 7;

string s;
LL fac[N], dp[N], tmp[N], ans[100][100];
int q, n, half, cnt[100];

int idx(char c) { return islower(c) ? c - 'a' : c - 'A' + 26; }

LL inv(LL x) {
    int pw = MOD - 2;
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        pw >>= 1;
    }
    return ans;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= 100000; i++) fac[i] = fac[i - 1] * i % MOD;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = s.length();
    half = n / 2;

    for (int i = 0; i < n; i++) cnt[idx(s[i])]++;

    LL factor = fac[half] * fac[half] % MOD;
    for (int i = 0; i < 52; i++) {
        if (cnt[i] == 0) continue;
        factor = factor * inv(fac[cnt[i]]) % MOD;
    }

    dp[0] = 1;
    for (int i = 0; i < 52; i++) {
        if (cnt[i] == 0) continue;
        for (int j = half; j >= cnt[i]; j--) {
            dp[j] = (dp[j] + dp[j - cnt[i]]) % MOD;
        }
    }

    //cout << dp[half] << endl;
    for (int i = 0; i < 52; i++) {
        if (cnt[i] == 0) continue;

        ans[i][i] = factor * dp[half] % MOD;
        for (int j = i + 1; j < 52; j++) {
            if (cnt[j] == 0) continue;
            for (int k = 0; k <= half; k++) tmp[k] = dp[k];

            // Drop things from the knapsack...
            for (int k = cnt[i]; k <= half; k++) tmp[k] = (tmp[k] - tmp[k - cnt[i]] + MOD) % MOD;
            for (int k = cnt[j]; k <= half; k++) tmp[k] = (tmp[k] - tmp[k - cnt[j]] + MOD) % MOD;

            ans[i][j] = ans[j][i] = 2 * tmp[half] * factor % MOD;
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        cout << ans[idx(s[x - 1])][idx(s[y - 1])] << '\n';
    }
    return 0;
}
