/*Idea: Analyze each group of edges with the same value in
 * increasing order (just like kruskal's algorithm) and for
 * every group:
 * 1. find the connected components of compacted nodes.
 * 2. for each connected component find the number of Spanning trees
 *  using Kirchoff's theorem. And multiply the answer with that.
 * 3. join the connected components kruskal's style.
 * Note: 31011 is not prime, so: solve the problem for each of its (two)
 *  prime factors and the at the end recover the answer module 31011.
 * Q: Can it be done without having to decompose it in its factors?.
 * */

#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INIT ios_base::sync_with_stdio(false);\
             cin.tie(0),cout.tie()
#define endl '\n'
#define fr first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define ers erase
#define sz(c) ((int)(c).size())
#define all(x) (x).begin(),(x).end()
#define unique(x) (x).resize(unique(all(x))-(x).begin())
#define debug(_fmt,...) \
fprintf(stderr,"("#__VA_ARGS__ ") = (" _fmt")\n",__VA_ARGS__)

template<class T>
void na(vector<T>& a, int n)
{a = vector<T>(n);for(T& i: a) cin >> i;}
template<class T>
void printVector(vector<T>& a)
{for(T& i: a) cout << i << ' '; cout << endl;}
template<class T>
vector<T> shrink(vector<T>& x)
{
  vector<T> vals = x;
  sort(all(vals)); unique(vals);
  for(T& i: x) i = ub(all(vals), i) - vals.begin();
  return vals;
}

typedef vector<ll> vec;
typedef vector<vec> mat;
const ll M = 31011ll;
const ll mod1 = 3;
const ll mod2 = 10337;

struct UF
{
	int n;
	vector<int> root, r;
	UF(int n)
	:root(n+1),r(n+1,1)
	{
		for(int i=1;i<=n;++i)root[i]=i;
	}
	
	int fs(int u)
	{
		if(u != root[u]) return root[u] = fs(root[u]);
    return u;
	}
	bool js(int u,int v)
	{
		u=fs(u),v=fs(v);
		if(u==v)return false;
		if(r[u]<r[v])
			swap(u,v);
		
		r[u]+=r[v];
		root[v]=u;
		return true;
	}
};

struct edge
{
  int u, v;
  ll c;
  edge(int u, int v, ll c=0)
    : u(u), v(v), c(c){}
  bool operator< (const edge& e)const
  {
    return c < e.c;
  }
};

ll modPow(ll b, ll e, ll mod)
{
  if(e == 0) return 1;
  if(e == 1) return b;
  if(e&1) return b * modPow(b, e - 1, mod) % mod;
  ll tmp = modPow(b, e >> 1, mod);
  return tmp * tmp % mod;
}

ll invMod(ll x, ll mod)
{
  return modPow(x, mod - 2, mod);
}

ll det(mat A, ll mod)
{
  for(int i=0;i<sz(A);++i)
  {
    for(int j=0;j<sz(A);++j)
    {
      if(i == j) A[i][j] %= mod;
      else A[i][j] = (mod - A[i][j] % mod)%mod;
    }
  }
  
	ll D = 1;
	for (int i = 0; i < (int)A.size(); ++i)
	{
		int p = i;
		for (int j = i + 1; j < (int)A.size(); ++j)
			if (labs(A[p][i]) < labs(A[j][i]))
				p = j;
		swap(A[p], A[i]);
		for (int j = i + 1; j < (int)A.size(); ++j)
			for (int k = i + 1; k < (int)A.size(); ++k)
				A[j][k] = (A[j][k] + mod - (A[i][k] * A[j][i] % mod) * invMod(A[i][i], mod) % mod) % mod;
		D = D * A[i][i] % mod;
		if (p != i)
			D = (mod - D) % mod;
	}
  
	return D;
}

const int N = 555;

int n, m;
int L[N][N], id[N];
bool mk[N], used[N];

void dfs(int u, vector<int>& seen)
{
  mk[u] = true;
  id[u] = sz(seen);
  seen.pb(u);
  for(int i=1;i<=n;++i)
    if(L[u][i] && !mk[i]) dfs(i, seen); 
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  cin >> n >> m;
  
  vector<edge> g;
  for(int i=1;i<=m;++i)
  {
    int u, v;
    ll c;
    cin >> u >> v >> c;
    g.eb(u, v, c);
  }
  sort(all(g));
  
  UF uf(n);
  ll ans3 = 1, ans10337 = 1;
  for(int i=0,j;i<m;i=j)
  {
    j = i;
    memset(L, 0, sizeof L);
    memset(used, 0, sizeof used);
    while(j < m && g[j].c == g[i].c)
    {
      int u = uf.fs(g[j].u);
      int v = uf.fs(g[j].v);
      if(u != v)
      {
        ++L[u][v];
        ++L[v][u];
        used[u] = used[v] = true;
      }
      ++j;
    }
    
    memset(id, 0, sizeof id);
    memset(mk, 0, sizeof mk);
    for(int k=1;k<=n;++k)
    {
      if(!used[k] || mk[k]) continue;
      vector<int> seen;
      dfs(k, seen);
      
      mat a(sz(seen), vec(sz(seen), 0));
      for(int u: seen)
      {
        for(int v: seen)
        {
          //~ cout <<  u <<' ' << id[u] << ' ' << v << ' ' << id[v] << ' ' << L[u][v] << '\n';
          if(u!=v)a[id[u]][id[v]] = L[u][v];
          a[id[u]][id[u]] += L[u][v];
        }
        //~ cout << endl;
      }
      a.pop_back();
      for(auto& r: a)
        r.pop_back();
      //~ cout << "Matriz: \n";
      //~ for(auto r: a)
        //~ printVector(r);
        
      ans3 = ans3 * det(a, mod1) % mod1;
      ans10337 = ans10337 * det(a, mod2) % mod2;
    }
    
    for(int k=i;k<j;++k)
      uf.js(g[k].u, g[k].v);
  }
  
  cout << ((ans3*20674)%M+(ans10337*10338)%M )%M << endl;
  
  return 0;
}
