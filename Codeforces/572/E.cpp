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

/**
 * (ai + aj) * (ai^2 + aj^2) == k MOD p
 * <-->
 * ai^4 - k * ai MOD p == aj^4 - k * aj MOD p
 */

int n, k, p;
map<LL, LL> pic;

LL process(LL x) {
    LL cur = 1;
    for (int i = 0; i < 4; i++) cur = cur * x % p;
    cur -= x * k % p;
    cur = (cur + p) % p;
    return cur;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p >> k;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ++pic[process(x)];
    }

    LL ans = 0;
    for (auto it : pic) {
        ans += it.second * (it.second - 1) / 2;
    }

    cout << ans << '\n';
    return 0;
}
