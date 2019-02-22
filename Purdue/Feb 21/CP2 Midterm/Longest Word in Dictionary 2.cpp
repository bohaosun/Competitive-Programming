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

const int max_node = 3123456;
const int sigma_size = 30;

bool ok[112345];

struct Trie {
    int ch[max_node][sigma_size], val[max_node], sz;
    void init() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }

    int idx(char c) { return c - 'a'; }

    void insert(string &s, int v) {  // Assume v != 0.
        int u = 0;
        int n = s.length();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void solve(int u) {
        for (int i = 0; i < 26; i++) {
            if (ch[u][i] && val[ch[u][i]]) {
                ok[val[ch[u][i]] - 1] = true;
                solve(ch[u][i]);
            }
        }
    }
};



string s, cur;
vector<string> vec;
Trie solver;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    getline(cin, s);
    stringstream ss(s);
    solver.init();

    while (ss >> cur) {
        vec.pb(cur);
    }

    for (int i = 0; i < vec.size(); i++) {
        solver.insert(vec[i], i + 1);
    }

    solver.solve(0);

    int maxm = -1, id = -1;

    for (int i = 0; i < vec.size(); i++) {
        if (ok[i]) {
            if (id == -1 || vec[i].length() > maxm || (vec[i].length() == maxm && vec[i] < vec[id])) {
                maxm = vec[i].length();
                id = i;
            }
        }
    }

    cout << vec[id] << '\n';
    return 0;
}
