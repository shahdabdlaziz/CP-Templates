#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// A multiset with order‐statistics (rank/select) on values of type T.
template<typename T>
struct OrderedMultiset {
    // Internally store each x as (x, unique_index) so duplicates are distinct
    using Key = pair<T,int>;
    tree<
        Key,
        null_type,
        less<Key>,
        rb_tree_tag,
        tree_order_statistics_node_update
    > t;

    int index = 0;  // increments on each insert to keep keys unique

    // ——— Inserts one copy of x. O(log n)
    void insert(T x) {
        t.insert({x, index++});
    }

    // ——— Erases a single copy of x if present. O(log n)
    void erase(T x) {
        auto it = t.lower_bound({x, 0});
        if (it != t.end() && it->first == x) {
            t.erase(it);
        }
    }

    // ——— Number of elements strictly less than x. O(log n)
    int order_of_key(T x) {
        return t.order_of_key({x, 0});
    }

    // ——— The k‑th smallest element (0‑based), or –1 if k ≥ size(). O(log n)
    T find_by_order(int k) {
        if (k < 0 || k >= (int)t.size()) return T(-1);
        return t.find_by_order(k)->first;
    }

    // ——— Total number of elements in the multiset. O(1)
    int size() {
        return t.size();
    }

    // ——— Remove all elements and reset. O(n)
    void clear() {
        t.clear();
        index = 0;
    }

    // ——— In‑order iteration (value,index) pairs
    auto begin() const { return t.begin(); }
    auto end()   const { return t.end();   }
};
