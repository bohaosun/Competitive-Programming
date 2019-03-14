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

/**
 * Basic
 */
const double eps = 1e-10;
const double PI = acos(-1.0);

struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};
int dcmp(double x) {
    if (abs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y / p); }
bool operator < (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
double Dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Length2(Vector A) { return Dot(A, A); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }  // In rad
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }
double Area2(Point A, Point B, Point C) { return Cross(B - A, C - A); }  // Divided by 2 to get triangle
Vector Rotate(Vector A, double rad) {
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Vector Norm(Vector A) {  // Norm with unit length, A != 0
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}

/**
 * Circles
 */

struct Circle {
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0): c(c), r(r) {}
    Point point(double a) {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

// Polar Angle of a vector
double polarAngle(Vector v) { return atan2(v.y, v.x); }

// Get two circles intersections, which are stored in sol.
// sol is not cleared.
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point> &sol) {
    double d = Length(C1.c - C2.c);
    if (dcmp(d) == 0) {
        if (dcmp(C1.r - C2.r) == 0) return -1;
        return 0;
    }
    if (dcmp(d - C1.r - C2.r) > 0) return 0;         // Seperated
    if (dcmp(abs(C1.r - C2.r) - d) > 0) return 0;    // Included

    double a = polarAngle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));

    Point p1 = C1.point(a - da), p2 = C1.point(a + da);
    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}

const int N = 20 + 5;
const double INF = 1e10;

struct Node {
    Circle cir;
    int h, vol;
    bool operator < (const Node &rhs) const {
        return h > rhs.h;
    }
} node[N];

bool full[N];
double speed[N], already[N];
int n;
vector<double> deg[N];
double f[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    cout << fixed;
    cout.precision(2);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> node[i].cir.c.x >> node[i].cir.c.y;
        cin >> node[i].h >> node[i].cir.r >> node[i].vol;
    }

    sort(node, node + n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<Point> sol;
            int num = getCircleCircleIntersection(node[i].cir, node[j].cir, sol);
            if (num < 2) continue;
            for (auto &p : sol) {
                deg[i].pb(polarAngle(p - node[i].cir.c));
                deg[j].pb(polarAngle(p - node[j].cir.c));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        sort(all(deg[i]));
        uni(deg[i]);
    }

    for (int i = 0; i < n; i++) {
        if (deg[i].empty()) {
            Point p = node[i].cir.point(0);
            for (int j = i + 1; j < n; j++) {
                if (node[j].h == node[i].h) continue;
                if (dcmp(Length(p - node[j].cir.c) - node[j].cir.r) < 0) {
                    f[i][j] = 1;
                    break;
                }
            }
        } else {
            deg[i].pb(deg[i][0] + PI * 2);
            for (int j = 0; j < deg[i].size() - 1; j++) {
                Point p = node[i].cir.point((deg[i][j] + deg[i][j + 1]) / 2);
                double ratio = (deg[i][j + 1] - deg[i][j]) / (PI * 2);

                for (int k = i + 1; k < n; k++) {
                    if (node[k].h == node[i].h) continue;
                    if (dcmp(Length(p - node[k].cir.c) - node[k].cir.r) < 0) {
                        f[i][k] += ratio;
                        break;
                    }
                }
            }
        }
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = i + 1; j < n; j++) cout << f[i][j] << ' ';
//        cout << endl;
//    }

    speed[0] = 100;
    double t = 0;
    int cnt = 0;

    while (cnt < n) {
        int id = -1;
        double minm = INF;
        for (int i = 0; i < n; i++) {
            if (dcmp(speed[i]) == 0) continue;
            if (full[i]) continue;
            double cur = (node[i].vol - already[i]) / speed[i];
            if (cur < minm) {
                minm = cur;
                id = i;
            }
        }

        if (id == -1) break;

        ++cnt;
        t += minm;
        full[id] = true;
        for (int i = 0; i < n; i++) already[i] += minm * speed[i];

        reset(speed, 0);
        speed[0] = 100;
        for (int i = 0; i < n; i++) {
            if (full[i]) {
                for (int j = i + 1; j < n; j++) speed[j] += speed[i] * f[i][j];
            }
        }
    }

    if (cnt == n) cout << t << '\n';
    else cout << "Invalid\n";

    return 0;
}
