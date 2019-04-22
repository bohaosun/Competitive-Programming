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

const int dr[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
const int dc[] = { 0, -1, 0, 1, -1, 1, -1, 1 };
// Head

const int N = 312345;

vector<int> son[N];
int n, cur, sym[N], k;

int dfs(int u) {
    if (son[u].empty()) return 1;

    if (sym[u] == 0) {
        int tot = 0;
        for (int v : son[u]) tot += dfs(v);
        return tot;
    } else {
        int minm = k;
        for (int v : son[u]) minm = min(minm, dfs(v));
        return minm;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> sym[i];
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        son[x].pb(i);
    }

    k = 0;
    for (int i = 1; i <= n; i++) {
        if (son[i].empty()) ++k;
    }
    
    int val = dfs(1);

    cout << k - val + 1 << '\n';
    return 0;
}
