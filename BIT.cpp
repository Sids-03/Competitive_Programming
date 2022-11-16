struct BIT{
    ll N;
    vll bit;
 
    void init(ll n){
        N = n;
        bit.assign(n+1 , 0);
    }
    void update(ll ind , ll val){
        while(ind <= N){
            bit[ind]+= val;
            ind += (ind & (-ind));
        }
    }
    ll psum(ll ind){
        ll ans = 0;
        while(ind > 0){
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    ll rsum(ll l , ll r){
        return psum(r)-psum(l-1);
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
