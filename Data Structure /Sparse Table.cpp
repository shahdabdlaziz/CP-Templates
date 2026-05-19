// Generic Sparse Table with both O(1) idempotent queries and O(log n) generic queries 0-Based .
template<typename T, class CMP = function<T(const T&, const T&)>>
class SparseTable {
public:
    int n;
    int max_log;
    vector<vector<T>> sp;
    CMP func;

    SparseTable(const vector<T>& a, const CMP& f)
        : func(f)
    {
        n = a.size();
        max_log = 32 - __builtin_clz(n);
        sp.assign(max_log, vector<T>());
        sp[0] = a;
        for (int j = 1; j < max_log; ++j) {
            sp[j].resize(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; ++i) {
                sp[j][i] = func(
                    sp[j-1][i],
                    sp[j-1][i + (1 << (j-1))]
                );
            }
        }
    }

    // O(1) query: works correctly only for idempotent(overlap does not affect the answer) operations (min, max, gcd, etc.)
    T query(int l, int r) const {
        int lg = __lg(r - l + 1);
        return func(
            sp[lg][l],
            sp[lg][r - (1 << lg) + 1]
        );
    }

    // O(log n) query: works for any associative operation.
    T query_log_n(int L, int R) const {
        bool first = true;
        T ans{};
        for (int log = max_log - 1; log >= 0; --log) {
            if (L + (1 << log) - 1 <= R) {
                if (first) {
                    ans = sp[log][L];
                    first = false;
                } else {
                    ans = func(ans, sp[log][L]);
                }
                L += 1 << log;
            }
        }
        return ans;
    }
};
// SparseTable sp(arr, [](int a, int b) { return gcd(a, b); });
