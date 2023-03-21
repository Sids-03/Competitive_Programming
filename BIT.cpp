
struct BIT{
    ll N;
    vll bit;
 
    void init(ll n){
        N = n;
        bit.assign(n+1 , 0);
    }
    void add(int x, int k) {
        for (; x <= N; x += x & -x) bit[x] += k;
    }
    int rsum(int l, int r) {
        int res = 0;
        for (int x = l - 1; x; x -= x & -x) res -= bit[x];
        for (int x = r; x; x -= x & -x) res += bit[x];
        return res;
    }
    ll find(ll val){
        ll curr = 0  , prevsum = 0;
        for(int i = log2(N) ; i >= 0 ; i --){
            if(curr + (1 << i) < N && prevsum + bit[curr + (1 << i)]  < val){
                prevsum  += bit[curr + (1 << i)];
                curr  += (1 << i);
            }
        }
        return curr + 1;
    }
    void prints(void){
        printv(bit);
    }
};
