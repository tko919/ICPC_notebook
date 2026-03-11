bool cmp(const Point &a, const Point &b) {
    auto sub = [&](Point a) {
        return (a.Y < 0 ? -1 : (a.Y == 0 && a.X >= 0 ? 0 : 1));
    };
    if (sub(a) != sub(b))
        return sub(a) < sub(b);
    return a.Y * b.X < a.X * b.Y;
}