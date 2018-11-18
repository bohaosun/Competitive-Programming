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
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 500 + 10;
pii p[N];
int fa[N];
int m, n;

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

double dist(int x, int y) {
    return sqrt((p[x]._1 - p[y]._1) * (p[x]._1 - p[y]._1) + (p[x]._2 - p[y]._2) * (p[x]._2 - p[y]._2));
}

bool check(double val) {
    for (int i = 0; i < n; i++) fa[i] = i;
    int tot = n;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int x = find(i), y = find(j);
            if (x == y) continue;
            if (dist(i, j) > val) continue;
            tot--;
            fa[x] = y;
        }
    return tot <= m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int i = 0; i < n; i++) cin >> p[i]._1 >> p[i]._2;
        double l = 0, r = 20000;
        for (int i = 0; i < 100; i++) {
            double mid = l + (r - l) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }

        cout << fixed;
        cout.precision(2);
        cout << l << '\n';
    }
    return 0;
}
