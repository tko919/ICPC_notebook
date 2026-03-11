template <typename T> struct Comb {
    int n;
    vector<T> fact, ifact;
    Comb() {}
    Comb(int n) : fact(n + 1), ifact(n + 1) {
        fact[0] = 1;
        rep(i, 1, n + 1) fact[i] = fact[i - 1] * i;
        ifact[n] = fact[n].inv();
        rrep(i, 0, n) ifact[i] = ifact[i + 1] * (i + 1);
    }
    T Fact(int n, bool inv = 0) {
        if (n < 0)
            return 0;
        return (inv ? ifact[n] : fact[n]);
    }
    T nCr(int n, int r, bool inv = 0) {
        if (n < 0 or r < 0 or n - r < 0)
            return 0;
        return Fact(n, inv) * Fact(r, !inv) * Fact(n - r, !inv);
    }
};