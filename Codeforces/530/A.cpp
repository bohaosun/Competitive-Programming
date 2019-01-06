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

int main() {
    int w, h, u1, d1, u2, d2;
    cin >> w >> h >> u1 >> d1 >> u2 >> d2;
    if (d1 > d2) {
        swap(d1, d2);
        swap(u1, u2);
    }

    for (int i = d2; i <= h; i++) w += i;
    w -= u2;
    if (w < 0) w = 0;
    for (int i = d1; i < d2; i++) w += i;
    w -= u1;
    if (w < 0) w = 0;
    for (int i = 1; i < d1; i++) w += i;
    cout << w << endl;
    return 0;
}
