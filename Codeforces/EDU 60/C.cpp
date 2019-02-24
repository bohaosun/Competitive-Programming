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

const int N = 112345;
const LL INF = LL(1e18);

string s;
int n;

LL sumx[N], sumy[N];
LL dx, dy;

bool check(LL t) {
    LL p = t / n, p2 = t % n;
    LL need = abs(dx - p * sumx[n] - sumx[p2]);
    need += abs(dy - p * sumy[n] - sumy[p2]);

    return need <= t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    LL x1, y1, x2, y2;

    cin >> x1 >> y1 >> x2 >> y2;
    cin >> n;

    cin >> s;
    s = '0' + s;

    dx = x2 - x1;
    dy = y2 - y1;
    for (int i = 1; i <= n; i++) {
        sumx[i] = sumx[i - 1];
        sumy[i] = sumy[i - 1];
        if (s[i] == 'U') sumy[i]++;
        else if (s[i] == 'D') sumy[i]--;
        else if (s[i] == 'L') sumx[i]--;
        else sumx[i]++;
    }

    LL l = 1, r = INF;
    while (l < r) {
        LL mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    if (l == INF) cout << -1 << '\n';
    else cout << l << '\n';
    return 0;
}
