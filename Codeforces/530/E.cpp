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

/*
 * Either every row or every column is composed by only 2 characters e.g.: ABABAB\n CDCDCDCD\n ...
 *
 * If one row has three colors, then there must be three contiguous blocks in this row that has color ABC.
 * Then all rows below it are confirmed and for these three columns, each of them only has two colors. So as other
 * columns.
 */

const int N = 312345;
const int INF = int(1e9);

string s[N], ans[N], cur[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;
    for (int i = 0; i < r; i++) cin >> s[i];
    for (int i = 0; i < r; i++) cur[i].resize(c);

    string chars = "ACGT";

    int tim = INF;
    do {
        int tot = 0;
        for (int i = 0; i < r; i++) {
            int cnt0 = 0, cnt1 = 0;
            for (int j = 0; j < c; j++) {
                if (s[i][j] != chars[(i & 1) * 2 + (j & 1)]) cnt0++;
                if (s[i][j] != chars[(i & 1) * 2 + ((j ^ 1) & 1)]) cnt1++;
            }
            if (cnt0 < cnt1) {
                for (int j = 0; j < c; j++) cur[i][j] = chars[(i & 1) * 2 + (j & 1)];
                tot += cnt0;
            } else {
                for (int j = 0; j < c; j++) cur[i][j] = chars[(i & 1) * 2 + ((j ^ 1) & 1)];
                tot += cnt1;
            }
        }
        if (tot < tim) { for (int i = 0; i < r; i++) ans[i] = cur[i]; tim = tot; }

        tot = 0;
        for (int j = 0; j < c; j++) {
            int cnt0 = 0, cnt1 = 0;
            for (int i = 0; i < r; i++) {
                if (s[i][j] != chars[(i & 1) * 2 + (j & 1)]) cnt0++;
                if (s[i][j] != chars[((i ^ 1) & 1) * 2 + (j & 1)]) cnt1++;
            }

            if (cnt0 < cnt1) {
                for (int i = 0; i < r; i++) cur[i][j] = chars[(i & 1) * 2 + (j & 1)];
                tot += cnt0;
            } else {
                for (int i = 0; i < r; i++) cur[i][j] = chars[((i ^ 1) & 1) * 2 + (j & 1)];
                tot += cnt1;
            }
        }
        if (tot < tim) { for (int i = 0; i < r; i++) ans[i] = cur[i]; tim = tot; }

    } while (next_permutation(all(chars)));

    for (int i = 0; i < r; i++) cout << ans[i] << '\n';
    return 0;
}
