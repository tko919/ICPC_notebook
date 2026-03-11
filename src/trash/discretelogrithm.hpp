ll ModLog(ll a, ll b, ll p) {
    ll g = 1;
    for (ll t = p; t; t >>= 1)
        g = g * a % p;
    g = gcd(g, p);
    ll t = 1, c = 0;
    for (; t % g; c++) {
        if (t == b)
            return c;
        t = t * a % p;
    }
    if (b % g)
        return -1;
    t /= g, b /= g;
    ll n = p / g, h = 0, gs = 1;
    for (; h * h < n; h++)
        gs = gs * a % n;
    map<ll, ll> bs;
    for (ll s = 0, e = b; s < h; bs[e] = ++s)
        e = e * a % n;
    for (ll s = 0, e = t; s < n;) {
        e = e * gs % n, s += h;
        if (bs.count(e)) {
            return c + s - bs[e];
        }
    }
    return -1;
}