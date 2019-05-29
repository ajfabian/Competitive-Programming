/*
 * Idea: Binary search in the time needed to cover the whole city;
 * 
 * Intuitive proof: If for time, let's say t, the city might be set on fire
 * then for bigger time the city can too be set on fire;
 * 
 * To check if for a fixed time t the city can be set on fire we expand
 * all given ignition points by t (as it's the time spent) to form a
 * square. Now we have k squares.
 * -> Key Observation: Let mnX (mxX), mnY (mxY) be the minimum
 * (maximum) x and y among all points not covered by any of the squares
 * formed. Then minimum time needed to cover all uncover points is:
 *  Max{ (mxX - mnX + 1) / 2, (mxX - mnX + 1) / 2 }
 * This is because the extra ignition point needs necessarily to cover
 * the these uncovered points that have the minimum (maximum) x and y, 
 * and it's sufficient to put the extra point in the coordinates:
 *  {(mnX + mxX) / 2, (mnY + mxY) / 2}
 * 
 * From this all that we need is to find these values of mnX, mxX, mnY, mxY.
 * */

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
#define fr first
#define sc second
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define ins insert
#define ers erase
#define lb lower_bound
#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
#define unique(x) (x).resize(unique(all(x)) - (x).begin())
#define debug(_fmt,...) \
fprintf(stderr,"("#__VA_ARGS__ ") = (" _fmt")\n",__VA_ARGS__)

const int inf = 2e9;

struct Square
{
  int x0, y0, x1, y1;
  Square(int x0, int y0, int x1, int y1)
  : x0(x0), y0(y0), x1(x1), y1(y1){}
};

int n, m;
vector<Square> base;

bool can(int t)
{
  vector<Square> now = base;
  for(auto& s: now)
  {
    s.x0 = max(1, s.x0 - t);
    s.y0 = max(1, s.y0 - t);
    s.x1 = min(n, s.x1 + t);
    s.y1 = min(m, s.y1 + t);
  }
  
  vector<int> xs{1,n}, ys{1,m};
  for(int i=0;i<sz(now);++i)
  {
    xs.pb(max(1, now[i].x0-1));
    xs.pb(min(n, now[i].x1+1));
    ys.pb(max(1, now[i].y0-1));
    ys.pb(min(m, now[i].y1+1));
  }
  
  sort(all(xs)); unique(xs);
  sort(all(ys)); unique(ys);
  
  int mnx=inf, mxx=-inf;
  for(int x: xs)
  {
    vector<pii> ry;
    for(auto& s: now)
    {
      if(s.x0 <= x && x <= s.x1)
        ry.eb(s.y0, s.y1);
    }
    sort(all(ry));
    int last=0;
    bool ok=true;
    //~ cerr << "For: " << x << endl;
    for(pii p: ry)
    {
      //~ cerr << p.fr << ' ' << p.sc << endl;
      if(last+1 < p.fr)
      {
        ok=false;
        break;
      }else last = p.sc;
    }
    if(last != m || !ok) mnx = min(mnx, x), mxx = max(mxx, x);
  }
  
  int mny=inf, mxy=-inf;
  for(int y: ys)
  {
    vector<pii> rx;
    for(auto& s: now)
    {
      if(s.y0 <= y && y <= s.y1)
        rx.eb(s.x0, s.x1);
    }
    sort(all(rx));
    int last=0;
    bool ok=true;
    for(pii p: rx)
    {
      if(last+1 < p.fr)
      {
        ok=false;
        break;
      }else last = p.sc;
    }
    if(last != n || !ok) mny = min(mny, y), mxy = max(mxy, y);
  }
  //~ debug("%d %d %d %d %d", t, mnx, mny, mxx, mxy);
  if(labs(mnx) >= inf || labs(mny) >= inf || labs(mxx) >= inf || labs(mxy) >= inf)
    return true;
  int needTime = max((mxx - mnx + 1) / 2, (mxy - mny + 1) / 2);
  return needTime <= t;
}

int bs(int lo, int hi)
{
  if(hi - lo <= 1)
  {
    if(can(lo)) return lo;
    if(can(lo + 1)) return lo+1;
    return lo + 2;
  }
  int m = (lo + hi) / 2;
  if(can(m)) return bs(lo, m);
  return bs(m+1,hi);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  cin >> n >> m;
  int k;
  cin >> k;
  for(int i=1;i<=k;++i)
  {
    int x, y;
    cin >> x >> y;
    base.eb(x,y,x,y);
  }
  
  //~ cout << can(1e5) << endl;
  cout << bs(0, 1000000000) << endl;
  
  return 0;
}
