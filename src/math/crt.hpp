ll extgcd(ll a, ll b, ll &p, ll &q) {
    if (b == 0) {
        p = 1;
        q = 0;
        return a;
    }
    ll d = extgcd(b, a % b, q, p);
    q -= a / b * p;
    return d;
}
pair<ll, ll> crt(const vector<ll> &vs, const vector<ll> &ms) {
    ll V = vs[0], M = ms[0];
    rep(i, 1, vs.size()) {
        ll p, q, v = vs[i], m = ms[i];
        if (M < m)
            swap(M, m), swap(V, v);
        ll d = extgcd(M, m, p, q);
        if ((v - V) % d != 0)
            return {0, -1};
        ll md = m / d, tmp = (v - V) / d % md * p % md;
        V += M * tmp;
        M *= md;
    }
    V = (V % M + M) % M;
    return {V, M};
}