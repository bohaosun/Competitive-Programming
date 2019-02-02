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
typedef pair <LL, LL> pll;
// Head

const int N = 112345;
const int M = 212;


struct Node {
    pii val;
    int id;
    bool operator < (const Node &rhs) const {
        return val < rhs.val;
    }
};

int n, m, k;
int s[N], t[N], w[N], d[N];
vector<int> vec[N];
pii maxm[N];

LL dp[N][M];

LL solve(int pos, int tim) {
    if (pos > n) return 0;
    LL &ans = dp[pos][tim];
    if (ans > -1) return ans;

    ans = solve(maxm[pos]._2 + 1, tim) + maxm[pos]._1;
    if (tim < m) ans = min(ans, solve(pos + 1, tim + 1));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> s[i] >> t[i] >> d[i] >> w[i];
        vec[s[i]].pb(i);
    }

    priority_queue<Node> pq;
    for (int i = 1; i <= n; i++) {
        maxm[i] = mp(0, i);
        for (int u : vec[i]) pq.push({ mp(w[u], d[u]), u });
        while (!pq.empty()) {
            Node u = pq.top();
            if (t[u.id] < i) { pq.pop(); continue; }
            maxm[i] = u.val;
            break;
        }
    }

    //for (int i = 1; i <= n; i++) cout << maxm[i]._1 << ' ' << maxm[i]._2 << endl;

    reset(dp, -1);
    cout << solve(1, 0) << '\n';
    return 0;
}
