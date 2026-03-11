struct Run {
    using P = pair<int, int>;
    using T = pair<int, P>;
    string s;
    vector<vector<P>> run;
    vector<T> sub(string t, string r) {
        int x = t.size(), y = r.size();
        string p = t, q = r;
        reverse(ALL(p));
        q.insert(q.end(), ALL(t));
        q.insert(q.end(), ALL(r));
        vector<int> v1 = Zalgo(p), v2 = Zalgo(q);
        vector<T> res;
        rep(i, 0, x) {
            int a = x - i, b = i - v1[a], c = max(0, y - v2[y + i]);
            if (x + y - b - c >= 2 * a)
                res.push_back({a, {b, c}});
        }
        return res;
    }
    void rec(int lb, int rb) {
        if (rb - lb <= 1)
            return;
        int m = (lb + rb) / 2;
        string t(s.begin() + lb, s.begin() + m),
            r(s.begin() + m, s.begin() + rb);
        auto ret = sub(t, r);
        for (auto &[a, bc] : ret) {
            auto [b, c] = bc;
            run[a].push_back({lb + b, rb - c});
        }
        reverse(ALL(t));
        reverse(ALL(r));
        ret = sub(r, t);
        for (auto &[a, bc] : ret) {
            auto [b, c] = bc;
            run[a].push_back({lb + c, rb - b});
        }
        rec(lb, m);
        rec(m, rb);
    }
    Run(string _s) : s(_s) {
        int n = s.size();
        run.clear();
        run.resize(n + 1);
        rec(0, n);
        auto cmp = [&](P p, P q) {
            return P{p.first, -p.second} < P{q.first, -q.second};
        };
        rep(t, 1, n + 1) {
            sort(ALL(run[t]), cmp);
            int mx = -1;
            vector<P> tmp;
            for (auto p : run[t])
                if (chmax(mx, p.second))
                    tmp.push_back(p);
            run[t] = tmp;
        }
    }
};