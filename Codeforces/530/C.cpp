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
int cnt1, cnt2, n;

int main() {
    cin >> s >> n;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '?') cnt1++;
        else if (s[i] == '*') cnt2++;
    }

    int len = s.length() - cnt1 - cnt2;
    if (n <= len) {
        int need = len - n;
        if (cnt1 + cnt2 < need) cout << "Impossible\n";
        else {
            string ans;
            int tot = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '?' || s[i] == '*') continue;
                if (i == s.length() - 1 || islower(s[i + 1])) ans.pb(s[i]);
                else {
                    if (tot < need) { tot++; }
                    else ans.pb(s[i]);
                }
            }
            cout << ans << '\n';
        }
    } else {
        if (cnt2) {
            bool ok = false;
            string ans;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '?' || s[i] == '*') continue;
                if (i == s.length() - 1) ans.pb(s[i]);
                else {
                    if (s[i + 1] == '*') {
                        if (ok) ans.pb(s[i]);
                        else {
                            ok = true;
                            for (int j = 0; j <= n - len; j++) ans.pb(s[i]);
                        }
                    } else {
                        ans.pb(s[i]);
                    }
                }
            }
            cout << ans << '\n';
        } else cout << "Impossible\n";
    }
    return 0;
}
