int ccw(const Point &a, Point b, Point c) {
    b -= a;
    c -= a;
    if (cross(b, c) > eps)
        return 1; // ccw
    if (cross(b, c) < -eps)
        return -1; // cw
    if (dot(b, c) < 0)
        return 2; // c,a,b
    if (norm(b) < norm(c))
        return -2; // a,b,c
    return 0;      // a,c,b
}