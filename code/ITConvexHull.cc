struct Line {
    long long a, b; // y = ax + b
    Line(long long a = 0, long long b = -INF): a(a), b(b) {}
    long long eval(long long x) {
        return a * x + b;
    }
};
 
struct Node {
    Line line;
    int l, r;
    Node *left, *right;
 
    Node(int l, int r): l(l), r(r), left(NULL), right(NULL), line() {}
 
    void update(int i, int j, Line newLine) {
        if (r < i || j < l) return;
        if (i <= l && r <= j) {
            Line AB = line, CD = newLine;
            if (AB.eval(valueX[l]) < CD.eval(valueX[l])) swap(AB, CD);
            if (AB.eval(valueX[r]) >= CD.eval(valueX[r])) {
                line = AB;
                return;
            }
            int mid = valueX[l + r >> 1];
            if (AB.eval(mid) < CD.eval(mid))
                line = CD, left->update(i, j, AB);
            else
                line = AB, right->update(i, j, CD);
            return;
        }
        left->update(i, j, newLine);
        right->update(i, j, newLine);
    }
 
    long long getMax(int i) {
        if (l == r) return line.eval(valueX[i]);
        if (i <= (l + r >> 1)) return max(line.eval(valueX[i]), left->getMax(i));
        return max(line.eval(valueX[i]), right->getMax(i));
    }
};
 
Node* build(int l, int r) {
    Node *x = new Node(l, r);
    if (l == r) return x;
    x->left = build(l, l + r >> 1);
    x->right = build((l + r >> 1) + 1, r);
    return x;
}