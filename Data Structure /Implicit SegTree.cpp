class SparseSegtree {
private:
    struct Node {
        int freqmn = 0;
        int freqmx = 0;
        int lazy = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    };
    Node *root = new Node;
    const int n;
 
    int combmn(int a, int b) { return min(a, b); }
    int combmx(int a, int b) { return max(a, b); }
 
    void apply(Node *cur, int len, int val) {
        (cur->lazy) += val;
        (cur->freqmn) += val;
        (cur->freqmx) += val;
    }
 
    void push_down(Node *cur, int l, int r) {
        if ((cur->left) == nullptr) { (cur->left) = new Node; }
        if ((cur->right) == nullptr) { (cur->right) = new Node; }
        int m = (l + r) / 2;
        apply(cur->left, m - l + 1, cur->lazy);
        apply(cur->right, r - m, cur->lazy);
    }
 
    void range_set(Node *cur, int l, int r, int ql, int qr, int val) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(cur, r - l + 1, val);
        } else {
            push_down(cur, l, r);
            int m = (l + r) / 2;
            range_set(cur->left, l, m, ql, qr, val);
            range_set(cur->right, m + 1, r, ql, qr, val);
            (cur->freqmn) = combmn((cur->left)->freqmn, (cur->right)->freqmn);
            (cur->freqmx) = combmx((cur->left)->freqmx, (cur->right)->freqmx);
        }
    }
 
    pair<int, int> range_sum(Node *cur, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) { return {2e18, -2e18}; }
        if (ql <= l && r <= qr) { return {cur->freqmn, cur->freqmx}; }
        push_down(cur, l, r);
        int m = (l + r) / 2;
 
        pair<int, int> n1 = range_sum(cur->left, l, m, ql, qr);
        pair<int, int> n2 = range_sum(cur->right, m + 1, r, ql, qr);
        return {combmn(n1.first, n2.first), combmx(n1.second, n2.second)};
    }
 
public:
    SparseSegtree(int n) : n(n) {}
 
    void range_set(int ql, int qr, int val) { range_set(root, 0, n - 1, ql, qr, val); }
 
    pair<int, int> range_sum(int ql, int qr) { return range_sum(root, 0, n - 1, ql, qr); }
};
