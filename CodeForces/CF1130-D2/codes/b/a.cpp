#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

struct status
{
  int tair, x, y;
  ll ct;
  status(int tair, int x, int y, ll ct)
    : tair(tair), x(x), y(y), ct(ct){}
    
  bool operator<(const status& s)const
  {
    return ct > s.ct;
  }
};

int main()
{ 
  int n;
  scanf("%d", &n);
  vector<vector<int>> pos(n+1);
  for(int i=1;i<=2*n;++i)
  {
    int x;
    scanf("%d", &x);
    pos[x].push_back(i);
  }
  
  priority_queue<status> pq;
  pq.emplace(0, 1, 1, 0);
  map<pair<int,pair<int,int>>, bool> dist;
  
  ll ans = 1e18/3;
  while(!pq.empty())
  {
    status cur = pq.top();
    pq.pop();
    if(dist.count({cur.tair, {cur.x , cur.y }})) continue;
    dist[{cur.tair, {cur.x , cur.y }}] = cur.ct;
    if(cur.tair == n)
    {
      ans = min(ans, cur.ct);
      continue;
    }
    int nxt = cur.tair + 1;
    ll nct = cur.ct + abs(cur.x-pos[nxt][0]) + abs(cur.y-pos[nxt][1]);
    pq.emplace(nxt, pos[nxt][0], pos[nxt][1], nct);
    nct = cur.ct + abs(cur.x-pos[nxt][1]) + abs(cur.y-pos[nxt][0]);
    pq.emplace(nxt, pos[nxt][1], pos[nxt][0], nct);
  }
  
  cout << ans << endl;
  
  return 0;
}
