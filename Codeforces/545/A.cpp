#include <bits/stdc++.h>

using namespace std;

const int N = 112345;
int n, a[N], r[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    r[n] = n;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] == a[i + 1]) {
            r[i] = r[i + 1];
        } else {
            r[i] = i;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int cur = r[i] - i + 1;
        int idx = r[i] + 1;
        if (idx > n) break;
        int nxt = r[idx] - idx + 1;
        ans = max(ans, min(cur, nxt));
    }
    
    cout << ans * 2 << '\n';
    return 0;
}
