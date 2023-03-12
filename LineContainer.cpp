vector<pll> all_lines;

lld intersection(pll l1 , pll l2){
    return ((lld)l1.second - l2.second)/(l2.first-l1.first);
}

bool can_delete(pll l1 , pll l2 , pll l3){

    return intersection(l1 , l2) < intersection(l2 , l3); // min
    //return intersection(l1 , l2) > intersection(l2 , l3); // max
}

void add_line(ll k , ll b){
    pll nl = {k,b};
    while(all_lines.size() >= 2 && can_delete(all_lines[all_lines.size()-2] , all_lines.back() , nl)){
        all_lines.pop_back();
    }
    all_lines.pb(nl);
}

int n;

ll vall(int pos , ll x){
    return all_lines[pos].first*x + all_lines[pos].second;
}

ll compute_min(ll x){
    ll l = -1;
    ll r = all_lines.size()-1;
    while(r-l > 1){
        ll mid = (l+r)/2;
        // vall(mid , x) < vall(mid+1 , x) // max
        if(vall(mid , x) > vall(mid+1 , x)){ // min
            l = mid;
        }else{
            r = mid;
        }
    }
    return vall(r , x);
}


//https://codeforces.com/contest/1083/submission/196939458 (max cht)
