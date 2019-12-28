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

int n, a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> n;
        if (n & 1) {
            a[1] = 0;
            ++n;
            for (int i = 2; i <= n; ++i) cin >> a[i];
        } else {
            for (int i = 1; i <= n; ++i) cin >> a[i];
        }

        sort(a + 1, a + n + 1);

        int val = 0;
        for (int i = 2; i <= n; i += 2) val ^= a[i] - a[i - 1] - 1;

        if (val) cout << "Georgia will win" << endl;
        else cout << "Bob will win" << endl;
    }

    return 0;
}
