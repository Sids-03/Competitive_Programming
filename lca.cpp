
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
        up.assign(n, vector<int>(31, -1));
    }
    LCA(){};
    LCA(int n){
        init(n);
    }

    inline void add_edge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    inline void dfs(int v, int p , int dis){
        tin[v] = ++timer;
        depth[v] = dis;

        up[v][0] = p;
        for (int i = 1; i < 31; i++){
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (int u : g[v]){
            if (u != p){
                dfs(u, v , dis+1);
            }
        }
        tout[v] = ++timer;
    }

    void dfs(int root = 0){
        dfs(root, root , 0);
    }

    inline bool upper(int u, int v){
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v){
        if (upper(u, v)) return u;
        if (upper(v, u)) return v;
        for (int i = 30 ; i >= 0; i--){
            if (!upper(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }

    inline int dist(int u, int v){
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

};
