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

const int dr[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
const int dc[] = { 0, -1, 0, 1, -1, 1, -1, 1 };
// Head

const int N = 25;

int n, m, ALL;
bool app[1 << N], vis[1 << N];

void dfs(int mask) {
    vis[mask] = true;
    if (app[mask] && !vis[ALL ^ mask]) dfs(ALL ^ mask);
    for (int i = 0; i < n; i++) {
        if ((1 << i) & mask && !vis[mask ^ (1 << i)]) dfs(mask ^ (1 << i));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        app[x] = true;
    }

    ALL = (1 << n) - 1;

    int ans = 0;
    for (int i = 0; i <= ALL; i++) {
        if (app[i] && !vis[i]) {
            ++ans;
            dfs(ALL ^ i);
        }
    }
    cout << ans << '\n';
    return 0;
}
