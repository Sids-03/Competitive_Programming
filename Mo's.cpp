//Decomposing queries in blocks of sqrt(N) size and storing the results in a vector, while increasing l and r in such a way, that it is most optimal. 


const int N = 2e5 + 5; 
const int Q = 2e5 + 5; 
const int M = 1e6 + 5; 
const int SZ = sqrt(N) + 1;

struct var{
	ll l , r , idx;
} qr[Q];
int n , q , a[N]; ll freq[M];
ll ans[Q];ll cur = 0;
bool comp(var &d1, var &d2){
  int b1 = d1.l / SZ;
  int b2 = d2.l / SZ;
  if(b1 != b2){
    return b1 < b2;
  }else{
    return (b1 & 1) ? d1.r < d2.r : d1.r > d2.r;
  }
}
inline void add(ll x){...}
inline void del(ll x){...}

void mo(){
  cin >> n >> q;
  for(int i = 1; i<= n ; i++)cin >> a[i];
  for(int i = 1; i<= q ; i++){
    cin >> qr[i].l >> qr[i].r;
    qr[i].idx = i;
  }
  sort(qr+1, qr+q+1 , comp);
  for(int i = 1; i<= q ; i ++){
    while(l < qr[i].l) remove(a[l++]);
    while(l > qr[i].l) add(a[--l]);
    while(r < qr[i].r) add(a[++r]);
    while(r > qr[i].r) remove(a[r--]);
    ans[qr[i].idx] = cur;
  }
}
