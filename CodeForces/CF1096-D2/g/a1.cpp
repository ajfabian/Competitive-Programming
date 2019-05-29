/*
 * Solved before...
 * This time the idea to find the nth power of a polynomial is:
 *  1. Transform it to point form using as many points as needed (if deegree
 *  of the polynomial is m then you will need at least m * n points).
 *  2. Elevate every element to nth power.
 *  3. Anti-transform the polinomial.
 * This way is a lot easier to implement, and don't need to clean.
 */

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

void clean(vector<ll>& x) // this shit is very important
{
  while(sz(x) && x.back() == 0)
    x.pop_back();
}

// convolution via fast modulo transform
vector<ll> conv(vector<ll> x, vector<ll> y, ll mod= 998244353)
{
	fmt(x, mod, +1);
	fmt(y, mod, +1);
	for (int i = 0; i < (int)x.size(); ++i)
		x[i] = (x[i] * y[i]) % mod;
	fmt(x, mod, -1);
  clean(x);
	return x;
}

const ll mod = 998244353;
int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  INIT;
  
  int n, k;
  cin >> n >> k;
  
  n >>= 1;
  
  vector<ll> p(1 << 20);
  for(int i = 1; i <= k; i++)
  {
    int x; cin >> x;
    ++p[x];
  }
  
  fmt(p, mod);
  for(ll& i: p)
    i = pow(i, n, mod);
  fmt(p, mod, -1);
  
  ll ans = 0; 
  for(ll i: p)
    ans = (ans + i * i % mod) % mod;
  cout << ans << endl;
  
  return 0;
}
