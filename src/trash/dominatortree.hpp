class Dominator {
    int idx = 0, n;
    vector<int> p, m;
    vector<int> par, ord, sdom, U, idom;
    vector<vector<int>> bucket, g, rev;
    int root(int v) {
        if (p[v] == v)
            return v;
        int rt = root(p[v]);
        if (sdom[m[v]] > sdom[m[p[v]]])
            m[v] = m[p[v]];
        return p[v] = rt;
    }
    int eval(int v) {
        root(v);
        return m[v];
    }
    void unite(int x, int y) {
        p[y] = x;
    }
    void dfs(int v) {
        sdom[v] = idx;
        ord[idx++] = v;
        for (int nxt : g[v])
            if (sdom[nxt] < 0) {
                par[nxt] = v;
                dfs(nxt);
            }
    }

  public:
    Dominator(int _n)
        : idx(0), n(_n), p(_n), m(_n), par(_n), ord(_n, -1), sdom(_n, -1),
          U(_n), idom(_n, -1), bucket(_n), g(_n), rev(_n) {
        rep(i, 0, n) p[i] = m[i] = i;
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        rev[v].push_back(u);
    }
    vector<int> run(int rt) {
        dfs(rt);
        for (int i = n - 1; i >= 0; i--) {
            int w = ord[i];
            if (w == -1)
                continue;
            for (int nxt : rev[w])
                if (sdom[nxt] >= 0) {
                    int u = eval(nxt);
                    chmin(sdom[w], sdom[u]);
                }
            bucket[ord[sdom[w]]].push_back(w);
            for (int v : bucket[par[w]])
                U[v] = eval(v);
            bucket[par[w]].clear();
            unite(par[w], w);
        }
        rep(i, 1, n) {
            int w = ord[i];
            if (w < 0)
                continue;
            int u = U[w];
            if (sdom[w] == sdom[u])
                idom[w] = sdom[w];
            else
                idom[w] = idom[u];
        }
        rep(i, 1, n) {
            int w = ord[i];
            if (w >= 0)
                idom[w] = ord[idom[w]];
        }
        idom[rt] = rt;
        return idom;
    }
};