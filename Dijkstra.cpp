  ll n;
  vector<vector<pll>> adj;
  vll d , parent;
  
  void dijkstra(ll source){
  	parent.assign(101,0);
  	d.assign(101 , INF);
    d[source] =0;
      priority_queue<pll> pq;
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
