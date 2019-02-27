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

const int N = 151234;

int fa[N], n, sz[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

vector<int> vec[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) { fa[i] = i; vec[i].pb(i); sz[i] = 1; }

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;

        int l = find(x), r = find(y);
        if (sz[l] < sz[r]) swap(l, r);

        fa[r] = l;
        for (int it : vec[r]) vec[l].pb(it);
        sz[l] += sz[r];
    }

    int cur = find(1);
    for (int it : vec[cur]) cout << it << ' ';
    cout << '\n';
    return 0;
}
