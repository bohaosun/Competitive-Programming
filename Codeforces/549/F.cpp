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

const double eps = 1e-10;

struct Point {
    LL x, y;
    Point(LL x = 0, LL y = 0): x(x), y(y) {}
};
int dcmp(LL x) {
    if (abs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y / p); }
/**
 * The < here is theoretically not correct. But we can use this to remove duplicate points.
 */
bool operator < (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
LL Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }

int convexHull(Point *p, int n, Point *ans) {
    sort(p, p + n);
    n = unique(p, p + n) - p;

    int sz = 0;

    for (int i = 1; i < n; i++) {
        if (p[sz].x == p[i].x) p[sz].y = p[i].y;
        else p[++sz] = p[i];
    }


    int m = 0;
    for (int i = 0; i <= sz; i++) {
        while (m > 1 && dcmp(Cross(ans[m - 1] - ans[m - 2], p[i] - ans[m - 2])) >= 0) m--;
        ans[m++] = p[i];
    }
    return m - 1;
}

const int N = 112345;

int n;
Point p[N];
Point ans[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    complex<double> cur;
    cout << cur.real() << ' ' << cur.imag() << endl;

    cin >> n;
    for (int i = 0; i < n; i++) {
        LL x, y;
        cin >> x >> y;
        y -= x * x;
        p[i] = { x, y };
    }

    cout << convexHull(p, n, ans) << '\n';
    return 0;
}
