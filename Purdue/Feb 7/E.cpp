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

const int INF = int(1e9) + 7;
const int N = 512;

int a[N][N], n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }

    int ans = -INF;
    for (int i = 1; i <= n; i++) {
        int maxm1 = -INF, maxm2 = -INF;
        for (int j = 1; j <= n; j++) {
            if (a[i][j] > maxm1) { maxm2 = maxm1; maxm1 = a[i][j]; }
            else if (a[i][j] > maxm2) { maxm2 = a[i][j];}
        }
        ans = max(ans, maxm2);
    }

    cout << 1 << '\n' << ans << '\n';
    return 0;
}
