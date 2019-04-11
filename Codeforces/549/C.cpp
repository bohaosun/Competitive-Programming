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

const int N = 112345;

vector<int> G[N];
int n, c[N], root;
vector<int> vec;

void dfs(int u) {
    bool ok = true;
    if (c[u] == 0) ok = false;
    for (int v : G[u]) {
        if (c[v] == 0) ok = false;
    }
    if (ok) vec.pb(u);

    for (int v : G[u]) dfs(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x != -1) G[x].pb(i);
        else root = i;

        cin >> c[i];
    }

    dfs(root);

    if (vec.empty()) cout << -1 << '\n';
    else {
        sort(all(vec));
        for (int it : vec) cout << it << ' ';
        cout << '\n';
    }
    return 0;
}
