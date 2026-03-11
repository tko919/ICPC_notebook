ll TonelliShanks(ll a, ll p) {
    a %= p;
    if (a == 0)
        return 0;
    if (p == 2)
        return a;
    if (mpow(a, (p - 1) >> 1, p) != 1)
        return -1;
    ll b = 1;
    while (mpow(b, (p - 1) >> 1, p) == 1)
        b = Random::get(1LL, p - 1);

    ll q = p - 1, k = 0;
    while (q % 2 == 0) {
        q >>= 1;
        k++;
    }
    ll x = mpow(a, (q + 1) >> 1, p);
    b = mpow(b, q, p);
    k -= 2;
    while (mpow(x, 2, p) != a) {
        ll err = minv(a, p) * mpow(x, 2, p) % p;
        if (mpow(err, 1 << k, p) != 1)
            x = x * b % p;
        b = mpow(b, 2, p);
        k--;
    }
    return x;
}