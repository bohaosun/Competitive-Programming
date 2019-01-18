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

LL c[N], a[N];
int n, m;

int lowbit(int x) { return x & (-x); }

LL sum(int x) {
    LL ans = 0;
    while (x) {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

void add(int pos, LL val) {
    while (pos <= n) {
        c[pos] += val;
        pos += lowbit(pos);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i, a[i]);
    }

    for (int i = 0; i < m; i++) {
        int id, x, y;
        cin >> id >> x >> y;
        if (id == 1) cout << sum(y) - sum(x - 1) << '\n';
        else {
            add(x, y - a[x]);
            a[x] = y;
        }
    }
    return 0;
}
