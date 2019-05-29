#include <bits/stdc++.h>
using namespace std;

#define BASE 29
#define fr first
#define sc second
#define mp make_pair

typedef long long int ll;
typedef pair<ll, ll> pll;

const ll mod1=1e9+7;
const ll mod2=1e9+9;
inline int val(char x){return x-'a'+1;}

map<pll, int> odd, even;

int main()
{
  string str;
  cin >> str;
  int n = str.size();
  
  ll ans = 0;
  for(int i=0;i<n;++i)
  {
    {
      pll curhash(0, 0);
      for(int j=i,t=1;j<n;++j,++t)
      {
        curhash.fr = (curhash.fr * BASE % mod1 + val(str[j])) % mod1;
        curhash.sc = (curhash.sc * BASE % mod2 + val(str[j])) % mod2;
        if(odd.count(curhash)) ans += 2ll * odd[curhash] * t;
        if(even.count(curhash)) ans += 1ll * even[curhash] * (2ll * t - 1ll);
      }
    }
    { // update even
      pll curhash(0, 0);
      for(int j=i;~j;--j)
      {
        curhash.fr = (curhash.fr * BASE % mod1 + val(str[j])) % mod1;
        curhash.sc = (curhash.sc * BASE % mod2 + val(str[j])) % mod2;
        even[curhash]++;
      }
    }
    { // update odd
      pll curhash(0, 0);
      for(int j=i-1;~j;--j)
      {
        curhash.fr = (curhash.fr * BASE % mod1 + val(str[j])) % mod1;
        curhash.sc = (curhash.sc * BASE % mod2 + val(str[j])) % mod2;
        odd[curhash]++;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
