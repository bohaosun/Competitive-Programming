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

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

const int N = 10000000 + 5;

int n;
vector<int> prime;
bool vis[N];
int a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vis[1] = true;

    int m = sqrt(10000000 + 0.5);

    for (int i = 2; i <= m; i++) {
        if (!vis[i]) {
            for (int j = i * i; j <= 10000000; j += i) {
                vis[j] = true;
            }
        }
    }

    //cout << prime.size() << endl;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l, r;
    int cnt = 0;
    cin >> l >> r;
    for (int i = 0; i < n; i++) {
        if (!vis[a[i]] && a[i] >= l && a[i] <= r) cnt++;
    }
    cout << cnt << endl;
    return 0;
}
