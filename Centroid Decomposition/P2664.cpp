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

/*
 * Centroid decomposition: key point is to find a way to process the pairs with the LCA at the root in O(n).
 * Then the overall complecity is O(nlogn).
 * Key Observation: If a color first appears on u, then the influence on each node of other subtrees would be sz[u].
 * Procedure (after find the root):
 * 1. process the sz
 * 2. calculate color[] and sum (the influence)
 * 3. For each subtree, update the answer (between the pairs with LCA at the root): First cancel the influence of
 * its own then update the answer then get the influence back
 * 4. update the ans for the root
 * 5. reset all the influence and process the next layer
 */

const int N = 112345;
const int INF = int(1e9);

int n, col[N], vis[N], sz[N];
bool centroid[N];
LL ans[N];
vector<int> G[N];

LL color[N], sum;

int get_size(int u, int fa) {
    sz[u] = 1;
    for (int v : G[u])
        if (v != fa && !centroid[v]) sz[u] += get_size(v, u);
    return sz[u];
}

pii get_root(int u, int fa, int tot_sz) {
    int tot = 1, max_sz = 0;
    pii ans(INF, 0);

    for (int v : G[u])
        if (v != fa && !centroid[v]) {
            max_sz = max(max_sz, sz[v]);
            tot += sz[v];
            ans = min(ans, get_root(v, u, tot_sz));
        }
    max_sz = max(max_sz, tot_sz - tot);
    ans = min(ans, mp(max_sz, u));
    return ans;
}

void process(int u, int fa, int sym) {
    vis[col[u]]++;
    if (vis[col[u]] == 1) {
        color[col[u]] += sz[u] * sym;
        sum += sz[u] * sym;
    }
    for (int v : G[u])
        if (v != fa && !centroid[v]) process(v, u, sym);
    vis[col[u]]--;
}

void update(int u, int fa, int num, int tot_sz) {
    vis[col[u]]++;
    if (vis[col[u]] == 1) {
        num++;
        sum -= color[col[u]];
    }
    ans[u] += sum + (LL)num * tot_sz;
    for (int v : G[u])
        if (v != fa && !centroid[v]) update(v, u, num, tot_sz);

    if (vis[col[u]] == 1) {
        sum += color[col[u]];
    }
    vis[col[u]]--;
}

void solve(int u) {
    get_size(u, 0);
    int root = get_root(u, 0, sz[u])._2;
    get_size(root, 0);

    process(root, 0, 1);
    vis[col[root]] = 1;
    for (int v : G[root]) {
        if (centroid[v]) continue;
        color[col[root]] -= sz[v];
        sum -= sz[v];
        process(v, root, -1);
        update(v, root, 0, sz[root] - sz[v]);
        process(v, root, 1);
        color[col[root]] += sz[v];
        sum += sz[v];
    }
    ans[root] += sum;
    vis[col[root]] = 0;
    process(root, 0, -1);

    centroid[root] = true;
    for (int v : G[root])
        if (!centroid[v]) solve(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> col[i];
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    solve(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}
