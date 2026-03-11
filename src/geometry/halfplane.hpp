Poly HalfplaneIntersection(vector<Line> &H) {
    sort(ALL(H), [&](Line &l1, Line &l2) { return cmp(l1.dir, l2.dir); });
    auto outside = [&](Line &L, Point p) -> bool {
        return cross(L.dir, p - L.a) < -eps;
    };
    deque<Line> deq;
    int sz = 0;
    rep(i, 0, SZ(H)) {
        while (sz > 1 and
               outside(H[i], Intersection(deq[sz - 1], deq[sz - 2]))) {
            deq.pop_back();
            sz--;
        }
        while (sz > 1 and outside(H[i], Intersection(deq[0], deq[1]))) {
            deq.pop_front();
            sz--;
        }
        if (sz > 0 and fabs(cross(H[i].dir, deq[sz - 1].dir)) < eps) {
            if (dot(H[i].dir, deq[sz - 1].dir) < 0) {
                return {};
            }
            if (outside(H[i], deq[sz - 1].a)) {
                deq.pop_back();
                sz--;
            } else
                continue;
        }
        deq.push_back(H[i]);
        sz++;
    }
    while (sz > 2 and outside(deq[0], Intersection(deq[sz - 1], deq[sz - 2]))) {
        deq.pop_back();
        sz--;
    }
    while (sz > 2 and outside(deq[sz - 1], Intersection(deq[0], deq[1]))) {
        deq.pop_front();
        sz--;
    }
    if (sz < 3)
        return {};
    deq.push_back(deq.front());
    Poly ret;
    rep(i, 0, sz) ret.push_back(Intersection(deq[i], deq[i + 1]));
    return ret;
}