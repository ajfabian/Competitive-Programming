#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll M;

ll sum(ll a, ll b)
{
  return (a + M + b) % M;
}

ll mul(ll a, ll b)
{
  return a * b % M;
}

int main()
{
  ll n, k, a, b;
  cin >> n >> k >> a >> b;
  
  M = n * k;
  ll x = 1e18, y = 0;
  vector<ll> s{sum(0, a), sum(0, -a)};
  //~ cerr << "S = " << s[0] << ' ' << s[1] << endl;
  for(int i=0;i<n;++i)
  {
    vector<ll> t{sum(i * k, b), sum(i * k, -b)};
    //~ cerr << "T = " << t[0] << ' ' << t[1] << endl;
    for(ll s0: s) for(ll t0: t)
    {
      ll l = sum(t0, -s0);
      //~ cerr << "l(" << s0 << ", " << t0 << ") = " << l << endl;
      x = min(x, M / __gcd(M, l));
      y = max(y, M / __gcd(M, l));
    }
  }
  
  cout << x << ' ' << y << endl;
  
  return 0;
}
