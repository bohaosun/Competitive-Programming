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

const int N = 512345;

int dp[N];

vector<int> vec;

int solve(int u) {
    if (!u) return 0;
    int &ans = dp[u];
    if (ans > -1) return ans;

    ans = 12345678;
    for (int it : vec) {
        if (it > u) break;
        ans = min(ans, solve(u - it) + 1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; ; i++) {
        if (i * i > 500000) break;
        vec.pb(i * i);
    }

    reset(dp, -1);

    int n;
    cin >> n;
    cout << solve(n) << '\n';
    return 0;

}
