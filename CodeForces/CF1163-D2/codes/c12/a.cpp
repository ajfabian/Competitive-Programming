#pragma GCC optimize("Ofast")

#include <iostream>
//~ #include <cstdio>
//~ #include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
//~ #include <unordered_set>
//~ #include <unordered_map>
//~ #include <ctime>
//~ #include <cassert>
//~ #include <complex>
#include <string>
//~ #include <cstring>
//~ #include <chrono>
//~ #include <random>
//~ #include <queue>
//~ #include <bitset>
using namespace std;

typedef long double rl;
typedef long long int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const rl eps = 1e-12;

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

inline int sign(rl x){return x < -eps ? -1 : x > eps;}
inline int rlcmp(rl x, rl y){return sign(x-y);}
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


struct cmp
{
  cmp(){}
  bool operator()(const rl& a, const rl& b)const
  {
    return rlcmp(a, b) < 0;
  }
};

struct pt
{
	ll x, y;
};

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
	int n;
	scanf("%d", &n);
	
	vector<pt> P;
	for(int i=1;i<=n;++i)
	{
		pt p;
		scanf("%lld%lld", &p.x, &p.y);
		P.push_back(p);
	}
  
	map<rl, set<rl, cmp>, cmp> s;
	set<ll> x;
	set<ll> y;
	
	ll ans = 0, tot = 0;
	for(int i=0;i<sz(P);++i)
	{
		for(int j=i+1;j<sz(P);++j)
		{
			pt p1 = P[i], p2 = P[j];
			
			cerr << p1.x << ',' << p1.y << " <-> ";
			cerr << p2.x << ',' << p2.y << "\n";
			
			ll dx = p1.x - p2.x;
			ll dy = p1.y - p2.y;
			
			if(dx == 0)
			{
				if(x.find(p1.x) == x.end())
				{
					ans += tot - sz(x);
				
					x.ins(p1.x);
					++tot;
				}
				continue;
			}
			if(dy == 0)
			{	
				if(y.find(p1.y) == y.end())
				{
					ans += tot - sz(y);
				
					y.ins(p1.y);
					++tot;
				}
				continue;
			}
			
			rl m = dy / ((rl) dx);
			rl c0 = (rl) p1.y - m * p1.x;
			
			if(s[m].find(c0) == s[m].end())
			{
				ans += tot - sz(s[m]);
				s[m].ins(c0);
				++ tot;
			}
		}
	}
	
	cout << ans << endl;
  
  return 0;
}
//~ "you will remember this, overflow is there, though you might not see it ..."

