#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

struct PT
{
  ll x, y;
  PT(){}
  PT(ll x, ll y) : x(x) , y(y){}
  ll operator% (const PT& p) const {return x * p.y - y * p.x;}
  PT operator- (PT& p) {return PT(x - p.x, y - p.y);}
  bool operator< (const PT& p){return x != p.x ? x < p.x : y < p.y;}
  void deb(bool nl=false)
  {
    cerr << "[" << x << ", " << y << "]";
    if(nl) cerr << endl;
  }
};

int main()
{
  int n;
  scanf("%d", &n);
  
  vector<PT> pts;
  for(int i=0;i<n;++i)
  {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    pts.emplace_back(x, y - x * x);
  }
    
  #define sz(x) ((int)(x.size()))
  #define P1 sz(upHull)-1
  #define P0 sz(upHull)-2
  
  sort(pts.begin(), pts.end());
  deque<PT> upHull;
  for(auto& p: pts)
  {
    while(sz(upHull) > 1 && (upHull[P1] - upHull[P0]) % (p - upHull[P1]) >= 0)
      upHull.pop_back();
    upHull.push_back(p);
  }
  
  int ans = sz(upHull) - 1;
  if(sz(upHull) > 1 && upHull[0].x == upHull[1].x) -- ans;
  cout << ans << endl;
  
  return 0;
}
