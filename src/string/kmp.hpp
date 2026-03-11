// kmp[i] := max{ l ≤ i | s[:l] == s[(i+1)-l:i+1] }
// minimal period: i+1-kmp[i]
vector<int> KMP(string &s) {
    vector<int> a(SZ(s));
    rep(i, 1, n) {
        int g = a[i - 1];
        while (g and s[i] != s[g])
            g = a[g - 1];
        a[i] = g + (s[i] == s[g]);
    }
    return a;
}