ll RNG(ll L, ll R) { // [L,R]
    static mt19937_64 gen(
        chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(L, R)(gen);
}
