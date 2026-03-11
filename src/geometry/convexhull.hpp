Poly ConvexHull(Poly &a) {
    int n = a.size(), k = 0;
    sort(ALL(a), [](const Point &p, const Point &q) {
        return (eq(p.Y, q.Y) ? p.X < q.X : p.Y < q.Y);
    });
    Poly res(n * 2);
    for (int i = 0; i < n; res[k++] = a[i++]) {
        while (k >= 2 and
               cross(res[k - 1] - res[k - 2], a[i] - res[k - 1]) < -eps)
            k--;
    }
    for (int i = n - 2, t = k + 1; i >= 0; res[k++] = a[i--]) {
        while (k >= t and
               cross(res[k - 1] - res[k - 2], a[i] - res[k - 1]) < -eps)
            k--;
    }
    res.resize(k - 1);
    return res;
}