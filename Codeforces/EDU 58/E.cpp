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

const int N = 512345;

int max_minm, max_maxm, n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    max_minm = 0, max_maxm = 0;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            max_minm = max(max_minm, x);
            max_maxm = max(max_maxm, y);
        } else {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            if (max_minm <= x && max_maxm <= y) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
