T Closest(Poly &a) {
    int n = a.size();
    if (n <= 1)
        return 0;
    sort(ALL(a), [&](Point a, Point b) {
        return (eq(a.X, b.X) ? a.Y < b.Y : a.X < b.X);
    });
    Poly buf(n);
    auto rec = [&](auto self, int lb, int rb) -> T {
        if (rb - lb <= 1)
            return (T)INF;
        int mid = (lb + rb) >> 1;
        auto x = a[mid].X;
        T res = min(self(self, lb, mid), self(self, mid, rb));
        inplace_merge(a.begin() + lb, a.begin() + mid, a.begin() + rb,
                      [&](auto p, auto q) { return p.Y < q.Y; });
        int ptr = 0;
        rep(i, lb, rb) {
            if (abs(a[i].X - x) >= res)
                continue;
            rep(j, 0, ptr) {
                auto sub = a[i] - buf[ptr - 1 - j];
                if (sub.Y >= res)
                    break;
                chmin(res, abs(sub));
            }
            buf[ptr++] = a[i];
        }
        return res;
    };
    return rec(rec, 0, n);
}