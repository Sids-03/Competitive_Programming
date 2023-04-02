const int mod = 998244353; 
typedef double ld;
typedef complex<double> cd;
typedef vector<double> vd;
void fft(vector<cd>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<cd> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// cd z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			cd z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<cd> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (cd& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
const int M = mod;
 
vll convMod(const vll &a, const vll &b) {
	if (a.empty() || b.empty()) return {};
	vll res(a.size() + b.size() - 1);
	int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(sqrt(M));
	vector<cd> L(n), R(n), outs(n), outl(n);
    for(int i = 0 ; i < (int)a.size() ; i ++)  L[i] = cd((int)a[i] / cut, (int)a[i] % cut);
	for(int i = 0 ; i < (int)b.size() ; i ++)  R[i] = cd((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	for(int i = 0 ; i < n ; i ++) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
    for(int i = 0 ; i < (int)res.size() ; i ++){
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

vll binpow(vll b,ll p){
    vll ans=vll(1,1);
    for(;p;p>>=1){
        if(p&1)ans=convMod(ans,b);
        b=convMod(b,b);
    }
    return ans;
}

