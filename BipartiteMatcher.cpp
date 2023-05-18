struct BipartiteMatcher{
    vector<vll> G;
    vll L, R, Viz;
    void init(int n, int m){
        G.clear(), L.clear(), R.clear(), Viz.clear();
        G.resize(n), L.resize(n, -1), R.resize(m, -1), Viz.resize(n, 0);
    }
    void AddEdge(int a, int b){if(a==0||b==0)
        return; G[a].push_back(b); }
    bool Match(int node){
        if(Viz[node]) return 0;
        Viz[node] = 1;
        for(auto vec : G[node]){
            if(R[vec] == -1 || Match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return 1;
            }
        }
        return 0;
    }
    int Solve(){
        bool ok = 1;
        while(ok){
            ok = 0;
            fill(Viz.begin(), Viz.end(), 0);
            for(int i = 0; i < L.size(); i ++)
                if(L[i] == -1)
                    ok |= Match(i);
        }
        int ret = 0;
        for(int i = 0; i < L.size(); i ++)
            ret += (L[i] != -1);
        return ret;
    }
};



//https://codeforces.com/contest/1423/submission/206313203
