template <bool neg = 0, bool dag = 0> struct MinCostFlow {
    using P = pair<ll, int>;
    struct edge {
        int to;
        ll cap, cost;
        int rev;
        edge(int to, ll cap, ll cost, int rev)
            : to(to), cap(cap), cost(cost), rev(rev) {}
    };
    int n;
    vector<vector<edge>> g;
    vector<ll> dist, pot;
    vector<int> vpre, epre;
    MinCostFlow(int n) : n(n), g(n), dist(n), pot(n), vpre(n), epre(n) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        g[u].push_back({v, cap, cost, SZ(g[v])});
        g[v].push_back({u, 0, -cost, SZ(g[u]) - 1});
    }
    void bellmanford(int s) {
        pot.assign(n, INF);
        pot[s] = 0;
        for (;;) {
            bool upd = 0;
            rep(v, 0, n) if (pot[v] != INF) {
                for (auto &e : g[v]) {
                    if (e.cap > 0 and chmin(pot[e.to], pot[v] + e.cost))
                        upd = 1;
                }
            }
            if (!upd)
                break;
        }
    }
    void bfs(int s) {
        vector<int> deg(n), tsort;
        queue<int> que;
        rep(v, 0, n) for (auto &e : g[v]) {
            if (e.cap > 0)
                deg[e.to]++;
        }
        rep(v, 0, n) if (deg[v] == 0) { que.push(v); }
        while (!que.empty()) {
            int v = que.front();
            tsort.push_back(v);
            que.pop();
            for (auto &e : g[v])
                if (e.cap > 0) {
                    deg[e.to]--;
                    if (deg[e.to] == 0)
                        que.push(e.to);
                }
        }
        pot.assign(n, INF);
        pot[s] = 0;
        for (auto &v : tsort)
            for (auto &e : g[v])
                if (e.cap > 0) {
                    chmin(pot[e.to], pot[v] + e.cost);
                }
    }
    ll run(int s, int t, ll flow) {
        ll ret = 0;
        if (neg) {
            if (dag)
                bfs(s);
            else
                bellmanford(s);
        }
        while (flow) {
            dist.assign(n, INF);
            priority_queue<P, vector<P>, greater<P>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] != d)
                    continue;
                rep(j, 0, SZ(g[v])) {
                    auto e = g[v][j];
                    if (e.cap > 0 and
                        chmin(dist[e.to],
                              dist[v] + e.cost + pot[v] - pot[e.to])) {
                        vpre[e.to] = v;
                        epre[e.to] = j;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
            if (dist[t] == INF)
                return -INF;
            rep(v, 0, n) {
                if (pot[v] == INF or dist[v] == INF)
                    pot[v] = INF;
                else
                    pot[v] += dist[v];
            }
            ll f = flow;
            for (int v = t; v != s; v = vpre[v])
                chmin(f, g[vpre[v]][epre[v]].cap);
            assert(f > 0);
            ret += pot[t] * f, flow -= f;
            for (int v = t; v != s; v = vpre[v]) {
                auto &e = g[vpre[v]][epre[v]];
                e.cap -= f;
                g[v][e.rev].cap += f;
            }
        }
        return ret;
    }
};