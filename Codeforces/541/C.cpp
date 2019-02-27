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

const int N = 112;

int n, a[N];
bool vis[N];

/**
 * Suppose a[i + 2] - a[i] is the max gap between any two consecutive elements after sorting. Then a[i] needs to approach
 * to a[i + 2] in two directions. So the maximum gap is larger than or equal to a[i + 2] - a[i].
 *
 * a[1] a[3] .... a[n] a[n - 1] a[n - 3]... (n is odd) or a[1] a[3] ... a[n - 1] a[n] a[n - 2] a[n - 4] (n is even),
 * the gap is max(a[i + 2] - a[i]). So it's an answer
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i += 2) {
        cout << a[i] << ' ';
        vis[i] = true;
    }

    for (int i = n; i >= 1; i--) {
        if (!vis[i]) cout << a[i] << ' ';
    }
    cout << '\n';
    return 0;
}
