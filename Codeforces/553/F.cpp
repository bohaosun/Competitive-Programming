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

const int N = 112;
const int MOD = 1000000007;

int n, k, arr[N], dim;
LL den;

LL inv(LL num) {
    int pw = MOD - 2;
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * num % MOD;
        pw >>= 1;
        num = num * num % MOD;
    }
    return ans;
}

void mul(LL ans[][N], LL a[][N], LL b[][N]) {
    for (int i = 0; i <= dim; i++) {
        for (int j = 0; j <= dim; j++) {
            ans[i][j] = 0;
            for (int k = 0; k <= dim; k++) {
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
}

void copy(LL a[][N], LL b[][N]) {
    for (int i = 0; i <= dim; i++) {
        for (int j = 0; j <= dim; j++) a[i][j] = b[i][j];
    }
}

void m_pow(LL mat[][N], int pw, LL ans[][N]) {
    for (int i = 0; i <= dim; i++) {
        for (int j = 0; j <= dim; j++) {
            if (i == j) ans[i][j] = 1;
            else ans[i][j] = 0;
        }
    }

    //cout << ans[0][0] << endl;
    //cout << mat[0][0] << endl;

    LL tmp[N][N];
    while (pw) {
        if (pw & 1) {
            copy(tmp, ans);
            //cout << ans[0][0] << endl;
            mul(ans, tmp, mat);
            //cout << mat[0][0] << endl;
        }
        pw >>= 1;
        copy(tmp, mat);
        mul(mat, tmp, tmp);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    int a = 0, b = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i] == 0) ++a;
        else ++b;
    }

    dim = min(a, b);
    LL mat[N][N];
    reset(mat, 0);
    den = inv(n * (n - 1) / 2);

    for (int i = 0; i <= dim; i++) {
        mat[i][i] = a * (a - 1) / 2 + b * (b - 1) / 2 + i * (b - i) + (a - i) * i;
        mat[i][i] = mat[i][i] * den % MOD;

        if (i) mat[i][i - 1] = i * i * den % MOD;
        if (i < dim) mat[i][i + 1] = (a - i) * (b - i) * den % MOD;
    }

//    for (int i = 0; i <= dim; i++) {
//        for (int j = 0; j <= dim; j++) cout << mat[i][j] << ' ';
//        cout << endl;
//    }

    LL ans[N][N];
    m_pow(mat, k, ans);

    int mass = 0;
    for (int i = 1; i <= a; i++) {
        if (arr[i] != 0) ++mass;
    }

    cout << ans[mass][0] << '\n';
    return 0;
}
