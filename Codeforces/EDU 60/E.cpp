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

const int N = 11234;

string s, t;

int result[N], pw[3], ans[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = s.length();

    pw[0] = 1; pw[1] = 26; pw[2] = sqr(26);

    for (int i = 0; i < 3; i++) {
        t.clear();
        for (int j = 0; j < n; j++) {
            int cur = (j / pw[i]) % 26;
            t.pb(char(cur) + 'a');
        }

        cout << "? " << t << endl;
        cin >> t;
        for (int j = 0; j < n; j++) result[j] += (t[j] - 'a') * pw[i];
    }

    for (int i = 0; i < n; i++) ans[result[i]] = i;
    cout << "! ";
    for (int i = 0; i < n; i++) cout << s[ans[i]];
    cout << endl;

    return 0;
}
