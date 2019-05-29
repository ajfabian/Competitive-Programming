#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair

using ll = unsigned long long;

const int N = 1e5+7;


int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n;
  cin >> n;
  vector<ll> a(n);
  for(ll& i: a) cin >> i;
  
  ll res = 0;
  for(ll i: a) res += i * (1ll * n - i + 1ll);
  for(int i=0;i<n-1;++i)
  {
    ll mini = min(a[i], a[i+1]);
    ll maxi = max(a[i], a[i+1]);
    res -= 1ll * (mini) * (1ll * n - maxi + 1ll);
  }
  cout << res << endl;
  
  return 0;
}
