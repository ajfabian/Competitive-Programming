#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef double d;
typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INIT ios_base::sync_with_stdio(false); cin.tie(0),cout.tie(0)
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
#define debug(_fmt,...) fprintf(stderr,"("#__VA_ARGS__ ") = (" _fmt")\n",__VA_ARGS__)

const d eps = 1e-12;

inline int sign(d x) { return x < -eps ? -1 : x > eps; }
inline int realcmp(d x, d y) { return sign(x-y); }
template<typename T> void na(vector<T>& a, int n) {a = vector<T>(n);for(T& i: a) cin >> i;}
template<typename T> void pv(vector<T>& a) { for(T& i: a) cerr << i << ' '; cerr << endl; }
template<typename T> vector<T> shrink(vector<T>& x) { vector<T> vals = x; sort(all(vals)); unique(vals); for(T& i: x) i = ub(all(vals), i) - vals.begin(); return vals; }

ll qry(ll x)
{
  cout << "? " << x << endl;
  ll ret;
  cin >>ret;
  return ret;
}

const ll mod = 1e6+3;

int qpow(ll b, ll e)
{
  if(e == 0ll) return 1ll;
  if(e == 1ll) return b;
  if(e & 1ll) return b * qpow(b, e-1) % mod;
  ll tmp = qpow(b, e >> 1);
  return tmp * tmp % mod;
}

ll invMod(ll x)
{
  return qpow(x, mod - 2);
}

ll gauss(vector<vector<ll>> a, vector<ll> &ans)
{
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; ++col)
	{
		int sel = row;
		for (int i = row; i < n; ++i)
			if (a[i][col] > a[sel][col])
				sel = i;
		if (a[sel][col] == 0)
			continue;
		for (int i = col; i <= m; ++i)
			swap(a[sel][i], a[row][i]);
		where[col] = row;

		for (int i = 0; i < n; ++i)
			if (i != row)
			{
				ll c = a[i][col] * invMod(a[row][col]) % mod;
				for (int j = col; j <= m; ++j)
					a[i][j] = (a[i][j] + mod - a[row][j] * c % mod) % mod;
			}

		++row;
	}

	ans.assign(m, 0);

	for (int i = 0; i < m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] * invMod(a[where[i]][i]) % mod;

	for (int i = 0; i < n; ++i)
	{
		ll sum = 0;
		for (int j = 0; j < m; ++j)
			sum = (sum + ans[j] * a[i][j] % mod) % mod;
		if (sum != a[i][m])
			return 0; // none
	}

	for (int i = 0; i < m; ++i)
		if (where[i] == -1)
			return -1; // inf
	return 1; // only one
}

ll eval(vector<ll> g, ll x)
{
  ll res = 0;
  reverse(all(g));
  for(ll i: g) res = (res * x % mod + i) % mod;
  return res;
}

main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  vector<vector<ll>> a(12, vector<ll>(12));
  for(int i=0;i<12;++i)
  {
    a[i][0] = 1;
    for(int j=1;j<11;++j)
      a[i][j] = a[i][j-1] * i % mod;
    a[i][11] = qry(i);
  }
  
  vector<ll> g;
  gauss(a, g);
  
  //~ pv(g);
  //~ return 0;
  
  for(int i=0;i<mod;++i)
  {
    ll tmp;
    if((tmp = eval(g, i)) == 0ll)
    {
      //~ cerr << "\nwith i = " << i << endl;
      //~ pv(g);
      //~ cerr << "eval = "  << eval(g, i) << " but " << tmp << endl;
      cout << "! " << i << endl;
      return 0;
    }
  }
  cout << "! -1" << endl;
  //~ cerr << "! -1" << endl;
}

#warning you will remember this, overflow is there, though you might not see it ...

