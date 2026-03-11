template <typename T>
vector<T> MinPlusConvolution_convex_convex(vector<T> &a, vector<T> &b) {
    int n = SZ(a), m = SZ(b);
    vector<T> c(n + m - 1);
    c[0] = a[0] + b[0];
    for (int k = 0, i = 0; k < n + m - 2; k++) {
        int j = k - i;
        if (j == m - 1 or (i < n - 1 and a[i + 1] + b[j] < a[i] + b[j + 1])) {
            c[k + 1] = a[++i] + b[j];
        } else {
            c[k + 1] = a[i] + b[++j];
        }
    }
    return c;
}