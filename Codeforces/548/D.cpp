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

const int N = 112345;
const int MOD = int(1e9) + 7;

LL add(LL a, LL b) { return (a + b) % MOD; }
LL mul(LL a, LL b) { return a * b % MOD; }
LL sub(LL a, LL b) { return (a - b + MOD) % MOD; }

int m;
LL dp[N];

LL qinv(LL u) {
    int pw = MOD - 2;
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * u % MOD;
        u = u * u % MOD;
        pw >>= 1;
    }
    return ans;
}

int vis[N];
vector<int> prime, factor[N];

void sieve() {
    for (int i = 2; i <= m; i++) if (!vis[i]) {
        prime.pb(i);
        factor[i].pb(i);
        for (int j = 2 * i; j <= m; j += i) {
            vis[j] = true;
            factor[j].pb(i);
        }
    }
}

LL cal(LL val, LL upb) {
    LL ans = 0;
    int sz = factor[val].size();
    int ALL = (1 << sz);

    for (int mask = 0; mask < ALL; mask++) {
        int cur = 1, cnt = 0;
        for (int j = 0; j < sz; j++) {
            if ((1 << j) & mask) { ++cnt; cur *= factor[val][j]; }
        }
        ans = (ans + ((cnt & 1) ? -1 : 1) * upb / cur + MOD) % MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m;
    LL base = qinv(m);

    sieve();

    dp[1] = 1;
    for (int i = 2; i <= m; i++) {
        LL rig = 1;
        LL lef = -1;
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                LL cur = cal(i / j, m / j);
                rig = add(rig, mul(mul(cur, base), dp[j]));

                if (i / j > j) {
                    cur = cal(j, m / (i / j));
                    if (j == 1) {
                        lef = sub(1, mul(cur, base));
                    } else {
                        rig = add(rig, mul(mul(cur, base), dp[i / j]));
                    }
                }
            }
        }
        //cout << lef << ' ' << rig << endl;
        assert(lef >= 1);
        dp[i] = mul(rig, qinv(lef));
    }

    //for (int i = 1; i <= m; i++) cout << dp[i] << endl;

    LL ans = 0;
    for (int i = 1; i <= m; i++) ans = add(ans, mul(dp[i], base));

    cout << ans << '\n';
    return 0;
}
