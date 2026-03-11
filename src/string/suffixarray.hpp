vector<int> SA(string &s) {
    int n = SZ(s);
    vector<int> sa(n);
    iota(ALL(sa), 0);
    sort(ALL(sa),
         [&](int i, int j) { return s[i] == s[j] ? i > j : s[i] < s[j]; });
    vector<int> rank(n), c(n), cnt(n);
    rep(i, 0, n) c[i] = s[i];
    for (int len = 1; len < n; len <<= 1) {
        rep(i, 0, n) {
            if (i == 0 or c[sa[i - 1]] != c[sa[i]]) {
                rank[sa[i]] = i;
            } else {
                if (sa[i - 1] + len >= n or
                    c[sa[i - 1] + len / 2] != c[sa[i] + len / 2]) {
                    rank[sa[i]] = i;
                } else {
                    rank[sa[i]] = rank[sa[i - 1]];
                }
            }
        }
        iota(ALL(cnt), 0);
        copy(ALL(sa), c.begin());
        rep(i, 0, n) {
            int j = c[i] - len;
            if (j >= 0)
                sa[cnt[rank[j]]++] = j;
        }
        swap(rank, c);
    }
    return sa;
}

vector<int> LCP(string &S,
                vector<int> &sa) { // lcp[i]=LCP(s[sa[i]:],s[sa[i+1]:])
    int n = SZ(S);
    vector<int> rank(n), lcp(n - 1);
    rep(i, 0, n) rank[sa[i]] = i;
    int h = 0;
    rep(i, 0, n) {
        if (rank[i] + 1 < n) {
            int j = sa[rank[i] + 1];
            while (max(i, j) + h < n && S[i + h] == S[j + h])
                h++;
            lcp[rank[i]] = h;
            if (h > 0)
                h--;
        }
    }
    return lcp;
}