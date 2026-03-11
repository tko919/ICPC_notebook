template <typename T>
pair<vector<T>, vector<vector<T>>> LinearEquation(vector<vector<T>> a,
                                                  vector<T> b) {
    int h = SZ(a), w = SZ(a[0]);
    rep(i, 0, h) a[i].push_back(b[i]);
    vector<int> idx = gauss(a, w);
    rep(i, idx.size(), h) if (a[i][w] != 0) return {{}, {}};
    vector<T> res(w);
    rep(i, 0, idx.size()) res[idx[i]] = a[i][w] / a[i][idx[i]];
    vector d(w, vector<T>(h + w));
    rep(i, 0, h) rep(j, 0, w) d[j][i] = a[i][j];
    rep(i, 0, w) d[i][h + i] = 1;
    int r = gauss(d, h).size();
    vector basis(w - r, vector<T>(w));
    rep(i, r, w) basis[i - r] = {d[i].begin() + h, d[i].end()};
    return {res, basis};
}