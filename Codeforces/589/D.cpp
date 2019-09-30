#include <bits/stdc++.h>
 
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
vector<pii> edges;
 
int n, m, st[N];
bool vis[N];
vector<int> p1, p2, p3;
int cnt[N];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
        edges.pb({ x, y });
    }
 
    // p1:
    for (auto it : edges) {
        if (it._1 == 1) vis[it._2] = true;
        if (it._2 == 1) vis[it._1] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            st[i] = 1;
            p1.pb(i);
        }
    }
 
    
    // p2:
    int id = -1;
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            id = i;
            break;
        }
    }
    if (id == -1) {
        cout << -1 << '\n';
        return 0;
    }
 
    reset(vis, 0);
    for (auto it :edges) {
        if (it._1 == id) vis[it._2] = true;
        if (it._2 == id) vis[it._1] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (st[i]) {
                cout << -1 << '\n';
                return 0;
            }
            st[i] = 2;
            p2.pb(i);
        }
    }
 
    // p3:
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            p3.pb(i);
            st[i] = 3;
        }
    }
    if (p3.empty()) {
        cout << -1 << '\n';
        return 0;
    }
 
    for (auto it : edges) {
        if (st[it._1] == st[it._2]) {
            cout << -1 << '\n';
            return 0;
        }
        ++cnt[it._1];
        ++cnt[it._2];
    }
 
    for (auto it : p1) {
        if (cnt[it] != p2.size() + p3.size()) {
            cout << -1 << '\n';
            return 0;
        }
    }
 
    for (auto it : p2) {
        if (cnt[it] != p1.size() + p3.size()) {
            cout << -1 << '\n';
            return 0;
        }
    }
 
    for (auto it : p3) {
        if (cnt[it] != p1.size() + p2.size()) {
            cout << -1 << '\n';
            return 0;
        }
    }
 
    for (int i = 1; i <= n; i++) cout << st[i] << ' ';
    cout << '\n';
    return 0;
}
