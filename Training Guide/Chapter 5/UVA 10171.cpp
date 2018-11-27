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

const int N = 100;
const int INF = 0x3f3f3f3f;

int idx(char c) { return c - 'A'; }

int G[N][N][2], m;
int d[N][2];

struct Node {
    int u, d;
    bool operator < (const Node& rhs) const {
        return d > rhs.d;
    }
};

void Dijkstra(int s, int id) {
    priority_queue<Node> pq;
    for (int i = 0; i < 26; i++) d[i][id] = INF;
    d[s][id] = 0;
    pq.push({ s, 0 });

    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (d[u.u][id] < u.d) continue;
        for (int v = 0; v < 26; v++)
            if (d[v][id] > d[u.u][id] + G[u.u][v][id]) {
                d[v][id] = d[u.u][id] + G[u.u][v][id];
                pq.push({ v, d[v][id] });
            }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> m && m) {
        reset(G, 0x3f);
        for (int i = 0; i < m; i++) {
            char ch, ch2;
            int id, x, y, d;
            cin >> ch;
            if (ch == 'Y') id = 0;
            else id = 1;
            cin >> ch;
            cin >> ch2;
            x = idx(ch2);
            cin >> ch2;
            y = idx(ch2);
            cin >> d;
            G[x][y][id] = min(G[x][y][id], d);
            if (ch == 'B') G[y][x][id] = min(G[y][x][id], d);
        }

        char c;
        int s, t;
        cin >> c;
        s = idx(c);
        cin >> c;
        t = idx(c);
        Dijkstra(s, 0);
        Dijkstra(t, 1);

        int ans = INF;
        vector<char> pos;
        for (int i = 0; i < 26; i++) ans = min(ans, d[i][0] + d[i][1]);
        if (ans == INF) cout << "You will never meet.\n";
        else {
            cout << ans;
            for (int i = 0; i < 26; i++)
                if (d[i][0] + d[i][1] == ans) pos.pb(char(i + 'A'));
            for (char it : pos) cout << ' ' << it;
            cout << '\n';
        }
    }
    return 0;
}
