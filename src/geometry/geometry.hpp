using T = double;
const T eps = 1e-12;
using Point = complex<T>;
using Poly = vector<Point>;
#define X real()
#define Y imag()
inline bool eq(const T &a, const T &b) { return fabs(a - b) < eps; }
istream &operator>>(istream &is, Point &p) {
    T x, y;
    is >> x >> y;
    p = Point(x, y);
    return is;
}

struct Line {
    Point a, b, dir;
    Line() {}
    Line(Point _a, Point _b) : a(_a), b(_b), dir(b - a) {}
    Line(T A, T B, T C) {
        if (eq(A, .0)) {
            a = Point(0, C / B), b = Point(1 / C / B);
        } else if (eq(B, .0)) {
            a = Point(C / A, 0), b = Point(C / A, 1);
        } else {
            a = Point(0, C / B), b = Point(C / A, 0);
        }
    }
};
struct Segment : Line {
    Segment() {}
    Segment(Point _a, Point _b) : Line(_a, _b) {}
};
struct Circle {
    Point p;
    T r;
    Circle() {}
    Circle(Point _p, T _r) : p(_p), r(_r) {}
};

Point unit(const Point &a) { return a / abs(a); }
T dot(const Point &a, const Point &b) { return a.X * b.X + a.Y * b.Y; }
T cross(const Point &a, const Point &b) { return a.X * b.Y - a.Y * b.X; }
Point rot(const Point &a, const T &theta) {
    return Point(cos(theta) * a.X - sin(theta) * a.Y,
                 sin(theta) * a.X + cos(theta) * a.Y);
}
Point rot90(const Point &a) { return Point(-a.Y, a.X); }
T arg(const Point &a, const Point &b, const Point &c) {
    double ret = acos(dot(a - b, c - b) / abs(a - b) / abs(c - b));
    if (cross(a - b, c - b) < 0)
        ret = -ret;
    return ret;
}

Point Projection(const Line &l, const Point &p) {
    T t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}
Point Reflection(const Line &l, const Point &p) {
    return p + (Projection(l, p) - p) * 2.;
}

bool isOrthogonal(const Line &a, const Line &b) {
    return eq(dot(a.b - a.a, b.b - b.a), .0);
}
bool isParallel(const Line &a, const Line &b) {
    return eq(cross(a.b - a.a, b.b - b.a), .0);
}
bool isIntersect(const Segment &a, const Segment &b) {
    return ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) <= 0 and
           ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) <= 0;
}
int isIntersect(const Circle &a, const Circle &b) {
    T d = abs(a.p - b.p);
    if (d > a.r + b.r + eps)
        return 4;
    if (eq(d, a.r + b.r))
        return 3;
    if (eq(d, abs(a.r - b.r)))
        return 1;
    if (d < abs(a.r - b.r) - eps)
        return 0;
    return 2;
}

T Dist(const Line &a, const Point &b) {
    Point c = Projection(a, b);
    return abs(c - b);
}
T Dist(const Segment &a, const Point &b) {
    if (dot(a.b - a.a, b - a.a) < eps)
        return abs(b - a.a);
    if (dot(a.a - a.b, b - a.b) < eps)
        return abs(b - a.b);
    return abs(cross(a.b - a.a, b - a.a)) / abs(a.b - a.a);
}
T Dist(const Segment &a, const Segment &b) {
    if (isIntersect(a, b))
        return .0;
    T res = min({Dist(a, b.a), Dist(a, b.b), Dist(b, a.a), Dist(b, a.b)});
    return res;
}

Point Intersection(const Line &a, const Line &b) {
    T d1 = cross(a.b - a.a, b.b - b.a);
    T d2 = cross(a.b - a.a, a.b - b.a);
    if (eq(d1, 0) and eq(d2, 0))
        return b.a;
    return b.a + (b.b - b.a) * (d2 / d1);
}
vector<Point> Intersection(const Circle &a, const Line &b) {
    vector<Point> res;
    T d = Dist(b, a.p);
    if (d > a.r + eps)
        return res;
    Point h = Projection(b, a.p);
    if (eq(d, a.r)) {
        res.push_back(h);
        return res;
    }
    Point e = unit(b.b - b.a);
    T ph = sqrt(a.r * a.r - d * d);
    res.push_back(h - e * ph);
    res.push_back(h + e * ph);
    return res;
}
vector<Point> Intersection(const Circle &a, const Circle &b) {
    vector<Point> res;
    int mode = isIntersect(a, b);
    T d = abs(a.p - b.p);
    if (mode == 4 or mode == 0)
        return res;
    if (mode == 3) {
        T t = a.r / (a.r + b.r);
        res.push_back(a.p + (b.p - a.p) * t);
        return res;
    }
    if (mode == 1) {
        if (b.r < a.r - eps) {
            res.push_back(a.p + (b.p - a.p) * (a.r / d));
        } else {
            res.push_back(b.p + (a.p - b.p) * (b.r / d));
        }
        return res;
    }
    T rc = (a.r * a.r + d * d - b.r * b.r) / d / 2.;
    T rs = sqrt(a.r * a.r - rc * rc);
    if (a.r - abs(rc) < eps)
        rs = 0;
    Point e = unit(b.p - a.p);
    res.push_back(a.p + rc * e + rs * e * Point(0, 1));
    res.push_back(a.p + rc * e + rs * e * Point(0, -1));
    return res;
}

