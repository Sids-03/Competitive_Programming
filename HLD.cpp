template <class T>
struct graph{
    struct edge{
        int from, to;
        T cost;
    };
    int n;
    vector<edge> edges;
    vector<vector<int>> adj;
    function<bool(int)> ignore;
    graph(int n): n(n), adj(n){ }
    int link(int u , int v , T w = 1){
        int id = (int)edges.size();
        adj[u].push_back(id), adj[v].push_back(id), edges.push_back({u , v , w});
        return id;
    }
    int dlink(int u , int v , T w = 1){
        int id = (int)edges.size();
        adj[u].push_back(id), edges.push_back({u , v , w});
        return id;
    }
    graph transposed() const {
        graph res(n);
        for(auto &e: edges) res.dlink(e.to , e.from , e.cost);
        res.ignore = ignore;
        return res;
    }
    int degree(int u){
        return (int)adj[u].size();
    }
};

vector<var>ochain; // required when solving for non commutative, to store the segments from the other chain


template<int VALS_IN_EDGES = 0>
struct heavy_light_decomp{
    int n;
    vector<int> roots;
    vector<vector<int>> adj;
    vector<int> pv, pe, sz, depth, next, pos, end, order; // next stores the head of heavy chain
    template<class T>
    heavy_light_decomp(const graph<T> &g, vector<int> roots = {0}) : n(g.n), roots(roots), adj(n), pv(n , -1), pe(n ,-1) , sz(n , 1), depth(n), next(n),pos(n), end(n){
        for(auto it = 0 ; it < (int)g.edges.size() ; it++){
            if(g.ignore && g.ignore(it)) continue;
            auto &e = g.edges[it];
            adj[e.from].push_back(it), adj[e.to].push_back(it);
        }
        function<void(int, int)> dfs_init = [&](int u , int root){
            next[u] = root;
            if(pe[u] != -1) adj[u].erase(find(adj[u].begin() , adj[u].end() , pe[u]));
            for(auto &id: adj[u]){
                auto &e = g.edges[id];
                int v = u ^ e.from ^ e.to;
                pv[v] = u, pe[v] = id, depth[v] = depth[u]+1;
                dfs_init(v , u);
                sz[u] += sz[v];
                auto &f = g.edges[adj[u][0]];
                if(sz[v] > sz[u ^ f.from ^ f.to]) swap(id , adj[u][0]);
            }
        };
        int timer = 0;
        function<void(int)> dfs_hld = [&](int u){
            pos[u] = timer++;
            order.push_back(u);
            if(!adj[u].empty()){
                auto &f = g.edges[adj[u][0]];
                int hv = u ^ f.from ^ f.to;
                for(auto id: adj[u]){
                    auto &e = g.edges[id];
                    int v = u ^ e.from ^ e.to;
                    next[v] = (v == hv ? next[u] : v);
                    dfs_hld(v);
                }
            }
            end[u] = timer;
        };
        for(auto r: roots) assert(!~pv[r]),dfs_init(r , r), dfs_hld(r);
    }
    int lca (int u,  int v){
        for(; next[u] != next[v]; v= pv[next[v]]){
            if(depth[next[u]] > depth[next[v]]) swap(u , v);
        }
        return depth[u] < depth[v]? u : v;
    }
    int dist(int u , int v , int w = -1){
        return depth[u] + depth[v] - 2*depth[~w ? w : lca(u , v)];
    }
    //function f reads the pos in data structure
    void querynode(int u , function<void(int)>f){f(pos[u]); }
    void querysubtree(int u , function<void(int , int)> f){f(pos[u]+VALS_IN_EDGES, end[u]); }
    //function (left ,right , (left->right)?) log(n)
    // if function is non commutative , maintain 2 segment trees, one for down chain, and another for up chain, for down, the index will be ordered, but for up, you need to reverse the chain, so another segment tree
    //different will be instead of (l, r) , it will be now (n-r-1 , n-l-1)
    void querypath(int u, int v, function<void(int, int, bool)> f){
		bool dir = true;
		for(; next[u] != next[v]; v = pv[next[v]]){
			if(depth[next[u]] > depth[next[v]]) swap(u, v), dir = !dir;
			f(pos[next[v]], pos[v], dir);
		}
		if(depth[u] > depth[v]) swap(u, v), dir = !dir;
		f(pos[u] + VALS_IN_EDGES, pos[v], dir);
	}
    auto getpath(int u , int v){// O(log n)
        vector<pair<int,int>> resl, resr; // pair of indices { l , r } in the data structure; resr is reserved (v -> next[v] , pv[next[v]] -> ... )
        querypath(u , v , [&](int l , int r , bool dir){(dir? resl : resr).push_back({l , r}); });
        return pair{resl , resr};
    }
};

// Segment tree (Non commutative): https://codeforces.com/contest/1843/submission/210728065
// Lazy Segment tree : https://codeforces.com/contest/696/submission/210670196
// Vercingetorix template: https://codeforces.com/contest/117/submission/216814425

