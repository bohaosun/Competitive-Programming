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

const int N = 100 + 10;
const int dw[] = { 1, -1, 0, 0, 0, 0 };
const int dl[] = { 0, 0, -1, 1, 0, 0 };
const int dh[] = { 0, 0, 0, 0, -1, 1 };

struct Node {
    int h, w, l;
    int d, b;
};

int d[N][N][N];  // blood
int h, w, l, blood;
string s[N][N];

Node A, B, S, E;

bool cmp(Node a, Node b) {
    return a.h == b.h && a.w == b.w && a.l == b.l;
}

int solve() {
    queue<Node> q;
    q.push(S);
    d[S.h][S.w][S.l] = blood;

    while (!q.empty()) {
        Node u = q.front(); q.pop();
        if (cmp(u, E)) return u.d;
        if (u.b == 1) continue;


        if (cmp(u, A)) {
            //cout << d[B.h][B.w][B.l] << endl;
            if (d[B.h][B.w][B.l] >= u.b) continue;
            u.h = B.h; u.w = B.w; u.l = B.l;
        } else if (cmp(u, B)) {
            if (d[A.h][A.w][A.l] >= u.b) continue;
            u.h = A.h; u.w = A.w; u.l = B.l;
        }

        //cout << u.h << ' ' << u.w << ' ' << u.l << ' ' << u.d << ' ' << u.b << endl;

        for (int i = 0; i < 6; i++) {
            int hh = u.h + dh[i], ww = u.w + dw[i], ll = u.l + dl[i];
            if (hh < 0 || ww < 0 || ll < 0 || hh >= h || ww >= w || ll >= l) continue;
            if (s[hh][ww][ll] == 'X') continue;

            int cur = u.b - 1;
            if (isdigit(s[hh][ww][ll])) cur = s[hh][ww][ll] - '0';
            if (d[hh][ww][ll] < cur) {
                d[hh][ww][ll] = cur;
                q.push({ hh, ww, ll, u.d + 1, cur });
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> h >> w >> l >> blood;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) cin >> s[i][j];
    }

    A = B = { -1, -1, -1 };

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < l; k++) {
                if (s[i][j][k] == 'S') {
                    S = { i, j, k, 0, blood };
                } else if (s[i][j][k] == 'E') {
                    E = { i, j, k, };
                } else if (s[i][j][k] == 'A') {
                    A = { i, j, k };
                } else if (s[i][j][k] == 'B') {
                    B = { i, j, k };
                }
            }
        }
    }

    cout << solve() << '\n';
    return 0;
}
