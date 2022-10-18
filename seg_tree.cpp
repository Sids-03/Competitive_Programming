
 // 1-based indexed segment tree , with last element of range of element included
#define var ll
 
// struct var{
//   //var as per needed in question (var present in the node of the segment tree)
// 	ll x;
// };
 
struct seg_tree{
 
	ll size;
	vector<var> a;
	vector<ll> lazy;
	vector<bool> clazy;
	//declare invariant for calc
	var invariant = INF;
	
	void init(ll n){
		size = 1;
		while(size < n) size*=2;
		a.assign(2*size  , INF);
		lazy.assign(2*size ,0);
		clazy.assign(2*size , false);
	}
	
	var merge( var b , var c){
		//merge nodes of the seg_tree
		// minimum:var a = min(b , c);
		return a;
	}

    // apply operation defines what we are doing in range update , for adding a+=operation(a,b); , assignment: a = operation(a,b);
	void apply_operation(ll &a , ll b){
		//addition:a +=b;
		//assignment: a=b;
	}
	void propagate(ll node , ll lx , ll rx){
		apply_operation(a[node] , lazy[node]);
		if(lx != rx){
			if(lazy[node]){
				apply_operation(lazy[2*node+1] , lazy[node]);
				apply_operation(lazy[2*node+2] , lazy[node]);
				clazy[2*node+1] = true;
				clazy[2*node+2] = true;
				
			}
		}
		lazy[node] = 0;
		clazy[node]=false;
	}
	
	void build( vll &arr ,  ll l , ll r , ll node){
		if(l == r){
			if(l < (ll)arr.size()){
				//set value;
				a[node] = arr[l];
			}
			return;
		}
		ll mid = (l+r)/2;
		build(arr , l , mid , 2*node+1 );
		build(arr , mid+1 , r , 2*node+2);
		a[node] = merge( a[2*node+1], a[2*node+2]);
	}
 
 
	void modify(ll l , ll r , ll v , ll node , ll lx , ll rx){
		if(clazy[node]){
			propagate(node , lx , rx);
		}
		if(lx > r || l > rx) return;
		if(lx >= l && rx <= r){
			//addition:lazy[node]+=v
			//assignment:lazy[node]=v;
			lazy[node]+=v;
			clazy[node] = true;
			propagate(node , lx , rx);
			return;
		}
		ll mid= (lx + rx)/2;
		modify(l , r , v , 2*node+1 , lx , mid);
		modify(l , r ,v , 2*node+2 , mid+1 , rx);
		a[node] = merge( a[2*node+1] , a[2*node+2]);
	}
 
	var get(ll i , ll node, ll lx , ll rx){
		if(clazy[node]){
			propagate(node , lx  , rx);
		}
		if(rx == lx){
			return a[node];
		}
 
		ll mid = (lx+rx)/2;
		ll res;
		if(i <= mid){
			return get(i , 2*node+1 , lx , mid);
		}else{
			return get(i , 2*node+2 , mid+1 , rx);
		}
	}
	
	void set(ll l , ll r , ll v  , ll node , ll pos ){
		
		if(clazy[node]){
			propagate(node , l , r);
		}
		if(l == r){
			//set value
			//addition:lazy[node]+=v
			//assignment:lazy[node]=v;
			clazy[node] = 1;
			lazy[node] += v;
			propagate(node , l , r);
			return;
		}
		ll mid = (l+r)/2;
		if( pos <= mid){
			set(l , mid , v , 2*node+1 , pos);
		}else{
			set(mid+1 , r , v , 2*node+2 , pos);
		}
		a[node]= merge(a[2*node+1], a[2*node+2]);
	}
	
	var calc(ll l , ll r , ll lx , ll rx , ll node){
		if(clazy[node]){
			propagate(node , lx , rx);
		}
		if(r < lx || l > rx){
			return INF;
		}
		if( l <= lx && r >= rx){
			return a[node];
		}
		ll mid = (lx+rx)/2;
		var sum1 = calc(l , r , lx , mid , 2*node+1 );
		var sum2 = calc(l , r , mid+1 , rx , 2*node+2);
		return merge(sum1 , sum2);
	}
	
	 void build( vll &arr ){
		build(arr , 0 , size-1 , 0);
	}

	var calc(ll l , ll r){
		var ans = calc(l , r , 0 , size-1 , 0);
		return ans;
	}
	
	void set(ll i , ll v){
		set(0 , size-1 , v, 0 , i);
	}
	
	void modify(ll l , ll r , ll v){
		modify(l , r ,v , 0 , 0 , size-1);
	}
 
	var get(ll i){
		return get(i , 0 , 0, size-1);
	}
	
	
 
	void prints(void){
		cout << size << endl;
		printv(a);
		printv(lazy);
		printv(clazy);
	}
 
};
