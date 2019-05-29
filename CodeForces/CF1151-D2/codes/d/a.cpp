#include <bits/stdc++.h>
using namespace std;

#define fr first
#define sc second
#define mp make_pair

using pii = pair<int, int>;

int main()
{
  int n;
  scanf("%d", &n);
  vector<pii> a(n);
  for(pii& i: a) scanf("%d%d", &i.fr, &i.sc);
  
  sort(a.begin(), a.end(), [&](const pii& x, const pii& y)
  {
    return x.fr - x.sc > y.fr - y.sc;
  }
  );
  
  
  long long int ans = 0;
  for(int i=0;i<n;++i)
    ans += 1ll * a[i].fr * (i) + 1ll * a[i].sc * (n - i - 1);
    
  cout << ans << endl;
  
  return 0;
}
