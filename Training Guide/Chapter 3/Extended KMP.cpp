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

const int N = 50000 + 10;

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

ExKMP solver;

int main() {
    while (cin >> solver.T >> solver.S) {
        solver.init();
        solver.GetExtend();

        bool ok = false;
        for (int i = 0; i < solver.S.length(); i++)
            if (solver.extend[i] + i == solver.S.length()) {
                ok = true;
                for (int j = i; j < solver.S.length(); j++) cout << solver.S[j];
                cout << ' ' << solver.extend[i] << '\n';
                break;
            }
        if (!ok) cout << 0 << '\n';
    }
    return 0;
}
