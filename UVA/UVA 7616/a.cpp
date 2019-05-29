/*
 * Idea: Use Hashes.
 * 
 * for every node hash every posuble subset of its adjacency list with
 * size s-1, adding it to this hash. Let's count the number of times
 * a hash occurs, if it occurs s times then these nodes are a clique.
 * 
 * // It's giving me TLE.
 * */

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N = 111;

vector<int> g[N];

void clean(int n)
{
  for(int i=0;i<n;++i)
    g[i].clear();
}

const ull BASE = 107;

ull powe[N];

int main()
{
  powe[0] = 1;
  for(int i=1;i<N;++i)
    powe[i] = powe[i-1] * BASE;
  
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for(int i=1;i<=m;++i)
    {
      int u, v;
      scanf("%d%d", &u, &v);
      -- u, -- v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    unordered_map<ull, int> h(1 << 15);
    for(int i=0;i<n;++i)
    {
      //~ sort(g[i].begin(), g[i].end());
      if((int)g[i].size() < s-1) continue;
      vector<int> mk(g[i].size(), 0);
      for(int j = 0; j < s-1; ++ j)
        mk[(int)g[i].size() - j - 1] = 1;
      //~ sort(mk.begin(), mk.end());
      do
      {
        ull curHash = powe[i];
        for(int j = 0; j < (int)g[i].size();++j)
          if(mk[j]) curHash += powe[g[i][j]];
        h[curHash]++;
      }while(next_permutation(mk.begin(), mk.end()));
    }
    
    int ans = 0;
    for(auto it: h)
    {
      if(it.second == s) ++ans;
    }
    printf("%d\n", ans);
    clean(n);
  }
  return 0;
}
