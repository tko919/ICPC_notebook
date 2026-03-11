template <typename T> struct MultiEval {
    int m, n;
    vector<Poly<T>> t;
    MultiEval(vector<T> &v) {
        m = v.size(), n = 1;
        while (n < m)
            n <<= 1;
        t.resize(n << 1);
        rep(i, 0, n) {
            T w = (i < m ? v[i] : 0);
            t[n + i] = Poly<T>({-w, T(1)});
        }
        for (int i = n - 1; i; i--)
            t[i] = t[i * 2] * t[i * 2 + 1];
    }
    vector<T> run(const Poly<T> &f) {
        vector<Poly<T>> c(n * 2);
        c[1] = f % t[1];
        rep(i, 1, n) {
            c[i * 2] = c[i] % t[i * 2];
            c[i * 2 + 1] = c[i] % t[i * 2 + 1];
        }
        vector<T> ret(m);
        rep(i, 0, m) ret[i] = (SZ(c[i + n]) ? c[i + n][0] : 0);
        return ret;
    }
};