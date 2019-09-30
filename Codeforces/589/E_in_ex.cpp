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
typedef pair <LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 250 + 10;
const int MOD = int(1e9) + 7;

LL pnum[N * N], pnum1[N * N], C[N][N];

int n, num;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> num;
    pnum[0] = pnum1[0] = 1;
    for (int i = 1; i <= sqr(n); ++i) {
        pnum[i] = pnum[i - 1] * num % MOD;
        pnum1[i] = pnum1[i - 1] * (num - 1) % MOD;
    }

    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    LL ans = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            int op = (i + j) % 2 == 1 ? -1 : 1;
            LL cur = C[n][i] * C[n][j] % MOD;
            cur = cur * pnum[(n - i) * (n - j)] % MOD;
            cur = cur * pnum1[sqr(n) - (n - i) * (n - j)] % MOD;
            ans = (ans + cur * op + MOD) % MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}
