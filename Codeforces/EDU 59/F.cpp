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

const int N = 512;
const LL INF = LL(1e15);

int n;
LL W[N][N];
LL Lx[N], Ly[N];
int lef[N];
bool S[N], T[N];
LL slack[N];

void AddEdge(int u, int v, LL w) {
    W[u][v] = max(W[u][v], w);
}

bool match(int u) {
    S[u] = true;
    for(int i = 1; i <= n; i++) if (!T[i]) {
            if (Lx[u] + Ly[i] == W[u][i]) {
                T[i] = true;
                if (!lef[i] || match(lef[i])) {
                    lef[i] = u;
                    return true;
                }
            } else {
                slack[i] = min(slack[i], Lx[u] + Ly[i] - W[u][i]);
            }
        }
    return false;
}

void update() {
    LL a = INF;
    for (int i = 1; i <= n; i++) if (!T[i])
            a = min(a, slack[i]);
    for (int i = 1; i <= n; i++) {
        if (S[i]) Lx[i] -= a;
        if (T[i]) Ly[i] += a;
    }
}

LL solve() {
    for (int i = 1; i <= n; i++) {
        lef[i] = Lx[i] = Ly[i] = 0;
        for (int j = 1; j <= n; j++)
            Lx[i] = max(Lx[i], W[i][j]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) slack[j] = INF;
        for (;;) {
            for (int j = 1; j <= n; j++) S[j] = T[j] = false;
            if (match(i)) break; else update();
        }
    }

    for (int i = 1; i <= n; i++)
        if (!lef[i] || W[lef[i]][i] == -INF) return -1;
    LL ans = 0;
    for (int i = 1; i <= n; i++) ans += Lx[i] + Ly[i];
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        LL a, b, k;
        cin >> a >> b >> k;
        for (int j = 1; j <= n; j++) {
            if (j <= k + 1) AddEdge(i, j, a - b * (j - 1));
            else AddEdge(i, j, a - b * k);
        }
    }
    cout << solve() << '\n';
    return 0;
}
