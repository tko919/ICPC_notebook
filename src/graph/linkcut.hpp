template <typename M, typename N, N (*f)(N, N)> struct LCT {
    struct Node {
        Node *lp = nullptr, *rp = nullptr, *par = nullptr;
        N val;
        M sum;
        int idx, sz = 1;
        bool rev = 0;
        Node() {}
        Node(int idx, N val) : idx(idx), val(val) {}
        void inv() {
            swap(lp, rp);
            sum.inv();
            rev ^= 1;
        }
        void eval() {
            if (rev) {
                if (lp)
                    lp->inv();
                if (rp)
                    rp->inv();
                rev = 0;
            }
        }
        void update() {
            sz = 1;
            if (lp)
                sz += lp->sz;
            if (rp)
                sz += rp->sz;
            sum.merge(val, lp ? lp->sum : M(), rp ? rp->sum : M());
        }
        bool is_root() { return !par || (par->lp != this && par->rp != this); }
        void rotate() {
            Node *pp, *p, *c;
            p = par, pp = p->par;
            if (p->lp == this) {
                c = rp, rp = p, p->lp = c;
            } else {
                c = lp, lp = p, p->rp = c;
            }
            if (pp) {
                if (pp->lp == p)
                    pp->lp = this;
                if (pp->rp == p)
                    pp->rp = this;
            }
            par = pp, p->par = this;
            if (c)
                c->par = p;
            p->update(), update();
        }
        void splay() {
            eval();
            while (!is_root()) {
                Node *q = par;
                if (q->is_root()) {
                    q->eval(), eval();
                    rotate();
                } else {
                    Node *r = q->par;
                    r->eval(), q->eval(), eval();
                    if (r->lp == q) {
                        if (q->lp == this)
                            q->rotate();
                        else
                            rotate();
                        rotate();
                    } else {
                        if (q->rp == this)
                            q->rotate();
                        else
                            rotate();
                        rotate();
                    }
                }
            }
        }
    };
    LCT() {}
    Node *make(int idx, N val) { return new Node(idx, val); }
    Node *expose(Node *v) {
        Node *pre = nullptr;
        for (Node *cur = v; cur; cur = cur->par) {
            cur->splay();
            if (cur->rp)
                cur->sum.add(cur->rp->sum);
            cur->rp = pre;
            if (cur->rp)
                cur->sum.sub(cur->rp->sum);
            cur->update();
            pre = cur;
        }
        v->splay();
        return pre;
    }
    void link(Node *c, Node *p) {
        evert(c);
        expose(p);
        c->par = p, p->rp = c;
        p->update();
    }
    void cut(Node *c, Node *p) {
        evert(p);
        expose(c);
        c->lp->par = nullptr;
        c->lp = nullptr;
        c->update();
    }
    void evert(Node *v) {
        expose(v);
        v->inv();
        v->eval();
    }
    Node *lca(Node *u, Node *v) {
        expose(u);
        return expose(v);
    }
    Node *root(Node *v) {
        expose(v);
        while (v->lp)
            v->eval(), v = v->lp;
        return v;
    }
    void update(Node *v, N x) {
        expose(v);
        v->val = f(v->val, x);
        v->update();
    }
    M &query(Node *u, Node *v) { // root = u -> v
        evert(u);
        expose(v);
        return v->sum;
    }
};

// using Key = ll;
// struct Monoid {
//     ll sum, psum, csum, light;
//     Monoid() : sum(0), psum(0), csum(0), light(0) {}
//     void inv() {
//         swap(psum, csum);
//     }
//     void merge(Key val, Monoid p, Monoid c) {
//         sum = p.sum + c.sum + val + light;
//         psum = p.psum + val + light;
//         csum = c.csum + val + light;
//     }
//     void add(Monoid v) {
//         light += v.sum;
//     }
//     void sub(Monoid v) {
//         light -= v.sum;
//     }
// };
// ll f(ll x, ll y) {
//     return x + y;
// }
// using V = LCT<Monoid, Key, f>::Node *;