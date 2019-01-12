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

string s;

int main() {
    cin >> s;
    int lef1 = -1, lef2 = -1;

    for (int i = 0; i < s.length(); i++) {
        if (lef1 == -1) {
            if (s[i] == '[') lef1 = i;
        } else if (lef2 == -1) {
            if (s[i] == ':') lef2 = i;
        }
    }

    if (lef1 == -1 || lef2 == -1) { cout << -1 << '\n'; return 0; }

    int rig1 = -1, rig2 = -1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (rig1 == -1) {
            if (s[i] == ']') rig1 = i;
        } else if (rig2 == -1) {
            if (s[i] == ':') rig2 = i;
        }
    }
    if (rig1 == -1 || rig2 == -1) { cout << -1 << '\n'; return 0; }
    if (lef2 >= rig2) { cout << -1 << '\n'; return 0; }

    int ans = 4;

    for (int i = lef2 + 1; i < rig2; i++) {
        if (s[i] == '|') ans++;
    }
    cout << ans << '\n';
    return 0;
}
