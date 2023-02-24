  ll n;
  vector<vector<pll>> adj;
  vll d , parent;
  
  void dijkstra(ll source){
  	parent.assign(n+1,0);
  	d.assign(n+1 , INF);
    d[source] =0;
      priority_queue<pll, vector<pll>, greater<pll>> pq;
      pq.push({0,source});
       while(!pq.empty()){
           ll vert = pq.top().second;
           ll dist = pq.top().first;
           pq.pop();
           if(dist > d[vert])continue;
           for(auto it:adj[vert]){
               if(d[vert]+it.second < d[it.first]){
                  d[it.first] = d[vert] + it.second;
                   pq.push({d[it.first] , it.first});
                   parent[it.first] = vert;
              }
          }
      }
  }
