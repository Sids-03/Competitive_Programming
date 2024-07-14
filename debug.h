#include<iostream>
using namespace std;

inline void __print(int x) {cout << x;}
inline void __print(long x) {cout << x;}
inline void __print(long long x) {cout << x;}
inline void __print(unsigned x) {cout << x;}
inline void __print(unsigned long x) {cout << x;}
inline void __print(unsigned long long x) {cout << x;}
inline void __print(float x) {cout << x;}
inline void __print(double x) {cout << x;}
inline void __print(long double x) {cout << x;}
inline void __print(char x) {cout << '\'' << x << '\'';}
inline void __print(const char *x) {cout << '\"' << x << '\"';}
inline void __print(const string &x) {cout << '\"' << x << '\"';}
inline void __print(bool x) {cout << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cout << '{'; __print(x.first); cout << ','; __print(x.second); cout << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cout << '{'; for (auto &i: x) cout << (f++ ? "," : ""), __print(i); cout << "}";}
inline void _print() {cout << "]"<<endl;}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cout << ", "; _print(v...);}
#define dbg(x...) cout << #x << " = ["; _print(x)
template<typename T,typename T1>T amax(T &a,T1 b){if(b>a)a=b;return a;}
template<typename T,typename T1>T amin(T &a,T1 b){if(b<a)a=b;return a;}
