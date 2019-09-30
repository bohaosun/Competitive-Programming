#include <bits/stdc++.h>

#define _1 first
#define _2 second
#define pb push_back
#define mp make_pair
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end())
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

const int MOD = int(1e9) + 7;
const int N = 260;

LL qpow(LL x, LL pw) {
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        pw >>= 1;
    }
    return ans;
}

LL dp[N][N], fac[N], rev[N], C[N][N], pnum[N], pnum1[N];
int n, num;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> num;

    fac[0] = 1;
    rev[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        rev[i] = qpow(fac[i], MOD - 2);
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            C[i][j] = fac[i] * rev[j] % MOD * rev[i - j] % MOD;
        }
    }

    pnum[0] = 1;
    for (int i = 1; i <= n; i++) pnum[i] = pnum[i - 1] * num % MOD;
    pnum1[0] = 1;
    for (int i = 1; i <= n; i++) pnum1[i] = pnum1[i - 1] * (num - 1) % MOD;

    for (int i = 1; i <= n; i++) {
        dp[1][i] = C[n][i] * pnum1[n - i] % MOD;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= j; k++) {
                LL cur;
                if (k < j) cur = dp[i - 1][k] * pnum[k] % MOD;
                else cur = dp[i - 1][k] * (pnum[k] - pnum1[k] + MOD) % MOD;

                //cout << cur << endl;
                cur = cur * C[n - k][j - k] % MOD;
                cur = cur * pnum1[n - j] % MOD;
                //cout << i << ' ' << j << ' ' << k << ' ' << cur << endl;
                dp[i][j] = (dp[i][j] + cur) % MOD;
            }
        }
    }

//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) cout << dp[i][j] << ' ';
//        cout << endl;
//    }

    cout << dp[n][n] << '\n';
    return 0;
}
