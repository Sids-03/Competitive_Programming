template <typename T> 
struct SparseTable {
    int n, K; 
    vector<vector<T>> st ;
    vector<int> lg ;  
    SparseTable(int _n, vector<T> &a) {
        n = _n ;
        K = 25 ;  
        st.resize(n+1, vector<T>(K+1)) ; 
        lg.resize(n+1) ;
        for(int i = 0 ; i < n ; ++i) st[i][0] = a[i] ; 
        for(int j = 1 ; j <= K ; ++j) {
            for(int i = 0 ; i + (1<<j) <= n ; ++i) {
                st[i][j] = merge(st[i][j-1], st[i+(1<<(j-1))][j-1]) ; 
            }
        }
        lg[0] = 1 ;
        for(int i = 2 ; i <= n ; ++i) lg[i] = lg[i/2] + 1 ; 
    }
    inline T merge(T a, T b) {
        return __gcd(a,b) ;
    }
    T query(int l, int r) {
        --l, --r ;
        int j = lg[r-l+1] ; 
        return merge(st[l][j], st[r-(1<<j)+1][j]) ; 
    }
};
 
