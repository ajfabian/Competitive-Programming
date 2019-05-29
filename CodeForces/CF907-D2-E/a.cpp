/*
 * Idea: Bitmask dp.
 * DP Transition:
 *  dp[curmask | adj[i]] = min(dp[curmask | adj[i]], dp[curmask] + 1)
 *    for all i in curmask.
 * 
 * What we want in the problem is to end up with a complete graph of
 * n vertexes. So sps our states are complete subgraphs (i.e. cliques)
 * of the final (wanted) graph, I ask how did we got it?
 * well we got a clique and then select one of its vertexes 'i' and then
 * joined all vertexes adjacent to 'i' forming a new bigger clique.
 * 
 * This is the optimal substructure of the dp:
 *  to get the full clique we first explore how can we obtain it from
 *  smaller cliques.
 * 
 * Corner Case: The whole graph is a Complete graph, in this case the 
 * answer is 0.
 * */

#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
#define fr first
#define sc second
#define pb push_back
#define sz(x) ((int)(x).size())

const int N = 23;

int adj[N];

int dp[1 << N];
pii pp[1 << N];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; ++ i)
  {
    int u, v;
    cin >> u >> v;
    -- u, -- v;
    adj[u] |= 1 << v;
    adj[v] |= 1 << u;
  }
  
  int full = (1 << n) - 1;
  bool iscomplete = true;
  for(int i = 0; i < n && iscomplete; ++ i)
    if((adj[i] | (1 << i)) != full)
      iscomplete = false;
  
  if(iscomplete)
    return !(cout << "0\n");
  
  memset(dp, 127, sizeof dp);
  for(int i=0;i<n;++i)
    dp[1 << i] = 0;
  
  int nn = (1 << n) - 1;
  
  for(int m = 1; m <= nn; ++m)
  {
    for(int s = 0; s < n; ++ s)
      if((m >> s) & 1)
      {
        if(dp[m | adj[s]] > dp[m] + 1)
        {
          dp[m | adj[s]] = min(dp[m] + 1, dp[m | adj[s]]);
          pp[m | adj[s]] = make_pair(s, m);
        }
      }
  }
  
  //~ cout << dp[nn] << endl;
  
  vector <int> ans;
  int cur = nn;
  while(pp[cur].sc)
  {
    //~ cerr << cur << endl;
    ans.pb(pp[cur].fr+1);
    cur = pp[cur].sc;
  }
  
  cout << sz(ans) << endl;
  for(int i: ans)
    cout << i << ' ';
    
  cout << endl;
  
  return 0;
}
