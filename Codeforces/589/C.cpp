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

vector<int> prime;
int x;
LL n;

LL qpow(LL x, LL pw) {
    LL ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        pw >>= 1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> n;

    int t = sqrt(x + 0.5);
    for (int i = 2; i <= t; i++) {
        if (x % i == 0) {
            prime.pb(i);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) prime.pb(x);

    LL ans = 1;
    for (int p : prime) {
        //cout << p << endl;
        LL cur = p;
        for (;;) {
            LL num = n / cur;
            ans = ans * qpow(p, num) % MOD;
            if (n / cur < p) break;
            cur *= p;
        }
    }

    cout << ans << '\n';
    return 0;
}
