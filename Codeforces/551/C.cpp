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

int n;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    if (n & 1) { cout << ":(\n"; return 0; }
    if (s[n - 1] == '(') { cout << ":(\n"; return 0; }

    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') ++l;
        else if (s[i] == ')') ++r;
    }

    if (l > n / 2 || r > n / 2) {
        cout << ":(\n";
        return 0;
    }

    int tot = 0, addl = n / 2 - l, addr = n / 2 - r;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') ++tot;
        else if (s[i] == ')') --tot;
        else {
            if (addl) { --addl; tot++; s[i] = '('; }
            else if (addr) { --addr; --tot; s[i] = ')'; }
        }

        if (i < n - 1 && tot <= 0) { cout << ":(\n"; return 0; }
        if (i == n - 1 && tot != 0) { cout << ":(\n"; return 0; }
    }

    cout << s << '\n';
    return 0;
}
