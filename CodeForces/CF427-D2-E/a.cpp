/*
 * Idea: Ternary Search.
 * 
 * the minimum cost function for the answer is unimodal, and so we can
 * do a ternary search to find out the minimum.
 * 
 * CF427-D2-E
 * TT: 5
 * CT: 15
 * lev: 6
 * Category: ternary search + greedy
 * Comment: Interesting.
 * 
 * */

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

  int n, m;
ll eval(vector<ll>& x, ll p)
{
  ll res = 0;
  
  int cur = 0;
  while(cur < (int)x.size() && x[cur] < p)
  {
    res += p - x[cur];
    cur += m;
  }
  
  cur = x.size() - 1;
  while(cur >= 0 && x[cur] > p)
  {
    res += x[cur] - p;
    cur -= m;
  }
  
  return res;
}

int main()
{
  scanf("%d%d", &n, &m);
  vector<ll> x(n);
  for(ll& i: x)
    scanf("%lld", &i);
  
  ll ans = 1e18;
  int lo = *min_element(x.begin(), x.end());
  int hi = *max_element(x.begin(), x.end());

  while(hi - lo > 2)
  {
    int d = (hi - lo) / 3;
    int m1 = lo + d; int m2 = hi - d;

    ll f1 = eval(x, m1); ll f2 = eval(x, m2);

    if(f1 < f2) hi = m2;
    else
    {
      ans = min(ans, f1);
      lo = m1;
    }
  }
  while(lo <= hi)
    ans = min(ans, eval(x, lo++));
  
  cout << 2 * ans << endl;
  
  return 0;
}
