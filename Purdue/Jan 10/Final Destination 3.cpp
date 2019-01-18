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

const int N = 212345;

int n, k, p;
pii a[N];

int fa[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]._1;
        a[i]._2 = i;
    }
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 2; i <= n; i++) {
        if (a[i]._1 - a[i - 1]._1 <= k) {
            int x = find(a[i - 1]._2), y = find(a[i]._2);
            fa[x] = y;
        }
    }

    for (int i = 0; i < p; i++) {
        int x, y;
        cin >> x >> y;
        if (find(x) == find(y)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
