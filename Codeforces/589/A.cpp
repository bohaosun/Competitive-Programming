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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, r;
    cin >> l >> r;

    for (int i = l; i <= r; i++) {
        vector<int> vec(20);
        int x = i;
        while (x) {
            vec[x % 10]++;
            x /= 10;
        }

        bool ok = true;
        for (auto it : vec) {
            if (it > 1) { ok = false; break; }
        }
        if (ok) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
