int n , q;

const int maxN = 3e5+1;
vll sol;

struct DSU{
    vector<pll> st[4*maxN];
    vll p;
    //path compression wont work during rollbacks, so rank compression
    vll rank;
    // e is basically storing the states, where .first is storing the present, and .second is storing the past to the moment where it was changed(cool)
    vector<pair<int&, int>> e;
    // op is basically storing by how much or how the value changed 
    vll op;
    int ans = 0;

    void init(int n){
        p.resize(n+1); rank.assign(n+1 , 1);
        for(int i = 0 ; i<= n ; i++) p[i] = i;
        ans = n;
    }

    int get(int u){
        if(u == p[u]){
            return u;
        }
        return get(p[u]);
    }

    void add(int u , int v){
        u = get(u); v = get(v);
        if(u == v){
            op.pb(0);
            return;
        }
        if(rank[u] > rank[v]) swap(u , v);
        ans--;
        op.pb(-1);
        e.pb({p[u] , p[u]});
        p[u] = v;
        e.pb({rank[v] , rank[v]});
        rank[v] += rank[u];
    }
    // update the range of queries from the index it starts to the index it ends [l,r] and total range will be [0,Q]
    void upd(int node , int l , int r , int lx, int rx, pll p){
        if(lx >= r || rx <= l){
            return;
        }
        if(lx >= l && rx <= r){
            st[node].pb(p);
        }else{
            int mid = (lx+rx)/2;
            upd(2*node+1 , l , r , lx , mid , p);
            upd(2*node+2 , l , r , mid , rx , p);
        }
    }

    void undo(){
        if(!op.back()){
            op.pop_back();
            return;
        }else{
            ans++;
            op.pop_back();
            for(int i = 0 ; i <2 ; i ++){
                e.back().first = e.back().second;
                e.pop_back();
            }
        }
    }

    //dfs in the interval tree

    void build(int node, int l , int r){
        for(auto it: st[node]){
            add(it.first , it.second);
        }
        if(r-l == 1){
            sol.pb(ans);
        }else{
            int mid = (l+r)/2;
            build(2*node+1 , l , mid);
            build(2*node+2 , mid ,r);
        }
        for(auto it: st[node]){
            undo();
        }
    }
};

