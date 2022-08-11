
struct data{
  //data as per needed in question (data present in the node of the segment tree)
	ll x;
};

struct seg_tree{

	ll size;
	vector<data> a;
  
  //data invariant = (like for minimum , we take INF , for addition 0 ,etc)

	void init(ll n){
		size = 1;
		while(size < n) size*=2;
		a.resize(2*size);
	}

	data merge(data a , data b){
		// how the parents of the nodes are calculated
    //for adding  , data c = data a+ data b;
	}

	void build( vll &arr ,  ll l , ll r , ll node){
		if(l == r){
			if(l < (ll)arr.size()){
        // leaf node case;
        //data leaf = (data in leaf);
				//a[node] = leaf;
			}
			return;
		}
		ll mid = (l+r)/2;
		build(arr , l , mid , 2*node+1 );
		build(arr , mid+1 , r , 2*node+2);
		a[node] = merge(a[2*node+1], a[2*node+2]);
	}

	void build( vll &arr ){
		build(arr , 0 , size-1 , 0);
	}


	void set(ll l , ll r , ll v  , ll node , ll i ){
		if(l == r){
      //leaf node case
      // data leaf = (data in leaf);
			//a[node] = leaf;
			return;
		}
		ll mid = (l+r)/2;
		if( i <= mid){
			set(l , mid , v , 2*node+1 , i);
		}else{
			set(mid+1 , r , v , 2*node+2 , i);
		}
		a[node] = merge(a[2*node+1], a[2*node+2]);
	}

	void set(ll i , ll v){
		set(0 , size-1 , v, 0 , i);
	}

	data calc(ll l , ll r , ll lx , ll rx , ll node){
		if(r < lx || l > rx){
			return invariant;
		}
		if( l <= lx && r >= rx){
			return a[node];
		}
		ll mid = (lx+rx)/2;
		data sum1 = calc(l , r , lx , mid , 2*node+1 );
		data sum2 = calc(l , r , mid+1 , rx , 2*node+2);
		return merge(sum1,sum2);
	}

	data calc(ll l , ll r){
		data ans = calc(l , r-1 , 0 , size-1 , 0);
		return ans;
	}
	// void prints(void){
	// 	printv(a);
	// }
};
