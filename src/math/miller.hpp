bool Miller(ll n) {
    if (n < 2 or (n & 1) == 0)
        return (n == 2);
    ll d = n - 1;
    while ((d & 1) == 0)
        d >>= 1;
    vector<ll> seeds;
    if (n < (1 << 30))
        seeds = {2, 7, 61};
    else
        seeds = {2, 325, 9375, 28178, 450775, 9780504};
    for (auto &x : seeds) {
        if (n <= x)
            break;
        ll t = d;
        ll y = mpow(x, t, n);
        while (t != n - 1 and y != 1 and y != n - 1) {
            y *= y;
            t <<= 1;
        }
        if (y != n - 1 and (t & 1) == 0)
            return 0;
    }
    return 1;
}