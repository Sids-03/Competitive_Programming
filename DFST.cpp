struct DFST{
    ll n, m;
    vector<vector<int>> graph, tree, back_in, back_out, dep, par;
    vector<bool>vis;

    DFST(int _n, int _m){
        n = _n, m = _m;
        graph.resize(n+1);
        tree.resize(n+1);
        back_in.resize(n+1); back_out.resize(n+1);
        par.resize(n+1); dep.assign(n+1, 0);
    }
    void add_edge(int u, int v){
        graph[u].pb(v);
        graph[v].pb(u);
    }
    void dfs(int node, int p){
        par[node] = par;
        dep[node] = dep[p]+1;
        for(auto it: graph[node]){
            if(!dep[it]){
                tree[node].pb(it);
                dfs(it, node);
            }else if(dep[it] < dep[node]-1){
                back_out[node].pb(it);
                back_in[it].pb(node);
            }
        }
    }
};


