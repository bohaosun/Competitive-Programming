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
 
/*
 * YES if and only if there's no vertex with degree 2
 *
 * Proof:
 *
 * only if part: Obvious
 *
 * if part: for any edge (u, v). If both u and v have degree one: trivial. Or u or v's degree is at least three, then
 * there's a way to add x to the edge without modifying other edges.
 *
 * Suppose it's u with degree at least 3. Then it can reach at least 3 different leaves l1, l2, l3 with simple path.
 * Suppose l1 is the one contains the edge. Then (l1, l2, +0.5x), (l1, l3, +0.5x), (l2, l3, -0.5x) will do so.
 */
 
const int N = 112345;
 
int n, cnt[N];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        ++cnt[x];
        ++cnt[y];
    }
    
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 2) {
            cout << "NO\n";
            return 0;
        }
    }
    
    cout << "YES\n";
    return 0;
}
