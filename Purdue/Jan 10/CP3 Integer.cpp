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

const int N = 30;

LL dp[N][3][2];
vector<int> vec;

LL solve(int pos, int num, int sym) {
    if (pos == -1) return 1;
    if (num == 0) return 1;
    LL &ans = dp[pos][num][sym];
    if (ans > -1) return ans;
    ans = 0;

    if (!sym) {
        ans += solve(pos - 1, num, sym);
        ans += solve(pos - 1, num - 1, sym) * 9;
    } else {
        if (vec[pos] == 0) ans += solve(pos - 1, num, sym);
        else {
            ans += solve(pos - 1, num, 0);
            ans += solve(pos - 1, num - 1, 0) * (vec[pos] - 1);
            ans += solve(pos - 1, num - 1, 1);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    reset(dp, -1);
    int T;
    cin >> T;
    while (T--) {
        LL l, r;
        cin >> l >> r;
        l--;
        vector<int> ll, rr;
        while (l) {
            ll.pb(l % 10);
            l /= 10;
        }
        while (r) {
            rr.pb(r % 10);
            r /= 10;
        }

        reset(dp, -1);
        vec = rr;
        LL ans = solve(rr.size() - 1, 3, 1);
        reset(dp, -1);
        vec = ll;
        ans -= solve(ll.size() - 1, 3, 1);
        cout << ans << '\n';
    }
    return 0;
}
