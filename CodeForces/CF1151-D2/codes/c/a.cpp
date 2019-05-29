#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair

using pii = pair<int, int>;
using ll = unsigned long long;

const ll mod = 1e9+7;

ll sodd(ll n){n %= mod; return n * n % mod;}
ll sevn(ll n){n %= mod; return n * (n + 1) % mod;}

ll srodd(ll l, ll r){return (sodd(r) + mod - sodd(l-1)) % mod;}
ll srevn(ll l, ll r){return (sevn(r) + mod - sevn(l-1)) % mod;}

ll solve(ll n)
{
  ll p[2]{1, 1}, res = 0;
  int cur = 1;
  for(ll sz = 1, pos = 1;pos <= n;sz <<= 1, cur ^= 1)
  {
    ll d = min(n - pos + 1, sz);
    //~ cerr << pos << ' ' << d << endl;
    if(cur == 1) // advance odd
    {
      res = (res + srodd(p[1], p[1] + d - 1))%mod;
    }else // advance even
    {
      res = (res + srevn(p[0], p[0] + d - 1))%mod;
    }
    p[cur] += d;
    pos += d;
  }
  return res;
}

int main()
{
  ll l, r;
  cin >> l >> r;
  //~ for(int i=1;i<=10;++i)  cerr << solve(i) << endl;
  //~ cerr << solve(88005553535) << endl;
  //~ cerr << solve(99999999999) << endl;
  cout << (solve(r) + mod - solve(l-1)) % mod << endl;
  return 0;
}
