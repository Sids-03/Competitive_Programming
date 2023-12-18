template<typename T, int SZ>
struct Basis {
    int bits;
    array<int, 20> basis {};
 
    Basis() : bits(SZ) {}
 
    void Add(T x) {
        for (int i = bits-1; i >= 0 and x > 0; --i) {
            if (basis[i]) x = min(x, x ^ basis[i]);
            else {basis[i] = x; x = 0;}
        }
    }
    void Merge(const Basis &other) {
        for (int i = bits-1; i >= 0; --i) {
            if (!other.basis[i]) break;
            Add(other.basis[i]);
        }
    }
    bool isPossible(T k) const {
        for (int i = bits-1; i >= 0; --i) {
            k = min(k, k ^ basis[i]);
        }
        return k == 0;
    }
    T max_xor(){
		T res = 0;
		for(int i = bits - 1; i >= 0; i--)
			if(!((res >> i) & 1) && basis[i])
				res ^= basis[i];
 
		return res;
	}
};

using T = Basis<int, 20>;

// link: https://codeforces.com/gym/493310/submission/237680600
