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
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define reset(x, y) memset(x, y, sizeof(x))
#define BUG(x) cerr << #x << " = " << (x) << endl
#define BUGP(x) cout << #x << " = " << (x)._1 << ", " << (x)._2 << endl
using namespace std;

typedef long long LL;
typedef pair<int, int> pii;
typedef pair <LL, LL> pll;

const int dr[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, -1, 1, -1, 1};
// Head

const int N = 10000000 + 10;
const LL INF = LL(1e15);

int freq[N], n;
int arr[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr[i] = x;
        ++freq[x];
    }

    LL ans = INF;
    LL a = -1, b = -1;

    for (int i = 1; i <= 10000000; i++) {
        LL cura = -1, curb = -1;
        for (int j = i; j < N; j += i) {
            if (freq[j] == 1) {
                if (cura == -1) cura = j;
                else { curb = j; break; }
            } else if (freq[j] >= 2) {
                if (cura == -1) cura = curb = j;
                else curb = j;
                break;
            }
        }

        if (curb == -1) continue;
        if (ans > cura * curb / i) {
            ans = cura * curb / i;
            a = cura;
            b = curb;
        }
    }

    vector<int> vec;

    for (int i = 0; i < n; i++) {
        if (arr[i] == a) {
            vec.pb(i + 1);
            break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == b) {
            vec.pb(i + 1);
            break;
        }
    }
    sort(all(vec));
    cout << vec[0] << ' ' << vec[1] << '\n';
    return 0;
}
