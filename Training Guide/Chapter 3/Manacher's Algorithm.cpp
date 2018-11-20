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

const int N = 123456;

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

Manacher solver;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> solver.s) {
        solver.init();
        cout << solver.solve() << '\n';
    }
    return 0;
}
