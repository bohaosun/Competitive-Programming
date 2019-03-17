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

const int N = 1123;

int a[N][N], n, m;

vector<int> row[N], col[N];

int my_find(vector<int> &vec, int val) {
    int idx = lower_bound(all(vec), val) - vec.begin();
    return idx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            row[i].pb(a[i][j]);
            col[j].pb(a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) { sort(all(row[i])); uni(row[i]); }
    for (int i = 1; i <= m; i++) { sort(all(col[i])); uni(col[i]); }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int idx1 = my_find(row[i], a[i][j]);
            int idx2 = my_find(col[j], a[i][j]);
            cout << max(idx1, idx2) + max(row[i].size() - idx1, col[j].size() - idx2) << ' ';
        }
        cout << '\n';
    }

    return 0;
}
