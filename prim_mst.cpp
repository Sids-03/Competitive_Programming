
ll n , m , tot_wt , e;
vector<vector<pll>>graph , tree;
vll parent , dist;


void prim_mst(ll source ){
    set<pll>st;
    st.insert({0,source});
    dist[source] = 0;
    vector<bool>vis(n+1 , false);
    while(!st.empty()){
        auto  x = *st.begin();
        st.erase(x);
        ll u = x.second;
        if(vis[u]){
            continue;
        }
        ll v = parent[u];
        ll w = x.first;
        tree[v].pb({w , u});
        tree[u].pb({w , v});
        e++;
        vis[u] = true;
        tot_wt += x.first;
        for(auto edge: graph[u]){
            if(!vis[edge.second] && edge.first < dist[edge.second]){
                st.erase({dist[edge.second] , edge.second});
                dist[edge.second] = edge.first;
                parent[edge.second] = u;
                st.insert({edge.first , edge.second});
            }
        }
    }
}
// if e != n , then it is impossible to form the mst

void init( ){
    graph.resize(n+1);
    parent.assign(n+1 ,0);
    dist.assign(n+1 , INF);
    tree.resize(n+1);
}

//good q: https://codeforces.com/contest/609/problem/E
//https://codeforces.com/contest/609/submission/186681679

