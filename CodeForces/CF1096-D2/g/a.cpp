/*
 * link: http://codeforces.com/contest/1096/problem/G
 * submits: 3
 * TT: 20
 * CT: 45
 * Level: 8.5
 * Category: ntt
 * Comment: Important. Actually, I thougth about ntt quite fast, but it cost me to imlement it in a way that doesn't give TLE. And what helped was to clean trailing zeroes from polynomials.
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

ll inv(ll b, ll M)
{
	ll u = 1, x = 0, s = b, t = M;
	while (s)
	{
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	return (x %= M) >= 0 ? x : x + M;
}

ll pow(ll a, ll b, ll M)
{
	ll x = 1;
	for (; b > 0; b >>= 1)
	{
		if (b & 1)
			x = (a * x) % M;
		a = (a * a) % M;
	}
	return x;
}

// fast modulo transform
//   (1) n = 2^k < 2^23
//   (2) only predetermined mod can be used
void fmt(vector<ll> &x, ll mod, int sign = +1)
{
	int n = x.size();
	ll h = pow(3, (mod - 1) / n, mod);
	if (sign < 0) h = inv(h, mod);
	for (int i = 0, j = 1; j < n - 1; ++j)
	{
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(x[i], x[j]);
	}
	for (int m = 1; m < n; m *= 2)
	{
		ll w = 1, wk = pow(h, n / (2 * m), mod);
		for (int i = 0; i < m; ++i)
		{
			for (int j = i; j < n; j += 2 * m)
			{
				ll u = x[j], d = x[j + m] * w % mod;
				if ((x[j] = u + d) >= mod)
					x[j] -= mod;
				if ((x[j + m] = u - d) < 0)
					x[j + m] += mod;
			}
			w = w * wk % mod;
		}
	}
	if (sign < 0)
	{
		ll n_inv = inv(n, mod);
		for (auto &a : x)
			a = (a * n_inv) % mod;
	}
}

typedef vector<ll> poly;
void clean(poly& x) // this is very important
{
  while(sz(x) && x.back() == 0)
    x.pop_back();
}

// convolution via fast modulo transform
vector<ll> conv(vector<ll> x, vector<ll> y, bool eq = false, ll mod= 998244353)
{
  int need = sz(x) + sz(y) - 1;
  while(need & (need-1)) ++need;
  x.resize(need, 0);
  y.resize(need, 0);
	fmt(x, mod, +1);
	if(eq) y = x; else fmt(y, mod, +1);
	for (int i = 0; i < (int)x.size(); ++i)
		x[i] = (x[i] * y[i]) % mod;
	fmt(x, mod, -1);
  clean(x);
	return x;
}



const ll mod = 998244353;

poly base(10, 0);
poly eye{1};

poly naive(poly& x, poly& y)
{
  int d1 = sz(x), d2 = sz(y);
  int need = sz(x) + sz(y) - 1;
  while(need & (need - 1)) ++need;
  poly res(need, 0);
  for(int i = 0; i < d1; ++i)
    for(int j = 0; j < d2; ++j )
      res[i + j] = (res[i + j] + x[i] * y[j]) % mod;
      
  clean(x);
  return res;
}
  
poly qpow(poly& b, int e)
{
  //~ cerr << e << endl;
  if(e == 0) return eye;
  if(e == 1) return b;
  if(e & 1)
  {
    poly tmp = qpow(b, e-1);
    return naive(tmp, b);
  }
  poly tmp = qpow(b, e >> 1);
  return conv(tmp, tmp, true);
}


int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, k;
  cin >> n >> k;
    
  
  for(int i = 1; i <= k; i++)
  {
    int x; cin >> x;
    base[x]++;
  }
  
  poly ans = qpow(base, n / 2);
  
  //~ cerr << "===\n";
  ll res = 0;
  for(ll i: ans)
    res = (res + i * i % mod) % mod;
  cout << res << endl;
  
  return 0;
}
