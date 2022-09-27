 
  ll n;
  vector<vector<pll>> adj;
  vll d , parent;
  
  
  void dijkstra(ll source){
       adj.resize(n+1);
       parent.resize(n+1);
       d.resize(n+1);
      priority_queue<pll> pq;
     pq.push({0,source});
       while(!pq.empty()){
           ll vert = pq.top().second;
           ll dist = pq.top().first;
           pq.pop();
           if(dist > d[vert])continue;
           for(auto it:adj[vert]){
               if(d[vert]+dist < d[it.first]){
                  d[it.first] = d[vert] + dist;
                   pq.push({d[it.first] , it.first});
                 parent[it.first] = vert;
              }
          }
      }
 
 
  }
