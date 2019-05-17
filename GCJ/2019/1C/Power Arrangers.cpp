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

const int N = 10;

vector<int> vec[N], rep;
bool vis[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, f;
    cin >> T >> f;

    for (int kase = 1; kase <= T; kase++) {
        //cout << "Case #" << kase << ": ";
        reset(vis, 0);

        rep.clear();
        for (int i = 0; i < 119; i++) rep.pb(i * 5 + 1);

        string ans;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) vec[j].clear();
            for (auto it : rep) {
                cout << it << endl;
                char c;
                cin >> c;
                vec[c - 'A'].pb(it);
            }

            int minm = 10000, id = -1;
            for (int j = 0; j < 5; j++) {
                if (vis[j]) continue;
                if (vec[j].size() < minm) {
                    minm = vec[j].size();
                    id = j;
                }
            }

            ans.pb(char(id + 'A'));
            rep = vec[id];
            for (auto &it : rep) ++it;
            vis[id] = true;
        }

        cout << ans << endl;
        char y;
        cin >> y;
        assert(y == 'Y');
    }
    return 0;
}
