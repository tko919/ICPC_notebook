template <typename T, T (*f)(T, T), T (*e)()> struct RBST {
    struct Node {
        Node *l, *r;
        int cnt;
        T x, sum;
        Node() = default;
        Node(T x) : x(x), sum(x), l(0), r(0) { cnt = 1; }
    };
    RBST(int n) : pool(n) {}
    int cnt(const Node *t) { return t ? t->cnt : 0; }
    T sum(const Node *t) { return t ? t->sum : e(); }
    Node *update(Node *t) {
        t->cnt = cnt(t->l) + cnt(t->r) + 1;
        t->sum = f(f(sum(t->l), t->x), sum(t->r));
        return t;
    }
    vector<Node> pool;
    int ptr = 0;
    inline Node *alloc(const T &v) {
        if (si(pool) == ptr)
            pool.resize(si(pool) * 2);
        return &(pool[ptr++] = Node(v));
    }
    Node *merge(Node *l, Node *r) {
        if (!l or !r)
            return l ? l : r;
        if (RNG(0, cnt(l) + cnt(r) - 1) < cnt(l)) {
            l->r = merge(l->r, r);
            return update(l);
        }
        r->l = merge(l, r->l);
        return update(r);
    }
    pair<Node *, Node *> split(Node *t, int k) {
        if (!t)
            return {t, t};
        if (k <= cnt(t->l)) {
            auto [l, r] = split(t->l, k);
            t->l = r;
            return {l, update(t)};
        }
        auto [l, r] = split(t->r, k - cnt(t->l) - 1);
        t->r = l;
        return {update(t), r};
    }
    void insert(Node *&t, int k, const T &v) {
        auto [l, r] = split(t, k);
        t = merge(merge(l, alloc(v)), r);
    }
};