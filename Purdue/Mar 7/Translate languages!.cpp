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

const int N = 112;
const int INF = 0x3f3f3f3f;
unordered_map<string, int> pic;

int n, m, a[N][N], d[N];
vector<int> vec;

void bfs() {
    reset(d, 0x3f);
    d[0] = 0;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i <= n; i++) {
            if (d[i] > d[u] + 1 && a[u][i] < INF) {
                d[i] = d[u] + 1;
                q.push(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    pic["English"] = 0;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        pic[s] = i;
    }

    reset(a, 0x3f);
    for (int i = 0; i < m; i++) {
        string s1, s2;
        int x, y, dis;
        cin >> s1 >> s2 >> dis;
        x = pic[s1]; y = pic[s2];
        a[x][y] = a[y][x] = dis;
    }

    bfs();
    for (int i = 0; i <= n; i++) vec.pb(i);
    sort(all(vec), [](int a, int b) { return d[a] < d[b]; });

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d[vec[i]] >= INF) { cout << "Impossible\n"; return 0; }
        int cur = INF;
        for (int j = 0; j < i; j++) {
            if (d[vec[j]] == d[vec[i]] - 1) cur = min(cur, a[vec[i]][vec[j]]);
        }
        //cout << vec[i] << ' ' << cur << endl;
        ans += cur;
    }

    cout << ans << '\n';
    return 0;
}
