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

int id(char c) { return c - 'a'; }

string s;

int num[100], num2[100];

int a[100], b[100];
int n;

LL fac[100];

LL solve(int pos, int *a) {
    for (int i = 0; i < 26; i++) num2[i] = num[i];
    for (int i = 0; i < pos; i++) num2[a[i]]--;

    LL ans = 0;

    for (int i = 0; i < a[pos]; i++) {
        if (num2[i]) {
            int rem = n - pos - 1;
            LL cur = fac[rem];
            num2[i]--;

            for (int j = 0; j < 26; j++) cur /= fac[num2[j]];
            ans += cur;
            num2[i]++;
        }
    }
    return ans;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= 20; i++) fac[i] = fac[i - 1] * i;
    getline(cin, s);
    stringstream ss(s);

    char c;
    while (ss >> c) {
        num[id(c)]++;
        num2[id(c)]++;
        n++;
    }

    cin >> c;
    int st = id(c);

    num2[st]--;
    a[0] = b[0] = st;

    //cout << num2[0] << ' ' << num2[1] << ' ' << num2[2] << endl;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (num2[j]) {
                num2[j]--;
                a[i] = j;
                break;
            }
        }
    }

    for (int i = 0; i < 26; i++) num2[i] = num[i];
    num2[st]--;

    for (int i = 1; i < n; i++) {
        for (int j = 25; j >= 0; j--) {
            if (num2[j]) {
                num2[j]--;
                b[i] = j;
                break;
            }
        }
    }

    //for (int i = 0; i < n; i++) cout << b[i] << ' ';
    //cout << endl;

    LL ans = 0;
    for (int i = 0; i < n - 1; i++) ans = (ans + solve(i, a)) % 2019;

    cout << (ans + 1) % 2019 << ' ';

    ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = (ans + solve(i, b)) % 2019;
    }
    cout << (ans + 1) % 2019 << '\n';
    return 0;
}
