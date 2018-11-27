class Treap {
    struct Node {
        int key, prior, size;
        int now;
        Node *l, *r;
 
        Node(int key): key(key), prior((rand() & 0xFFFF) << 10 | (rand())), size(1), l(NULL), r(NULL), now(1) {}
        ~Node() { delete l; delete r; }
    };
 
    int size(Node *x) { return x ? x->size : 0; }
 
    void update(Node *x) {
        if (!x) return;
        x->size = size(x->l) + size(x->r) + x->now;
    }
 
    Node* join(Node *l, Node *r) {
        if (!l || !r) return l ? l : r;
        if (l->prior < r->prior)
            return l->r = join(l->r, r), update(l), l;
        else
            return r->l = join(l, r->l), update(r), r;
    }
 
    void split(Node *v, int x, Node* &l, Node* &r) {
        if (!v)
            l = r = NULL;
        else if (v->key < x)
            split(v->r, x, v->r, r), l = v;
        else
            split(v->l, x, l, v->l), r = v;
        update(v);
    }
 
    void show(Node *x) {
        if (!x) return;
        show(x->l);
        cout << x->key << '-' << x->now << " | ";
        show(x->r);
    }
 
    Node *root;
 
public:
    Treap(): root(NULL) {}
    ~Treap() { delete root; }
 
    bool insert(int x) {
        Node *l, *mid, *r;
        split(root, x, l, mid);
        split(mid, x + 1, mid, r);
        if (mid) {
            mid->now++;
            mid->size++;
        } else {
            mid = new Node(x);
        }
        root = join(join(l, mid), r);
        return true;
    }
  
    int countSmaller(int x) {
        Node *l, *r;
        split(root, x, l, r);
        int res = size(l);
        root = join(l, r);
        return res;
    }

    int countSmallerOrEqual(int x) {
        return countSmaller(x + 1);
    }

    int countGreaterOrEqual(int x) {  
        return size() - countSmaller(x);
    }
 
    int size() const { return root ? root->size : 0; }
 
    void show() {
        cout << "{";
        show(root);
        cout << "}\n";
    }
};
