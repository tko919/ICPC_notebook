template <class F> int max_right(int L, F ch) const {
    int l = sz + L, w = 1;
    M ansL = m1();
    for (; L + w <= sz; l >>= 1, w <<= 1)
        if (l & 1) {
            if (not ch(f(ansL, data[l])))
                break;
            ansL = f(ansL, data[l++]);
            L += w;
        }
    while (l <<= 1, w >>= 1) {
        if (L + w <= sz && ch(f(ansL, data[l]))) {
            ansL = f(ansL, data[l++]);
            L += w;
        }
    }
    return L;
}
template <class F> int min_left(int R, F ch) const {
    int r = sz + R, w = 1;
    M ansR = m1();
    for (; R - w >= 0; r >>= 1, w <<= 1)
        if (r & 1) {
            if (not ch(f(data[r - 1], ansR)))
                break;
            ansR = f(data[--r], ansR);
            R -= w;
        }
    while (r <<= 1, w >>= 1) {
        if (R - w >= 0 && ch(f(data[r - 1], ansR))) {
            ansR = f(data[--r], ansR);
            R -= w;
        }
    }
    return R;
}