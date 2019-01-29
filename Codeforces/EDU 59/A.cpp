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

int q;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        cin >> s;
        bool ok = false;
        for (int i = 1; i < s.length() - 1; i++) {
            if (s[i] != '0') ok = true;
        }
        if (s[s.length() - 1] > s[0]) ok = true;
        if (ok) {
            cout << "YES\n"; cout << 2 << '\n';
            cout << s[0] << ' ';
            for (int i = 1; i < s.length(); i++) cout << s[i];
            cout << '\n';
        } else cout << "NO\n";
    }
    return 0;
}
