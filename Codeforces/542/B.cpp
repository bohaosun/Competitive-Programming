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

const int N = 112345;

int n;
vector<int> vec[N];
bool vis[N][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n * 2; i++) {
        int x;
        cin >> x;
        vec[x].pb(i);
    }


    LL ans = 0;
    vec[0] = { 1, 1 };

    for (int i = 1; i <= n; i++) {
        int dis1 = abs(vec[i][0] - vec[i - 1][0]) + abs(vec[i][1] - vec[i - 1][1]);
        int dis2 = abs(vec[i][0] - vec[i - 1][1]) + abs(vec[i][1] - vec[i - 1][0]);

        ans += min(dis1, dis2);
    }

    cout << ans << '\n';
    return 0;
}
