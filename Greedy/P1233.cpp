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
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 5123;

vector<pii> vec;
int n;
bool vis[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        vec.pb({ x, y });
    }
    sort(all(vec));

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        ans++;
        int last = vec[i]._2;
        for (int j = i + 1; j < n; j++) {
            if (vis[j] || vec[j]._2 < last) continue;
            vis[j] = true;
            last = vec[j]._2;
        }
    }
    cout << ans << '\n';
    return 0;
}
