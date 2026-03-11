template <typename T> vector<int> gauss(vector<vector<T>> &M, int c = -1) {
    int h = SZ(M), w = SZ(M[0]);
    if (M.empty())
        return {};
    if (c == -1)
        c = w;
    int cur = 0;
    vector<int> res;
    // det = 1;
    rep(i, 0, c) {
        if (cur == h)
            break;
        rep(j, cur, h) if (M[j][i] != 0) {
            swap(M[cur], M[j]);
            // if (cur != j)
            //     det *= -1;
            break;
        }
        // det *= M[cur][i];
        if (M[cur][i] == 0)
            continue;
        rep(j, 0, h) if (j != cur) {
            T z = M[j][i] / M[cur][i];
            rep(k, i, w) M[j][k] -= M[cur][k] * z;
        }
        res.push_back(i);
        cur++;
    }
    return res;
}