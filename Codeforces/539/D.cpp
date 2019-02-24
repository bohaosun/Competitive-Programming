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

/**
 * If the string contains n or n - 1 same characters then there's no solution.
 * Otherwise two cuts will be enough. Suppose the longest prefix consists the same character is s[0 : len - 1].
 *
 * Then let the prefix s[: len], mid, suffix s[n - len - 1 :]. Then suffix + mid + prefix is a palindrome and not
 * equal to the original one.
 *
 * So only have to check if one cut is enough.
 */

string s;
int cnt[30];

bool check(string &s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        if (s[l++] != s[r--]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
        if (cnt[s[i] - 'a'] >= n - 1) { cout << "Impossible\n"; return 0; }
    }

    for (int i = 1; i < n; i++) {
        string s2 = s.substr(i);
        //cout << s2 << endl;
        s2 += s.substr(0, i);
        //cout << s2 << endl;
        if (s2 != s && check(s2)) { cout << 1 << '\n'; return 0; }
    }

    cout << 2 << '\n';
    return 0;
}
