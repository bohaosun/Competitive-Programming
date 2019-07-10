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
 
int d[N][20], f[N][20];
int n, a[N];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i][0] = a[i];
    }
 
    for (int j = 1; j < 18; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << j) - 1 > n) break;
            f[i][j] = f[i][j - 1] + f[i + (1 << (j - 1))][j - 1];
            d[i][j] = d[i][j - 1] + d[i + (1 << (j - 1))][j - 1] + (f[i][j] >= 10);
            f[i][j] %= 10;
        }
    }
 
    int q;
    cin >> q;
 
    while (q--) {
        int l, r;
        cin >> l >> r;
 
        for (int i = 0; ; i++) {
            if ((1 << i) == r - l + 1) {
                cout << d[l][i] << '\n';
                break;
            }
        }
    }
    return 0;
}
