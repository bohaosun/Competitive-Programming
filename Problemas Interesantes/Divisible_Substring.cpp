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

string s;
int a[N], cnt[N], n, p;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;
    cin >> s;

    LL ans = 0;
    if (p == 2) {
        for (int i = 0; i < n; ++i) {
            if (int(s[i] - '0') % 2 == 0) ans += i + 1;
        }
    } else if (p == 5) {
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0' || s[i] == '5') ans += i + 1;
        }
    } else {
        int base = 1;
        for (int i = n - 1; i >= 0; --i) {
            a[i] = (s[i] - '0') * base % p;
            a[i] = (a[i] + a[i + 1]) % p;
            base = base * 10 % p;
        }

        for (int i = 0; i <= n; ++i) {
            ans += cnt[a[i]];
            ++cnt[a[i]];
        }
    }

    cout << ans << '\n';
    return 0;
}
