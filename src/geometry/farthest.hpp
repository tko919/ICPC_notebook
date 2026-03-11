T farthest(const Poly &a) {
    int n = a.size();
    int x = 0, y = 0;
    rep(i, 1, n) {
        if (a[i].Y > a[x].Y)
            x = i;
        if (a[i].Y < a[y].Y)
            y = i;
    }
    T res = abs(a[x] - a[y]);
    int i = x, j = y;
    do {
        if (cross(a[(i + 1) % n] - a[i], a[(j + 1) % n] - a[j]) < 0)
            i = (i + 1) % n;
        else
            j = (j + 1) % n;
        chmax(res, abs(a[i] - a[j]));
    } while (i != x or j != y);
    return res;
}