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

const int N = 1123;
const int MOD = int(1e9) + 7;

int a[N][N], r[N], c[N];
int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= m; i++) cin >> c[i];

    reset(a, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= r[i]; j++) {
            if (a[i][j] == 0) {
                cout << 0 << '\n';
                return 0;
            }
            a[i][j] = 1;
        }
        if (a[i][r[i] + 1] == 1) {
            cout << 0 << '\n';
            return 0;
        }
        a[i][r[i] + 1] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= c[i]; j++) {
            if (a[j][i] == 0) {
                cout << 0 << '\n';
                return 0;
            }
            a[j][i] = 1;
        }
        if (a[c[i] + 1][i] == 1) {
            cout << 0 << '\n';
            return 0;
        }
        a[c[i] + 1][i] = 0;
    }

    LL ans = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == -1) ans = ans * 2 % MOD;
        }
    }

    cout << ans << '\n';
    return 0;
}
