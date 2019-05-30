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
#include <complex>

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

const int N = 312345;

int a[N], n, q;

int now[20], dp[N][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 0; i < 20; i++) {
        now[i] = n + 1;
        dp[n + 1][i] = n + 1;
    }

    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 20; j++) {
            if (a[i] & (1 << j)) { dp[i][j] = i; continue; }
            dp[i][j] = n + 1;
            for (int k = 0; k < 20; k++) {
                if (a[i] & (1 << k)) {
                    dp[i][j] = min(dp[i][j], dp[now[k]][j]);
                }
            }
        }

        for (int j = 0; j < 20; j++) {
            if (a[i] & (1 << j)) now[j] = i;
        }
    }

//    for (int i = 1; i <= n; i++) {
//        for (int j = 0; j < 3; j++) cout << dp[i][j] << ' ';
//        cout << endl;
//    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        bool ok = false;
        for (int i = 0; i < 20; i++) {
            if ((a[r] & (1 << i)) && dp[l][i] <= r) {
                ok = true;
                break;
            }
        }

        if (ok) cout << "Shi\n";
        else cout << "Fou\n";
    }
    return 0;
}
