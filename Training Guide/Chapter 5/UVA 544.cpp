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

const int N = 200 + 10;

map<string, int> id;
int n, m, cnt;
int G[N][N];

int ID(string& s) {
    if (id.count(s)) return id[s];
    else return id[s] = cnt++;
}

bool vis[N];

bool check(int val, int s, int t) {
    reset(vis, 0);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < n; i++)
            if (G[u][i] >= val && !vis[i]) {
                vis[i] = true;
                q.push(i);
            }
    }
    return vis[t];
}

int main() {
    int kase = 0;
    while (cin >> n >> m && n) {
        id.clear();
        reset(G, 0);
        cnt = 0;
        for (int i = 0; i < m; i++) {
            string s1, s2;
            int val;
            cin >> s1 >> s2 >> val;
            G[ID(s1)][ID(s2)] = G[ID(s2)][ID(s1)] = val;
        }
        string s1, s2;
        cin >> s1 >> s2;
        int s = ID(s1), t = ID(s2);

        int l = 1, r = 10001;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (check(mid, s, t)) l = mid + 1;
            else r = mid;
        }
        cout << "Scenario #" << ++kase << '\n';
        cout << l - 1 << " tons\n\n";
    }
    return 0;
}
