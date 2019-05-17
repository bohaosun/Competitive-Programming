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
#include <complex>

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

const int N = 512;

bool dead[N];
int n;
vector<int> vec[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int kase = 1; kase <= T; kase++) {
        cout << "Case #" << kase << ": ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            vec[i].clear();
            string s;
            cin >> s;
            for (int j = 0; j < s.length(); j++) {
                if (s[j] == 'R') vec[i].pb(0);
                else if (s[j] == 'P') vec[i].pb(1);
                else vec[i].pb(2);
            }
        }

        vector<int> ans;
        reset(dead, 0);
        bool ok = true;

        for (int i = 0; i < n; i++) {
            vector<int> cur;
            for (int j = 0; j < n; j++) {
                if (dead[j]) continue;
                cur.pb(vec[j][i % vec[j].size()]);
            }
            sort(all(cur));
            uni(cur);

            if (cur.empty()) break;

            if (cur.size() == 3) {
                cout << "IMPOSSIBLE\n";
                ok = false;
                break;
            }

            if (cur.size() == 1) {
                ans.pb((cur[0] + 1) % 3);
                break;
            }

            if (cur[0] + 1 == cur[1]) {
                ans.pb(cur[1]);
                for (int j = 0; j < n; j++) {
                    if (vec[j][i % vec[j].size()] == cur[0]) dead[j] = true;
                }
            } else {
                ans.pb(0);
                for (int j = 0; j < n; j++) {
                    if (vec[j][i % vec[j].size()] == 2) dead[j] = true;
                }
            }
        }

        if (!ok) continue;

        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] == 0) cout << 'R';
            else if (ans[i] == 1) cout << 'P';
            else cout << 'S';
        }
        cout << '\n';
    }
    return 0;
}
