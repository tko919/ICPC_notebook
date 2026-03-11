template <typename T> void NTT(vector<T> &a, bool type) {
    int n = SZ(a), s = 0;
    while ((1 << s) < n)
        s++;
    assert((1 << s) == n);
    static T g = 2;
    static vector<T> pw, ipw;
    while (g.pow((T::get_mod() - 1) >> 1) == 1) {
        g += 1;
    }
    while (SZ(pw) <= s) {
        pw.push_back(g.pow((T(-1).v) >> SZ(pw)));
        ipw.push_back(pw.back().inv());
    }
    vector<T> b(n);
    rep(i, 1, s + 1) {
        int wid = 1 << (s - i);
        T base = type ? ipw[i] : pw[i], rot = 1;
        for (int y = 0; y < n / 2; y += wid) {
            for (int x = 0; x < wid; x++) {
                auto L = a[y << 1 | x];
                auto R = a[y << 1 | x | wid] * rot;
                b[y | x] = L + R;
                b[y | x | n >> 1] = L - R;
            }
            rot *= base;
        }
        swap(a, b);
    }
}

template <typename T>
vector<T> mult(vector<T> &a, vector<T> &b, bool same = 0) {
    if (a.empty() or b.empty())
        return {};
    int n = SZ(a), m = SZ(b), deg = 1;
    while (deg < n + m - 1)
        deg <<= 1;
    vector<T> ret(deg);
    rep(i, 0, n) ret[i] = a[i];
    NTT(ret, 0);
    if (same) {
        rep(i, 0, deg) ret[i] *= ret[i];
    } else {
        vector<T> c(deg);
        rep(i, 0, m) c[i] = b[i];
        NTT(c, 0);
        rep(i, 0, deg) ret[i] *= c[i];
    }
    NTT(ret, 1);
    ret.resize(n + m - 1);
    T e = T(deg).inv();
    for (auto &x : ret)
        x *= e;
    return ret;
}