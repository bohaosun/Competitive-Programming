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
#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define mp make_pair
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
// Head

const int N = 1123456;

struct ExKMP {
    int extend[N];  // extend[i]: the longest common prefix between S[i:] and T[0:]
    int next[N];  // next[i]: the longest common prefix between T[i:] and T[0:]
    string S;  // Find the extend of every position of S
    string T;  // Use T's prefix

    void init() { memset(next, 0, sizeof(next)); }

    void GetNext() {
        int p = 0, a = 0;
        int m = T.length();
        next[0] = m;

        for (int i = 1; i < m; i++) {
            if (i + next[i - a] >= p) {
                if (i >= p) p = i;

                while (p < m && T[p] == T[p - i]) p++;
                next[i] = p - i;
                a = i;
            } else {
                next[i] = next[i - a];
            }
        }
    }

    void GetExtend() {
        int p = 0;  // The rightmost position in S that is matched (position p is not matched)
        int a = 0;  // The start position of S that matches until p
        GetNext();

        int n = S.length();
        int m = T.length();
        for (int i = 0; i < n; i++) {
            if (i + next[i - a] >= p) {
                if (i >= p) p = i;  // p is totally not useful so start from it self.

                while (p < n && p - i < m && S[p] == T[p - i]) p++;
                extend[i] = p - i;
                a = i;
            } else {
                extend[i] = next[i - a];
            }
        }
    }
};

struct Manacher {
    string s;
    string s_new;  // The string after modifying
    int p[N * 2];
    // p[i]: the palindrome radius with center at i. The length of max-palindrome centered at i is then p[i] - 1

    void init() {
        s_new.clear();
        for (int i = 0; i < s.length(); i++) {
            s_new.push_back('#');
            s_new.push_back(s[i]);
        }
        s_new.push_back('#');
    }

    int solve() {
        int len = s_new.length();
        int max_len = -1;  // Length of the longest sub-palindrome
        int mx = 0;  // The rightmost point covered by a sub-palindrome (mx itself is not covered)
        int id = 0;  // The center of the rightmost palindrome

        for (int i = 0; i < len; i++) {
            if (i < mx) p[i] = min(p[id * 2 - i], mx - i);
            else p[i] = 1;

            while (i - p[i] >= 0 && i + p[i] < len && s_new[i - p[i]] == s_new[i + p[i]]) p[i]++;

            if (mx < i + p[i]) {
                mx = i + p[i];
                id = i;
            }

            max_len = max(max_len, p[i] - 1);
        }
        return max_len;
    }
};

string s, t;
ExKMP kmp;
Manacher manacher;
LL sum[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> t;
    reverse(all(s));
    kmp.S = s;
    kmp.T = t;
    kmp.GetExtend();

    manacher.s = s;
    manacher.init();
    manacher.solve();

    sum[0] = kmp.extend[0];
    for (int i = 1; i < s.length() + 5; i++) sum[i] = sum[i - 1] + kmp.extend[i];

    //for (int i = 0; i < s.length(); i++) cout << kmp.extend[i] << endl;

    LL ans = 0;
    for (int i = 0; i < manacher.s_new.length(); i++) {
        if (manacher.p[i] - 1 == 0) continue;
        int pa = manacher.p[i] - 1;
        //cout << i << ' ' << pa << endl;
        int pos = i / 2;

        ans += sum[pos + (pa + 1) / 2] - sum[pos];
    }
    cout << ans << '\n';
    return 0;
}
