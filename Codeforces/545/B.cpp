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

const int dr[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
const int dc[] = { 0, -1, 0, 1, -1, 1, -1, 1 };
// Head

const int N = 5123;

string s[2];
vector<int> vec[5];
int n;

void print(int idx, int num) {
    for (int i = 0; i < num; i++) cout << vec[idx][i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < 2; i++) cin >> s[i];

    for (int i = 0; i < n; i++) {
        if (s[0][i] == '1' && s[1][i] == '1') vec[2].push_back(i + 1);
        else if (s[0][i] == '1') vec[0].push_back(i + 1);
        else if (s[1][i] == '1') vec[1].push_back(i + 1);
        else vec[3].push_back(i + 1);
    }

    for (int i = 0; i <= vec[0].size(); i++) {
        for (int j = 0; j <= vec[1].size(); j++) {
            if (i + j > n / 2) continue;
            int cur = i, rhs = (int)vec[1].size() - j;
            int diff = cur - rhs;

            int tot = (int)vec[2].size() - diff;
            if (tot < 0) continue;
            if (tot % 2 == 1) continue;
            int x = tot / 2;

            if (x + diff < 0) continue;  // Same number of effective now
            if (n / 2 - i - j - x > vec[3].size()) continue;  // Same size
            
            print(0, i);
            print(1, j);
            print(2, x);
            print(3, n / 2 - i - j - x);
            cout << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
