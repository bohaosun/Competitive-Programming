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

const int K = 112;
const int MOD = 998244353;

int num;
int b[K], n, m;

void mul(LL C[][K], LL A[][K], LL B[][K]) {
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= num; j++) {
            C[i][j] = 0;
            for (int k = 1; k <= num; k++) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % (MOD - 1);
        }
    }
}

void copy(LL A[][K], LL B[][K]) {
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= num; j++) A[i][j] = B[i][j];
    }
}

void pw(LL A[][K], int pwv) {
    LL ans[K][K];
    reset(ans, 0);
    for (int i = 1; i <= num; i++) ans[i][i] = 1;
    //cout << 1 << endl;

    while (pwv) {
        LL B[K][K];
        if (pwv & 1) {
            copy(B, ans);
            mul(ans, B, A);
        }
        copy(B, A);
        mul(A, B, B);
        pwv >>= 1;
    }
    copy(A, ans);
}


void gcd(LL a, LL b, LL& d, LL& x, LL& y) {
    if(!b) { d = a; x = 1; y = 0; }
    else { gcd(b, a % b, d, y, x); y -= x * (a / b); }
}

LL inv(LL a, LL n) {
    LL d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}

// find x such that a ^ x == b (mod n). n is a prime number. When there's no solution, -1 is returned.
// O(sqrt(n) * log(n))
LL log_mod(LL a, LL b, LL n) {
    LL m, v, e = 1;
    m = LL(sqrt(n + 0.5)) + 1;
    map<LL, int> x;
    x[1] = 0;
    for(int i = 1; i < m; i++) {
        e = e * a % n;
        if(!x.count(e)) x[e] = i;
    }
    v = inv(e * a % n, n);
    for(int i = 0; i < m; i++) {  // Consider a^(im), a^(im + 1), ....., a^(im + m - 1)
        if(x.count(b)) return m * i + x[b];
        b = b * v % n;
    }
    return -1;
}

LL qpow(LL a, LL pw) {
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        pw >>= 1;
    }
    return ans;
}

/**
 * Key points:
 * 1. Use quick power and matrix multiplication to find the final value
 * 2. Find a primitive root (Here is 3)
 * 3. Apply Ex-Euclidean Algorithm to solve the equation obtained in 2
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num;
    for (int i = 1; i <= num; i++) cin >> b[i];
    cin >> n >> m;

    LL A[K][K];
    reset(A, 0);
    for (int i = 1; i <= num; i++) A[1][i] = b[i];
    for (int i = 2; i <= num; i++) A[i][i - 1] = 1;

    pw(A, n - num);


    LL a = A[1][1];
    LL rig = log_mod(3, m, MOD);          // 3 is a primitive root
    LL b = MOD - 1;
    LL x, y, d;
    gcd(a, b, d, x, y);

    //cout << rig << endl;
    //cout << a << ' ' << x << ' ' << b << ' ' << y << ' ' << d << endl;

    if (rig % d) cout << -1 << '\n';
    else {
        x = (x + MOD - 1) % (MOD - 1);
        cout << qpow(3, x * (rig / d) % (MOD - 1)) << '\n';
    }
    return 0;
}
