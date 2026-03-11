ll extgcd(ll a, ll b, ll &p, ll &q) { // argmin{|p|+|q|:ap+bq=gcd(a,b)}
    if (b == 0) {
        p = 1, q = 0;
        return a;
    }
    ll d = extgcd(b, a % b, q, p);
    q -= a / b * p;
    return d;
}
ll minv(ll a, ll m) {
    ll y, z;
    extgcd(a, m, y, z);
    return (y % m + m) % m;
}