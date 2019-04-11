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

const int N = 70 + 5;

struct Node {
    int x, y, z;
};

string s[N];
int n;
Node pre[N][N][N];
int d[N][N][N];
queue<Node> q;


void init() {
    reset(d, -1);
    cin >> n;
    int x, y, z;
    cin >> x >> y >> z;
    --x; --y; --z;
    for (int i = 0; i < n; i++) cin >> s[i];

    q.push({ x, y, z });
    d[x][y][z] = 0;
}

vector<pii> ans;
void print(int x, int y, int z) {
    //cout << x << ' ' << y << ' ' << z << endl;
    //cout << d[x][y][z] << endl;
    if (d[x][y][z] == 0) {
        reverse(all(ans));
        cout << ans.size() << '\n';
        for (auto it : ans) cout << it._1 + 1 << ' ' << it._2 + 1 << '\n';
    } else {
        Node cur = pre[x][y][z];
        //cout << cur.x << ' ' << cur.y << ' ' << cur.z << endl;
        if (x != cur.x) {
            ans.pb({ cur.x, x });
        } else if (y != cur.y) {
            ans.pb({ cur.y, y });
        } else {
            ans.pb({ cur.z, z });
        }
        print(cur.x, cur.y, cur.z);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    while (!q.empty()) {
        Node u = q.front(); q.pop();
        int x = u.x, y = u.y, z = u.z;
        //cout << x << ' ' << y << ' ' << z << endl;
        //cout << d[x][y][z] << endl;

        vector<int> vec = { x, y, z };
        sort(all(vec));
        if (vec == vector<int>{ 0, 1, 2 }) {
            print(x, y, z);
            return 0;
        }

        // move x:
        for (int i = 0; i < n; i++) {
            if (i == y || i == z) continue;
            if (s[x][i] == s[y][z]) {
                if (d[i][y][z] == -1) {
                    d[i][y][z] = d[x][y][z] + 1;
                    pre[i][y][z] = { x, y, z };
                    q.push({ i, y, z });
                }
            }
        }

        // move y:
        for (int i = 0; i < n; i++) {
            if (i == x || i == z) continue;
            if (s[y][i] == s[x][z]) {
                if (d[x][i][z] == -1) {
                    d[x][i][z] = d[x][y][z] + 1;
                    pre[x][i][z] = { x, y, z };
                    q.push({ x, i, z });
                }
            }
        }

        // move z:
        for (int i = 0; i < n; i++) {
            if (i == x || i == y) continue;
            if (s[z][i] == s[x][y]) {
                if (d[x][y][i] == -1) {
                    d[x][y][i] = d[x][y][z] + 1;
                    pre[x][y][i] = { x, y, z };
                    q.push({ x, y, i });
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
