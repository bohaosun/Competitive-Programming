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

/**
 * For Dora, if day i and day j there's no store in common. Then obviously it's impossible.
 * Then we prove if for every pair, there's at least one store in common, then it's possble:
 *
 * Let p1, p2, ... pm be prime numbers.
 * Let ai = product of all pj such that Dora visits the store i on day j. So pj | ai if and only if Dora visits store
 * i on day j.
 *
 * Then for day k, the lcm of Dora's is always the product of all p1 to pm.
 *
 * For the other person, the lcm doesn't contain pi. So Dora wins
 */

const int N = 11234;

bitset<N> s;
int m, n;
vector<int> vec[55];

bool check(int i, int j) {
    s = 0;
    for (auto it : vec[i]) s[it] = true;
    for (auto it : vec[j]) {
        if (s[it]) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    for (int i = 0; i < m; i++) {
        int sz;
        cin >> sz;
        while (sz--) {
            int x;
            cin >> x;
            vec[i].pb(x);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (!check(i, j)) {
                cout << "impossible\n";
                return 0;
            }
        }
    }

    cout << "possible\n";
    return 0;
}
