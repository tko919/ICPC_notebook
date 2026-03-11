int isContained(const Poly &a,
                const Point &b) { // 0:not contain,1:on edge,2:contain
    bool res = 0;
    int n = a.size();
    rep(i, 0, n) {
        Point p = a[i] - b, q = a[(i + 1) % n] - b;
        if (p.Y > q.Y)
            swap(p, q);
        if (p.Y < eps and eps < q.Y and cross(p, q) > eps)
            res ^= 1;
        if (eq(cross(p, q), .0) and dot(p, q) < eps)
            return 1;
    }
    return (res ? 2 : 0);
}