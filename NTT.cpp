const ll mod = 998244353;


namespace getPrimitive{
    ll powmod (ll a, ll b, ll p) {
        ll res = 1;
        while (b)
            if (b & 1)
                res = ll (res * 1ll * a % p),  --b;
            else
                a = ll (a * 1ll * a % p),  b >>= 1;
        return res;
    }
   
    // to generate primitive root 
    ll generator (ll p) {
        vector<ll> fact;
        ll phi = p-1,  n = phi;
        for (ll i=2; i*i<=n; ++i)
            if (n % i == 0) {
                fact.push_back (i);
                while (n % i == 0)
                    n /= i;
            }
        if (n > 1)
            fact.push_back (n);

        for (ll res=2; res<=p; ++res) {
            bool ok = true;
            for (size_t i=0; i<fact.size() && ok; ++i)
                ok &= powmod (res, phi / fact[i], p) != 1;
            if (ok)  return res;
        }
        return -1;
    }

};


namespace NTT {
    vll perm, wp[2];
    const ll mod = 998244353, G = 3;    ///G is the primitive root of M(can be calculated using generator)
    ll root, inv, N, invN;

    ll power(ll a, ll p) {
        ll ans = 1;
        while (p) {
            if (p & 1) ans = (1LL*ans*a)%mod;
            a = (1LL*a*a)%mod;
            p >>= 1;
        }
        return ans;
    }
    // (mod-1)%n == 0 , condition for NTT, otherwise use CRT
    void precalculate(ll n) {
        assert( (n&(n-1)) == 0 && (mod-1)%n==0);
        N = n;
        invN = power(N, mod-2);
        perm = wp[0] = wp[1] = vector<ll>(N);
 
        perm[0] = 0;
        for (ll k=1; k<N; k<<=1)
            for (ll i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
 
        root = power(G, (mod-1)/N);
        inv = power(root, mod-2);
        wp[0][0]=wp[1][0]=1;
 
        for (ll i=1; i<N; i++) {
            wp[0][i] = (wp[0][i-1]*1LL*root)%mod;
            wp[1][i] = (wp[1][i-1]*1LL*inv)%mod;
        }
    }
 
    void ntt(vector<ll> &v, bool invert = false) {
        if (v.size() != perm.size())   precalculate(v.size());
        for (ll i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);
 
        for (ll len = 2; len <= N; len *= 2) {
            for (ll i=0, d = N/len; i<N; i+=len) {
                for (ll j=0, idx=0; j<len/2; j++, idx += d) {
                    ll x = v[i+j];
                    ll y = (wp[invert][idx]*1LL*v[i+j+len/2])%mod;
                    v[i+j] = (x+y>=mod ? x+y-mod : x+y);
                    v[i+j+len/2] = (x-y>=0 ? x-y : x-y+mod);
                }
            }
        }
        if (invert) {
            for (ll &x : v) x = (x*1LL*invN)%mod;
        }
    }
 
    vector<ll> multiply(vector<ll> a, vector<ll> b) {
        ll n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        a.resize(n);
        b.resize(n);
        ntt(a);
        ntt(b);
        for (ll i=0; i<n; i++) a[i] = (a[i] * 1LL * b[i])%mod;
        ntt(a, true);
        return a;
    }

    //if polynomial exponentiation needed, instead resize the size of polynomial to atleast 5n , then exponentiate the coefficients and then inverse transform
};

 
vll binpow(vll b,ll p){
    vll ans=vll(1,1);
    while(p > 0){
        if(p&1){
            ans = NTT::multiply(ans,b);
        }
        cout << b.size() << endl;
        b = NTT::multiply(b,b);
        cout << b.size() << " " <<  count(all(b) , 0) << endl;
        p = p >> 1;
    }
    return ans;
}
