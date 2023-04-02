typedef double ld;
typedef complex<ld> cd;
#define pvll pair<ll,vll>
// const int SIZE = 1<<19;
 
 //inv = 1 (ifft) inv = 0 (fft)
void fft(vector<cd> &a, bool inv){
    int N = (int) a.size();
    //bit permutation reversal -> (0,1,2,3,4,5,6,7) -> ([{0,4},{2,6}],[{1,5},{3,7}])
    for(int i = 1, j = 0; i < N; i++){
        int bit = N>>1;
        for(; j&bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
 
        if(i < j)
            swap(a[i], a[j]);
    }

    // omega(n,k) = (2*k*pi*i)/n; n'th roots of unity
    for(int len = 2; len <= N; len <<= 1){
        ld theta = 2*PI / len * (inv ? -1 : 1);
        cd wlen(cos(theta), sin(theta));
        for(int i = 0; i < N; i += len){
            cd w(1);
            for(int j = 0; j < len / 2; j++){
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if(inv)
        for(cd &z : a)
            z /= N;
}
 
//a = multiply(a,b) means a = a * b
 
vll multiply(vll a , vll b){
    ll n=1; vll v;
    while(n<((ll)a.size())+((ll)b.size())) n <<=1;
    vector<cd> fa(n), fb(n);
    for(int i = 0 ; i < n ; i ++) fa[i] = fb[i] = cd(0);
    for(int i = 0 ; i <a.size() ; i ++) fa[i] = cd(a[i]);
    for(int i = 0 ; i <b.size() ; i ++) fb[i] = cd(b[i]);
    fft(fa,false);
    fft(fb,false);
    for(int i = 0 ; i < n ; i ++){
        fa[i]=(fa[i]*fb[i]);
    }
    fft(fa,true);
    for (int i = 0; i < a.size() + b.size() - 1; ++i) {
        v.push_back((long long)(fa[i].real() + 0.5));
    }
    return v;
}

//exponentiation can be done, by resizing the inital array after 5n, and doing fft transformation, then exponentiating the values of points and then inverse fft
 
