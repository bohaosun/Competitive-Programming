#include <unordered_map>
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

const int N = 5123;

vector<int> vec[N];
int minm[N];
int n, m;

int dis(int i, int j) {
    if (i < j) return j - i;
    else return n - i + j;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        vec[a].pb(b);
    }

    for (int i = 1; i <= n; i++) {
        if (vec[i].empty()) {
            minm[i] = -1;
        } else {
            minm[i] = n;
            for (int j : vec[i]) {
                minm[i] = min(minm[i], dis(i, j));
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int ans = 0, cur = -1;
        for (int j = i; j <= n; j++) {
            cur++;
            int num = vec[j].size();
            if (num == 0) continue;
            ans = max(ans, cur + (num - 1) * n + minm[j]);
        }

        for (int j = 1; j < i; j++) {
            cur++;
            int num = vec[j].size();
            if (num == 0) continue;
            ans = max(ans, cur + (num - 1) * n + minm[j]);
        }
        cout << ans << ' ';
    }

    cout << '\n';
    return 0;
}
