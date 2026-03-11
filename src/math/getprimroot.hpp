ll getPrimitiveRoot(ll p) {
    vector<ll> ps = Pollard(p - 1);
    for (;;) {
        ll x = RNG(1, p - 1);
        for (auto &q : ps) {
            if (mpow(x, (p - 1) / q, p) == 1)
                goto fail;
        }
        return x;
    fail:;
    }
    assert(0);
}