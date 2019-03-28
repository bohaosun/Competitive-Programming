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
const double eps = 1e-12;
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
/**
 * The < here is theoretically not correct. But we can use this to remove duplicate points.
 */
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

// The first line: P + v * t, the second line: Q + w * t
// Need to ensure they have unique intersection before applying "GetLineIntersection". (iff cross(v, w) != 0)
// t1 = cross(w, u) / cross(v, w); t2 = cross(v, u) / cross(v, w);
Point getLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}
double distanceToLine(Point P, Point A, Point B) {  // Line: defined by A and B
    Vector v1 = B - A, v2 = P - A;
    return abs(Cross(v1, v2)) / Length(v1);
}
double distanceToSegment(Point P, Point A, Point B) {
    if (A == B) return Length(P - A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    return abs(Cross(v1, v2)) / Length(v1);
}
Point getLineProjection(Point P, Point A, Point B) {
    Vector v = B - A;
    return A + v * (Dot(v, P - A) / Dot(v, v));
}
bool segmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
bool onSegment(Point p, Point a1, Point a2) {  // segment defined by a1 and a2
    if (p == a1 || p == a2) return true;  // At the extremes
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
double polygonArea(vector<Point> &p) {  // size >= 3
    double area = 0;
    int n = p.size();
    assert(n >= 3);
    for (int i = 1; i < n - 1; i++) area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}
bool segmentIntersection(Point a1, Point a2, Point b1, Point b2) {
    if (onSegment(a1, b1, b2) || onSegment(a2, b1, b2)) return true;
    if (onSegment(b1, a1, a2) || onSegment(b2, a1, a2)) return true;
    return segmentProperIntersection(a1, a2, b1, b2);
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

// The line: P + t * v, P + v * t1 and P + v * t2 are intersections.
// return the number of intersections
// sol: all intersections. It's not cleared.
int getLineCircleIntersection(Point P, Vector v, Circle C, double &t1, double &t2, vector<Point> &sol) {
    double a = v.x, b = P.x - C.c.x, c = v.y, d = P.y - C.c.y;
    double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0) return 0;
    if (dcmp(delta) == 0) {
        t1 = t2 = -f / (2 * e);
        sol.push_back(P + v * t1);
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(P + v * t1);
    t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(P + v * t2);
    return 2;
}

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

// The tangents of the circle C passing the point p
// The directional vectors are stored in sol.
// Return the number of tangents
int getTangents(Point p, Circle C, vector<Vector> &sol) {
    Vector u = C.c - p;
    double dist = Length(u);
    if (dcmp(dist - C.r) < 0) return 0;   // Included
    else if (dcmp(dist - C.r) == 0) {
        sol.push_back(Rotate(u, PI / 2));
        return 1;
    } else {
        double ang = asin(C.r / dist);
        sol.push_back(Rotate(u, ang));
        sol.push_back(Rotate(u, -ang));
        return 2;
    }
}

// Suppose there's a ray pointing to the right.
// Cross counterclockwise: wn++, cross clockwise: wn--.
// 1: in, 0: out, -1: on the border
int isPointInPolygon(Point p, Point *poly, int n) {
    int wn = 0;  // Winding Number
    for (int i = 0; i < n; i++) {
        if (onSegment(p, poly[i], poly[(i + 1) % n])) return -1;   // Need onSegment consider extremes!!!!
        int k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i + 1) % n].y - p.y);

        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;
    return 0;
}

// Input is p. Return the number of vertices selected
// If points are not allowed on the border, change the two "<=" to "<".
int convexHull(Point *p, int n, Point *ans) {
    sort(p, p + n);
    n = unique(p, p + n) - p;

    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && dcmp(Cross(ans[m - 1] - ans[m - 2], p[i] - ans[m - 2])) <= 0) m--;
        ans[m++] = p[i];
    }
    int k = m;
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && dcmp(Cross(ans[m - 1] - ans[m - 2], p[i] - ans[m - 2])) <= 0) m--;
        ans[m++] = p[i];
    }

    if (n > 1) return m - 1;
    else return m;
}

struct Line {
    Point P;
    Vector v;
    double ang;
    Line() {}
    Line(Point P, Vector v): P(P), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const Line &rhs) const {
        return ang < rhs.ang;
    }
};

