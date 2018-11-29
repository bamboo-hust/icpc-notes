class Treap {
    struct Node {
        int key;
        uint32_t prior;
        bool rev_lazy;
        int size;
        Node *l, *r;
        Node(int key): key(key), prior(rand()), rev_lazy(false), size(1), l(nullptr), r(nullptr) {}
        ~Node() { delete l; delete r; }
    };

    inline int size(Node *x) { return x ? x->size : 0; }

    void push(Node *x) {
        if (x && x->rev_lazy) {
            x->rev_lazy = false;
            swap(x->l, x->r);
            if (x->l) x->l->rev_lazy ^= true;
            if (x->r) x->r->rev_lazy ^= true;
        }
    }

    inline void update(Node *x) {
        if (x) {
            x->size = size(x->l) + size(x->r) + 1;
        }
    }

    void join(Node *&t, Node *l, Node *r) {
        push(l); push(r);
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior < r->prior)
            join(l->r, l->r, r), t = l;
        else
            join(r->l, l, r->l), t = r;
        update(t);
    }

    void splitByKey(Node *v, int x, Node* &l, Node* &r) {
        if (!v) return void(l = r = nullptr);
        push(v);
        if (v->key < x)
            splitByKey(v->r, x, v->r, r), l = v;
        else
            splitByKey(v->l, x, l, v->l), r = v;
        update(v);
    }

    void splitByIndex(Node *v, int x, Node* &l, Node* &r) {
        if (!v) return void(l = r = nullptr);
        push(v);
        int index = size(v->l) + 1;
        if (index < x)
            splitByIndex(v->r, x - index, v->r, r), l = v;
        else
            splitByIndex(v->l, x, l, v->l), r = v;
        update(v);
    }

    void show(Node *x) {
        if (!x) return;
        push(x);
        show(x->l);
        cerr << x->key << ' ';
        show(x->r);
    }

    Node *root;
    Node *l, *m, *r;

    public:
    Treap() { root = NULL; }
    ~Treap() { delete root; }
    int size() { return size(root); }

    int insert(int x) {
        splitByKey(root, x, l, m);
        splitByKey(m, x + 1, m, r);
        int ans = 0;
        if (!m) m = new Node(x), ans = size(l) + 1;
        join(l, l, m);
        join(root, l, r);
        return ans;
    }

    int erase(int x) {
        splitByKey(root, x, l, m);
        splitByKey(m, x + 1, m, r);
        int ans = 0;
        if (m) {
            ans = size(l) + 1;
            delete m;
        }
        join(root, l, r);
        return ans;
    }

    void insertAt(int pos, int x) {
        splitByIndex(root, pos, l, r);
        join(l, l, new Node(x));
        join(root, l, r);
    }

    void eraseAt(int x) {
        splitByIndex(root, x, l, m);
        splitByIndex(m, 2, m, r);
        delete m;
        join(root, l, r);
    }

    void updateAt(int pos, int newValue) {
        eraseAt(pos);
        insertAt(pos, newValue);
    }

    int valueAt(int pos) {
        splitByIndex(root, pos, l, m);
        splitByIndex(m, 2, m, r);
        int res = m->key;
        join(l, l, m);
        join(root, l, r);
        return res;
    }

    void reverse(int from, int to) {
        splitByIndex(root, from, l, m);
        splitByIndex(m, to - from + 2, m, r);
        m->rev_lazy ^= 1;
        join(l, l, m);
        join(root, l, r);
    }
    
    void show() {
        cerr << "Size = " << size() << " ";
        cerr << "[";
        show(root);
        cerr << "]\n";
    }
};