struct dsu {
    vector<int> parnt, sz, chckPoints , nxt;
    vector<pair<int, int> > updates;
    int cmp;
 
    dsu(int n) {
        sz.assign(n + 1, 1);
        parnt.resize(n + 1);
        nxt.resize(n + 1) ;
        iota(parnt.begin(), parnt.end(), 0);
        iota(nxt.begin(), nxt.end(), 1);
        updates.clear();
        cmp = n;
    }
 
    int find(int u) {
        while (parnt[u] != u) u = parnt[u];
        return u;
    }
    
    int mergeRange(int l , int r) {
        if(nxt[l] > r) return nxt[l] ;
        merge(l , nxt[l]) ;
        return nxt[l] = mergeRange(nxt[l] , r) ;
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            return false;
        }
        if (sz[v] > sz[u]) swap(u, v);
        sz[u] += sz[v];
        parnt[v] = u;
        updates.emplace_back(v, u);
        cmp--;
        return true;
    }
 
    void snapshot() {
        chckPoints.push_back(updates.size());
    }
 
    void rollBack() {
        if (chckPoints.empty()) return;
        while (chckPoints.back() != updates.size()) {
            auto [v , u] = updates.back();
            sz[u] -= sz[v];
            parnt[v] = v;
            cmp++;
            updates.pop_back();
        }
        chckPoints.pop_back();
    }
};
