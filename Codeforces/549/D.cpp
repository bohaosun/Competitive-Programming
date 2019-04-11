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

LL n, k, a, b;
LL minm, maxm;

LL gcd(LL a, LL b) { return !b ? a : gcd(b, a % b); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    minm = LL(1e18), maxm = 0;

    cin >> n >> k >> a >> b;

    // behind behind:
    LL dis = b - a;
    if (dis <= 0) dis += k;

    for (int i = 0; i <= n - 1; i++) {
        LL l = dis + k * i;
        LL cur = (n * k) / gcd(l, n * k);

        maxm = max(maxm, cur);
        minm = min(minm, cur);
    }

    // behind front:
    dis = k - b - a;
    if (dis <= 0) dis += k;
    for (int i = 1; i <= n - 1; i++) {
        LL l = dis + k * i;
        LL cur = (n * k) / gcd(l, n * k);

        maxm = max(maxm, cur);
        minm = min(minm, cur);
    }

    // front behind:
    dis = a + b;
    for (int i = 1; i <= n - 1; i++) {
        LL l = dis + k * i;
        LL cur = (n * k) / gcd(l, n * k);

        maxm = max(maxm, cur);
        minm = min(minm, cur);
    }

    // front front:
    dis = a - b;
    if (dis <= 0) dis += k;
    for (int i = 1; i <= n - 1; i++) {
        LL l = dis + k * i;
        LL cur = (n * k) / gcd(l, n * k);

        maxm = max(maxm, cur);
        minm = min(minm, cur);
    }

    cout << minm << ' ' << maxm << '\n';
    return 0;
}
