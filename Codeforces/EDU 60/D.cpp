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

const int M = 112;
const int MOD = 1000000007;

// dp[i]: the way to fill in i spaces
// dp[i] = dp[i - 1] + dp[i - m]

LL n;
int m;

LL A[M][M];

LL ans[M][M], B[M][M];

void copy(LL A[][M], LL B[][M]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) A[i][j] = B[i][j];
    }
}

void mul(LL A[][M], LL B[][M], LL C[][M]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = 0;
            for (int k = 0; k < m; k++) {
                A[i][j] = (A[i][j] + B[i][k] * C[k][j]) % MOD;
            }
        }
    }
}

void qpow(LL A[][M], LL pw) {
    for (int i = 0; i < m; i++) ans[i][i] = 1;
    while (pw) {
        if (pw & 1) {
            copy(B, ans);
            mul(ans, A, B);
        }
        pw >>= 1;
        copy(B, A);
        mul(A, B, B);
    }

    copy(A, ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    if (n < m) { cout << 1 << '\n'; return 0; }

    for (int i = 0; i < m - 1; i++) A[i][i + 1] = 1;
    A[m - 1][0] = A[m - 1][m - 1] = 1;

    qpow(A, n - m + 1);
    vector<int> v(m, 1);

    LL ans = 0;
    for (int i = 0; i < m; i++) ans = (ans + A[m - 1][i] * v[i]) % MOD;

    cout << ans << '\n';
    return 0;
}
