// by Siddhid Saha (2112010)


#include <bits/stdc++.h>
using namespace std;

#define INF 1e18
#define endl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define PI atan(1)*4
#define set_bits __builtin_popcountllO
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define vll vector<ll>
#define pll pair<ll,ll>
#define rvsort(a) sort(all(a),greater<int>())
#define read(a,n) for(int i = 0 ; i < n ; i ++){ cin >> a[i];}
#define printv(a) for(auto it: a){cout << it << " ";} cout << endl;
#define ms(arr, v) memset(arr, v, sizeof(arr))

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifndef ONLINE_JUDGE
#include "/Users/templates/debug.h"
#else
#define dbg(x...)
#endif
/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
void extendgcd(ll a, ll b, ll*v) {if (b == 0) {v[0] = 1; v[1] = 0; v[2] = a; return ;} extendgcd(b, a % b, v); ll x = v[1]; v[1] = v[0] - v[1] * (a / b); v[0] = x; return;} //pass an arry of size1 3
ll mminv(ll a, ll b) {ll arr[3]; extendgcd(a, b, arr); return arr[0];} //for non prime b
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}
void google(int t) {cout << "Case #" << t << ": ";}
vector<ll> sieve(int n) {int*arr = new int[n + 1](); vector<ll> vect; for (int i = 2; i <= n; i++)if (arr[i] == 0) {vect.push_back(i); for (int j = 2 * i; j <= n; j += i)arr[j] = 1;} return vect;}
ll phin(ll n) {ll number = n; if (n % 2 == 0) {number /= 2; while (n % 2 == 0) n /= 2;} for (ll i = 3; i <= sqrt(n); i += 2) {if (n % i == 0) {while (n % i == 0)n /= i; number = (number / i * (i - 1));}} if (n > 1)number = (number / n * (n - 1)) ; return number;} //O(sqrt(N))
ll uid(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
/*--------------------------------------------------------------------------------------------------------------------------*/
//const int mod = 1e9 + 7;
//const int mod = 998244353; 


void solve()
{

}

int main() {

ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);


ll t = 1;
// cin >> t;
for(int i = 1 ; i <= t ; i++){
//google(i);
solve();
}
return 0;
}







