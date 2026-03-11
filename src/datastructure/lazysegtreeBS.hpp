template <class F> int max_right(int L, F ch) {
    if (L == n)
        return n;
    L += sz;
    rrep(i, 1, height + 1) down(L >> i);
    M sum = m1();
    do {
        while (L % 2 == 0)
            L >>= 1;
        if (!ch(f(sum, data[L]))) {
            while (L < sz) {
                down(L);
                L <<= 1;
                if (ch(f(sum, data[L])))
                    sum = f(sum, data[L++]);
            }
            return L - sz;
        }
        sum = f(sum, data[L++]);
    } while ((L & -L) != L);
    return n;
}
template <class F> int min_left(int R, F ch) {
    if (R == 0)
        return 0;
    R += sz;
    rrep(i, 1, height + 1) down((R - 1) >> i);
    M sum = m1();
    do {
        R--;
        while (R > 1 and (R & 1))
            R >>= 1;
        if (!ch(f(data[R], sum))) {
            while (R < sz) {
                down(R);
                R = (R * 2 + 1);
                if (ch(f(data[R], sum))) {
                    sum = f(data[R--], sum);
                }
            }
            return R + 1 - sz;
        }
        sum = f(data[R], sum);
    } while ((R & -R) != R);
    return 0;
}