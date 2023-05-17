int n, l;
vector<vector<int>> adj;
struct LCA{
    vector<vector<int>> g;
    vector<vector<int>> up;
    vector<int> tin, tout, depth;
    int timer = 0;

    inline void init(int n){
        n++;
        g.resize(n);
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        int l = 31 - __builtin_clz(n);
        up.assign(n, vector<int>(l + 1, 0));
    }
    LCA(){};
    LCA(int n){
        init(n);
    }

    inline void add_edge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    inline void dfs(int v, int p){
        tin[v] = tout[v] = ++timer;
        depth[v] = (p == v ? 0 : depth[p] + 1);

        up[v][0] = p;
        for (int i = 1; i < (int)up[v].size(); i++){
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (int u : g[v]){
            if (u != p){
                dfs(u, v);
                tout[v] = tout[u];
            }
        }
    }

    void dfs(int root = 0){
        dfs(root, root);
    }

    inline bool upper(int u, int v){
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    inline int lca(int u, int v){
        if (upper(u, v)) return u;
        if (upper(v, u)) return v;
        for (int i = (int)up[u].size() - 1; i >= 0; i--){
            if (!upper(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }

    inline int dist(int u, int v){
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

};