bool onLeft(Line L, Point p) {
    return dcmp(Cross(L.v, p - L.P)) > 0;
}

Point getLineIntersection(Line a, Line b) {
    return getLineIntersection(a.P, a.v, b.P, b.v);
}

// L: lines, n: the number of lines, poly: the result
// Return the number of the vertices
int halfPlaneIntersection(Line *L, int n, Point *poly) {
    sort(L, L + n);
    int head, tail;                    // The head and tail of the deque
    Point *p = new Point[n];           // Vertices of the polygon (intersection of q[i] and q[i + 1])
    Line *q = new Line[n];             // Deque of remaining lines

    q[head = tail = 0] = L[0];
    for (int i = 1; i < n; i++) {
        while (head < tail && !onLeft(L[i], p[tail - 1])) tail--;
        while (head < tail && !onLeft(L[i], p[head])) head++;
        q[++tail] = L[i];

        if (dcmp(Cross(q[tail].v, q[tail - 1].v)) == 0) {    //Parallel and same direction?
            tail--;
            if (onLeft(q[tail], L[i].P)) q[tail] = L[i];
        }
        if (head < tail) p[tail - 1] = getLineIntersection(q[tail - 1], q[tail]);
    }
    while (head < tail && !onLeft(q[head], p[tail - 1])) tail--;   // Delete useless planes
    if (tail - head <= 1) return 0;
    p[tail] = getLineIntersection(q[tail], q[head]);

    int m = 0;
    for (int i = head; i <= tail; i++) poly[m++] = p[i];
    return m;
}

/**
 * PSLG
 */
typedef vector<Point> Polygon;

struct Edge {
    int from, to;
    double ang;
};

const int maxn = 1000 + 10;   // Number of points
const int maxm = 10000 + 10;  // Number of edges

vector<Edge> edges;
struct PSLG {
    int n, m, face_cnt;
    double x[maxn], y[maxn];
    vector<int> G[maxn];
    bool vis[maxm * 2];   // If an edge has been visited
    int left[maxm * 2];   // The index of left face
    int prev[maxm * 2];   // The previous edge

    vector<Polygon> faces;
    double area[maxn];   // The area of each polygon

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
        faces.clear();
    }

    // Polar angle from -> to
    double getAngle(int from, int to) {
        return atan2(y[to] - y[from], x[to] - x[from]);
    }

    void AddEdge(int from, int to) {
        edges.pb({ from, to, getAngle(from, to) });
        edges.pb({ to, from, getAngle(to, from) });
        m = edges.size();
        G[from].pb(m - 2);
        G[to].pb(m - 1);
        vis[m - 2] = vis[m - 1] = false;
    };

    void build() {
        for (int u = 0; u < n; u++) {
            int d = G[u].size();
            sort(all(G[u]), [](int a, int b){
                return edges[a].ang < edges[b].ang;
            });
            // Must put edges outside to use lambda
            for (int i = 0; i < d; i++)
                prev[G[u][(i + 1) % d]] = G[u][i];
        }

        face_cnt = 0;
        for (int u = 0; u < n; u++) {
            for (int i = 0; i < G[u].size(); i++) {
                int e = G[u][i];
                if (!vis[e]) {
                    ++face_cnt;
                    Polygon poly;
                    for (;;) {
                        vis[e] = true; left[e] = face_cnt;
                        int from = edges[e].from;
                        poly.pb({ x[from], y[from] });
                        e = prev[e ^ 1];
                        if (e == G[u][i]) break;
                        assert(!vis[e]);
                    }
                    faces.pb(poly);
                }
            }
        }

        for (int i = 0; i < faces.size(); i++) {
            area[i] = polygonArea(faces[i]);
        }
    }
};

// Suppose all points don't coincide. Delete the situations where three points are on the same line.
Polygon simplify(const Polygon& poly) {
    Polygon ans;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i];
        Point b = poly[(i + 1) % n];
        Point c = poly[(i + 2) % n];
        if (dcmp(Cross(a - b, c - b)) != 0) ans.pb(b);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;

    while (T--) {
        Point a, b, g;
        cin >> a.x >> a.y;
        cin >> b.x >> b.y;
        cin >> g.x >> g.y;
        if (segmentIntersection({ 0, 0 }, g, a, b)) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}
