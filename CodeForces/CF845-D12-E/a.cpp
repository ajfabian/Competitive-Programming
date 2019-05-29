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

struct Space
{
  ll x0, y0, x1, y1;
  Space(ll x0, ll y0, ll x1, ll y1)
    : x0(x0), y0(y0), x1(x1), y1(y1){}
  
  bool operator< (const Space& s) const
  {
    if(x0 != s.x0) return x0 < s.x0;
    if(y0 != s.y0) return y0 < s.y0;
    if(x1 != s.x1) return x1 < s.x1;
    return y1 < s.y1;
  }
  
  Space operator% (Space s)
  {
    //~ cerr << "doing ";
    //~ print();
    //~ cerr << "with ";
    //~ s.print();
    ll mnx, mny, mxx, mxy;
    mnx = max(x0, s.x0);
    mxx = min(x1, s.x1);
    mny = max(y0, s.y0);
    mxy = min(y1, s.y1);
    return Space(mnx, mny, mxx, mxy);
  }
  
  bool isDegenerate()
  {
    return x0 >= x1 || y0 >= y1;
  }
  
  void print()
  {
    cerr << "[" << x0 << ", " << y0 << ", " << x1 << ", " << y1 << "]\n";
  }
};

const ll inf = 1e10;

ll n, m;
vector<Space> canonical;

struct Event
{
  ll x, y0, y1;
  int t; // 0 - segment starts, 1 - query pt, 2 - segment ends
  Event(ll x=0, ll y0=0, ll y1=0, int t=0)
    : x(x), y0(y0), y1(y1), t(t){}
  bool operator <(const Event& e)const
  {
    if(x != e.x) return x < e.x;
    if(t != e.t) return t < e.t;
    if(y0 != e.y0) return y0 < e.y0;
    return y1 < e.y1;
  }
  
  bool operator== (const Event& e)const
  {
    return x == e.x && y0 == e.y0 && y1 == e.y1 && t == e.t;
  }
  
  void print()
  {
    if(t == 0) cerr << "segment starts: ";
    if(t == 1) cerr << "query pt: ";
    if(t == 2) cerr << "segment ends: ";
    debug("%lld %lld %lld", x, y0, y1);
  }
};

const int mr[]{0,-1,-1,-1,0,0,1,1,1},
          mc[]{0,-1,0,1,-1,1,-1,0,1};

bool can(ll t)
{
  vector<Space> now = canonical;
  for(Space& s: now)
  {
    s.x0 -= t; s.x0 = max(s.x0, 1ll);
    s.y0 -= t; s.y0 = max(s.y0, 1ll);
    s.x1 += t; s.x1 = min(s.x1, n);
    s.y1 += t; s.y1 = min(s.y1, m);
    //~ s.print();
  }
  
  now.eb(1,1,n,m);
  
  vector<Event> events;
  events.eb(1,1,1,1);
  events.eb(1,m,m,1);
  events.eb(n,1,1,1);
  events.eb(n,m,m,1);
  
  for(int i=0;i<sz(now)-1;++i)
  {
    events.eb(now[i].x0, now[i].y0, now[i].y1, 0);
    events.eb(now[i].x1, now[i].y0, now[i].y1, 2);
    for(int j=i+1;j<sz(now);++j)
    {
      Space tmp = now[j];
      tmp.x0 -= 1;
      tmp.y0 -= 1;
      tmp.x1 += 1;
      tmp.y1 += 1;
      Space inter = now[i] % tmp;
      
      if(inter.isDegenerate()) continue;
      
      vector<pll> I;
      I.eb(inter.x0,inter.y0);
      I.eb(inter.x0,inter.y1);
      I.eb(inter.x1,inter.y0);
      I.eb(inter.x1,inter.y1);
      for(pii h: I)
      {
        int r = h.fr;
        int c = h.sc;
        for(int k=0;k<9;++k)
        {
          int nr = r + mr[k];
          int nc = c + mc[k];
          if(nr > n || nr < 1 || nc > m || nc < 1) continue;
          events.eb(nr,nc,nc,1);
        }
      }      
    }
  }
  
  sort(all(events));
  unique(events);
  multiset<pll> s;
  ll mnx=inf, mny=inf, mxx=-inf, mxy=-inf;
  for(Event& e: events)
  {
    //~ e.print();
    if(e.t == 0)
    {
      s.ins(mp(e.y0, e.y1));
    }else if(e.t == 2)
    {
      s.ers(s.find(mp(e.y0, e.y1)));
    }else
    {
      if(s.empty()) continue;
      
      pll cur = mp(e.y0, e.y1);
      bool outside = true;
      auto it = s.lb(cur);
      if(it != s.end())
        if(it->fr <= cur.fr && cur.fr <= it->sc)
        {
          outside = false;
          //~ cerr << "******** outside1: " << e.x << ' ' << cur.fr << endl;
        }
      if(it != s.begin())it--;
      if(it != s.end())
        if(it->fr <= cur.fr && cur.fr <= it->sc)
        {
          outside = false;
          //~ cerr << "******** outside2: " << e.x << ' ' << cur.fr << endl;
        }
      if(outside)
      {
        mnx = min(mnx, e.x);
        mxx = max(mxx, e.x);
        mny = min(mny, cur.fr);
        mxy = max(mxy, cur.fr);
      }
    }
  }
  //~ debug("%lld %lld %lld %lld %lld", t, mnx, mny, mxx, mxy);
  if(labs(mnx) >= inf || labs(mxx) >= inf || labs(mny) >= inf || labs(mxy) >= inf)
    return true;
  //~ debug("%lld %lld %lld %lld %lld", t, mnx, mny, mxx, mxy);
  ll needTime = max( (mxx - mnx + 1) / 2, (mxy - mny + 1) / 2 );
  //~ cerr << needTime << endl;
  return needTime <= t;
}

ll bs(ll lo, ll hi)
{
  if(hi - lo <= 1)
  {
    if(can(lo)) return lo;
    if(can(lo+1)) return lo + 1;
    return lo + 2; // this shouldn't happend.
  }
  ll m = (lo + hi) >> 1;
  if(can(m)) return bs(lo, m);
  return bs(m+1, hi);
}

int main()
{
  #ifdef OJUDGE
    //freopen("in","r",stdin);
  #endif
  //~ INIT;
  
  cin >> n >> m;
  
  int k;
  cin >> k;
  for(int i=1;i<=k;++i)
  {
    int x, y;
    cin >> x >> y;
    canonical.eb(x,y,x,y);
  }
  
  //~ cout << can(3) << endl ;
  cout << bs(0, 1000000000) << endl;
  
  return 0;
}
