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
#include <complex>

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

const int N = 15 + 5;

string s[N];
int n, m;
int r[N][N], c[N][N];
int sg[N][N][N][N];
int cnt;

bool judge(int r1, int c1, int r2, int c2) {
    return r1 == 0 && c1 == 0 && r2 == n - 1 && c2 == m - 1;
}

int mex(vector<int> &vec) {
    if (vec.empty() || vec[0] > 0) return 0;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[i - 1] + 1) return vec[i - 1] + 1;
    }
    return vec[vec.size() - 1] + 1;
}

int solve(int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) return 0;
    int &ans = sg[r1][c1][r2][c2];
    if (ans > -1) return ans;

    vector<int> vec;
    for (int i = r1; i <= r2; i++) {
        if (r[i][c2] < c1) {
            int tmp = solve(r1, c1, i - 1, c2) ^ solve(i + 1, c1, r2, c2);
            if (judge(r1, c1, r2, c2) && tmp == 0) cnt += c2 - c1 + 1;
            vec.pb(tmp);
        }
    }

    for (int i = c1; i <= c2; i++) {
        if (c[r2][i] < r1) {
            int tmp = solve(r1, c1, r2, i - 1) ^ solve(r1, i + 1, r2, c2);
            if (judge(r1, c1, r2, c2) && tmp == 0) cnt += r2 - r1 + 1;
            vec.pb(tmp);
        }
    }

    sort(all(vec));
    uni(vec);

    return ans = mex(vec);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int kase = 1; kase <= T; kase++) {
        cout << "Case #" << kase << ": ";
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> s[i];

        for (int i = 0; i < n; i++) {
            int last = -1;
            for (int j = 0; j < m; j++) {
                if (s[i][j] == '#') last = j;
                r[i][j] = last;
            }
        }

        for (int i = 0; i < m; i++) {
            int last = -1;

            for (int j = 0; j < n; j++) {
                if (s[j][i] == '#') last = j;
                c[j][i] = last;
            }
        }

//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < m; j++) cout << c[i][j] << ' ';
//            cout << endl;
//        }

        reset(sg, -1);
        cnt = 0;
        solve(0, 0, n - 1, m - 1);

//        for (int r1 = 0; r1 < n; r1++) {
//            for (int r2 = r1; r2 < n; r2++) {
//                for (int c1 = 0; c1 < m; c1++) {
//                    for (int c2 = c1; c2 < m; c2++)
//                        cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << ' ' << sg[r1][c1][r2][c2] << endl;
//                }
//            }
//        }

        if (!sg[0][0][n - 1][m - 1]) cout << 0 << '\n';
        else cout << cnt << '\n';
    }
    return 0;
}
