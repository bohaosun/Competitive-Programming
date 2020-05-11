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

const int N = 212345;
const int MOD = 998244353;

LL pw[N], fac[N];
int n, m, k;

LL inv(LL x) {
    LL ans = 1;
    int val = MOD - 2;
    while (val) {
        if (val & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        val >>= 1;
    }
    return ans;
}

LL C(int a, int b) {
    LL ans = fac[a];
    ans = ans * inv(fac[a - b]) % MOD;
    ans = ans * inv(fac[b]) % MOD;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    pw[0] = fac[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * (m - 1) % MOD;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;

    LL ans = 0;
    for (int i = n - k; i <= n; ++i) {
        LL cur = C(n - 1, i - 1);
        cur = cur * m % MOD;
        cur = cur * pw[i - 1] % MOD;
        ans = (ans + cur) % MOD;
    }

    cout << ans << '\n';
    return 0;
}