T Area(const Poly &a) {
    T res = 0;
    int n = a.size();
    rep(i, 0, n) res += cross(a[i], a[(i + 1) % n]);
    return fabs(res / 2.);
}
T Area(const Poly &a, const Circle &b) {
    int n = a.size();
    if (n < 3)
        return .0;
    auto rec = [&](auto self, const Circle &c, const Point &p1,
                   const Point &p2) {
        Point va = c.p - p1, vb = c.p - p2;
        T f = cross(va, vb), res = .0;
        if (eq(f, .0))
            return res;
        if (max(abs(va), abs(vb)) < c.r + eps)
            return f;
        if (Dist(Segment(p1, p2), c.p) > c.r - eps)
            return c.r * c.r * arg(vb * conj(va));
        auto u = Intersection(c, Segment(p1, p2));
        Poly sub;
        sub.push_back(p1);
        for (auto &x : u)
            sub.push_back(x);
        sub.push_back(p2);
        rep(i, 0, sub.size() - 1) res += self(self, c, sub[i], sub[i + 1]);
        return res;
    };
    T res = .0;
    rep(i, 0, n) res += rec(rec, b, a[i], a[(i + 1) % n]);
    return fabs(res / 2.);
}
T Area(const Circle &a, const Circle &b) {
    T d = abs(a.p - b.p);
    if (d >= a.r + b.r - eps)
        return .0;
    if (d <= abs(a.r - b.r) + eps) {
        T r = min(a.r, b.r);
        return M_PI * r * r;
    }
    T ath = acos((a.r * a.r + d * d - b.r * b.r) / d / a.r / 2.);
    T res = a.r * a.r * (ath - sin(ath * 2) / 2.);
    T bth = acos((b.r * b.r + d * d - a.r * a.r) / d / b.r / 2.);
    res += b.r * b.r * (bth - sin(bth * 2) / 2.);
    return fabs(res);
}

Circle Incircle(const Point &a, const Point &b, const Point &c) {
    T A = abs(b - c), B = abs(c - a), C = abs(a - b);
    Point p(A * a.X + B * b.X + C * c.X, A * a.Y + B * b.Y + C * c.Y);
    p /= (A + B + C);
    T r = Dist(Line(a, b), p);
    return Circle(p, r);
}
Circle Circumcircle(const Point &a, const Point &b, const Point &c) {
    Line l1((a + b) / 2., (a + b) / 2. + (b - a) * Point(0, 1));
    Line l2((b + c) / 2., (b + c) / 2. + (c - b) * Point(0, 1));
    Point p = Intersection(l1, l2);
    return Circle(p, abs(p - a));
}

Poly tangent(const Point &a, const Circle &b) {
    return Intersection(b, Circle(a, sqrt(norm(b.p - a) - b.r * b.r)));
}
vector<Line> tangent(const Circle &a, const Circle &b) {
    vector<Line> res;
    T d = abs(a.p - b.p);
    if (eq(d, 0))
        return res;
    Point u = unit(b.p - a.p);
    Point v = u * Point(0, 1);
    for (int t : {-1, 1}) {
        T h = (a.r + b.r * t) / d;
        if (eq(h * h, 1)) {
            res.push_back(Line(a.p + (h > 0 ? u : -u) * a.r,
                               a.p + (h > 0 ? u : -u) * a.r + v));
        } else if (1 > h * h) {
            Point U = u * h, V = v * sqrt(1 - h * h);
            res.push_back(Line(a.p + (U + V) * a.r, b.p - (U + V) * (b.r * t)));
            res.push_back(Line(a.p + (U - V) * a.r, b.p - (U - V) * (b.r * t)));
        }
    }
    return res;
}
