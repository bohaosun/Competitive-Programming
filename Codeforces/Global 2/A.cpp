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

const int N = 312345;

bool app[N];
int maxm[N], minm[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (!app[x]) {
            app[x] = true;
            maxm[x] = minm[x] = i;
        } else {
            maxm[x] = i;
        }
    }

    int amaxm = 0, aminm = n + 1;
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (!app[i]) continue;
        ans = max(ans, max(maxm[i] - aminm, amaxm - minm[i]));
        aminm = min(aminm, minm[i]);
        amaxm = max(amaxm, maxm[i]);
    }

    cout << ans << '\n';
    return 0;
}
