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

const int N = 512;

int a[N][N], n, m;
vector<int> vec[N][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    }

    for (int k = 0; k < 10; k++) {
        int cnt[] = { 0, 0, 0 };
        for (int i = 1; i <= n; i++) {
            vec[i][0].clear();
            vec[i][1].clear();

            for (int j = 1; j <= m; j++) {
                if (a[i][j] & (1 << k)) vec[i][1].pb(j);
                else vec[i][0].pb(j);
            }

            if (!vec[i][0].empty() && !vec[i][1].empty()) ++cnt[2];
            else if (!vec[i][0].empty()) ++cnt[0];
            else ++cnt[1];
        }

        if (cnt[1] & 1) {
            cout << "TAK\n";
            for (int i = 1; i <= n; i++) {
                if (vec[i][0].empty()) cout << vec[i][1][0] << ' ';
                else cout << vec[i][0][0] << ' ';
            }
            cout << '\n';
            return 0;
        }

        if (cnt[2]) {
            cout << "TAK\n";
            bool output = false;
            for (int i = 1; i <= n; i++) {
                if (vec[i][0].empty()) cout << vec[i][1][0] << ' ';
                else if (vec[i][1].empty()) cout << vec[i][0][0] << ' ';
                else {
                    if (output) { cout << vec[i][0][0] << ' '; }
                    else {
                        cout << vec[i][1][0] << ' ';
                        output = true;
                    }
                }
            }
            return 0;
        }
    }

    cout << "NIE\n";
    return 0;
}
