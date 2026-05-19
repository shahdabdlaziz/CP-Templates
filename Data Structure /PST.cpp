// how many number between x and y inside range l , r
// get the kth element O(log(n))
// get the k-th element in path
// get number of distinct element in subarray or path in tree O(log(n))


struct Node {
    int value;
    Node *left, *right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
    Node(int v, Node* l, Node* r) : value(v), left(l), right(r) {}

    Node(Node* l, Node* r) : value(0), left(l), right(r) {
        if (left) value += left->value;
        if (right) value += right->value;
    }
};

struct PST {
    int n;
    vector<Node*> roots;

    PST(int n, int versions) : n(n) {
        roots.assign(versions, nullptr);
    }

    Node* build(int l, int r, vector<int>& arr) {
        if (l == r) return new Node(arr[l]);
        int mid = (l + r) / 2;
        Node* left = build(l, mid, arr);
        Node* right = build(mid + 1, r, arr);
        return new Node(left, right);
    }

    Node* update(Node* cur, int idx, int val, int lx, int rx) {
        if (lx == rx) return new Node(val);
        int mid = (lx + rx) / 2;
        if (idx <= mid) {
            Node* left = update(cur->left, idx, val, lx, mid);
            return new Node(left, cur->right);
        } else {
            Node* right = update(cur->right, idx, val, mid + 1, rx);
            return new Node(cur->left, right);
        }
    }

    int query(Node* cur, int l, int r, int lx = 0, int rx = -1) {
        if (rx == -1) rx = n - 1;
        if (!cur || l > rx || r < lx) return 0LL;
        if (l <= lx && rx <= r) return cur->value;
        int mid = (lx + rx) / 2;
        return query(cur->left, l, r, lx, mid) + query(cur->right, l, r, mid + 1, rx);
    }
    // get the kth element in path from ru to rv , rw is the lca and rpw is the parent of the lca .
    int kth(Node* ru, Node* rv, Node* rw, Node* rpw, int l, int r, int k) {
        if (l == r) return l;

        int mid = (l + r) / 2;

        int cntLeft =
            ru->left->value +
            rv->left->value -
            rw->left->value -
            rpw->left->value;

        if (cntLeft >= k)
            return kth(ru->left, rv->left, rw->left, rpw->left, l, mid, k);
        else
            return kth(ru->right, rv->right, rw->right, rpw->right, mid + 1, r, k - cntLeft);
    }

    // starting from index i get the first index such that number of distinct in range equals k .
    // build the PST using last appearance back word
    int getIdx (Node *cur , int lx , int rx , int k) {
        if(lx == rx) return lx ;

        int ansLeft = cur->left->value ;
        int md = (lx + rx) / 2 ;
        if(ansLeft >= k) {
            return getIdx(cur->left , lx , md , k) ;
        }else {
            return getIdx(cur->right , md + 1 , rx , k - ansLeft) ;
        }
    }
} ;
