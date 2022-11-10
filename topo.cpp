ll n;
vector<vll> adj;
vll vis;
vll ans;
bool check_cycle;
 
void dfs(ll node){
	vis[node] = 1;
	for(auto it: adj[node]){
		if(vis[it] == 1){
			check_cycle = true;
			return;
		}
		if(vis[it] == 0){
			dfs(it);
		}
	}
	ans.pb(node);
	vis[node] = 2;
}

void topo(){
	vis.assign(n , 0);
	ans.clear();
	for(int i =0  ;i < n ; i ++){
		if(!vis[i]){
			dfs(i);
		}
	}
	reverse(all(ans));
}
 
 
