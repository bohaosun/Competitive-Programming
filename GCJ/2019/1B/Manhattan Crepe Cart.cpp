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

const int N = 112345;

int p, q;
int cnt[N][4];  // N S E W
int sum[N][4];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int kase = 1; kase <= T; kase++) {
        reset(cnt, 0);
        reset(sum, 0);
        cin >> p >> q;

        for (int i = 0; i < p; i++) {
            int x, y;
            char d;
            cin >> x >> y >> d;
            if (d == 'N') cnt[y + 1][0]++;
            else if (d == 'S') cnt[y - 1][1]++;
            else if (d == 'E') cnt[x + 1][2]++;
            else cnt[x - 1][3]++;
        }

        for (int i = 0; i < 4; i += 2) {
            for (int j = 1; j <= q; j++) sum[j][i] = sum[j - 1][i] + cnt[j][i];
        }

        for (int i = 1; i < 4; i += 2) {
            for (int j = q - 1; j >= 0; j--) sum[j][i] = sum[j + 1][i] + cnt[j][i];
        }

        int maxm = -1, idx = -1, idy = -1;

        for (int i = 0; i <= q; i++) {
            if (sum[i][0] + sum[i][1] > maxm) {
                maxm = sum[i][0] + sum[i][1];
                idy = i;
            }
        }

        maxm = -1;
        for (int i = 0; i <= q; i++) {
            if (sum[i][2] + sum[i][3] > maxm) {
                maxm = sum[i][2] + sum[i][3];
                idx = i;
            }
        }

        cout << "Case #" << kase << ": " << idx << ' ' << idy << '\n';
    }
    return 0;
}
