/*
 * MIS for 40 vertexes :O
 * 
 * 1. Divide the vertexes into two groups.
 * 2. For every subset of the first part compute the MIS contained in it (with dp).
 * 3. For every independent subset of the second part check the max indep
 *  set of the first part that can be formed with vertexes not adjacents to current subset of second part.
 * */

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 21;

int dp[1 << N];

map<string, int> _id;
int id(string& s)
{
  if(_id.count(s)) return _id[s];
  int tmp = _id.size();
  return _id[s] = tmp;
}

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  
  if(m == 1)
  {
    cout << "1\n";
    return 0;
  }
  
  char last=-1;
  vector<set<int>> brust;
  set<int> cur;
  for(int i=1;i<=n;++i)
  {
    cin >> last;
    if(last == '1')
    {
      if(cur.empty()) continue;
      brust.push_back(cur);
      cur.clear();
    }else
    {
      string s;
      cin >> s;
      int pid = id(s);
      cur.insert(pid);
    }
  }
  brust.push_back(cur);
  cur.clear();
  
  vector<ll> adj(m);
  
  for(auto& s: brust)
    for(int i: s) for(int j: s) if(i != j)
      adj[i] |= 1ll << j;
  
  int l = m / 2; // [0 .. l)
  int h = m - l; // [l .. l+h=m)
  ll fhalf = (1ll << l) - 1;
  ll shalf = (1ll << h) - 1; shalf <<= l;
  cerr << l << ' ' << h << endl;
  assert((fhalf & shalf) == 0 && (fhalf | shalf) == (1ll << m) - 1);
  
  for(int i=0;i<l;++i)
    dp[1 << i] = 1;
  
  int ans = 0;
  for(int s=1;s<(1 << l);++s)
  {
    int p = __builtin_ctz(s);
    dp[s] = max({dp[s], dp[s-(1 << p)], dp[s - (s & ((adj[p] & fhalf) | 1 << p))] + 1});
    ans = max(ans, dp[s]);
  }
  cerr << "first part: " << ans << endl;
  
  for(int s=1;s<(1 << h);++s)
  {
    //~ cerr << "===== " << s << " =====\n";
    bool isindep = true;
    int allAdj = 0;
    for(int i=0;isindep && i<h;++i)
    {
      if(s>>i&1)
      {
        if(adj[i+l] >> l & s )
         isindep =false;
        allAdj |= adj[i+l] & fhalf;
      }
    }
    //~ cerr << "isindep: " << isindep << ' ' << fhalf - allAdj << endl;
    if(!isindep) continue;
    
    int sz;
    ans = max(ans, sz = __builtin_popcount(s));
    ans = max(ans, sz + dp[fhalf - allAdj]);
    //~ cerr << ans << endl;
  }
  cout << ans << endl;
 
  return 0;
}
