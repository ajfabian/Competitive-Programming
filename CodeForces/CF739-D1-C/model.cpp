#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 10;

ll arr[N];

int main()
{
  //~ freopen("in","r",stdin);
  int n;
  int q;
  scanf("%d", &n);
  for(int i=1;i<=n;++i)
    scanf("%lld", &arr[i]);

  scanf("%d", &q);
  while(q--)
  {
    int l, r;
    ll d;
    scanf("%d%d%lld", &l, &r, &d);

    for(int i=l;i<=r;++i)
      arr[i] += d;

    int ans = 1;
    for(int i=1;i<=n;++i)
    {
      int sofar = 0, down = 0;
      if(arr[i+1] == arr[i]) continue;
      for(int j = i;j<=n;++j)
      {
        if(j+1 <= n && arr[j+1] < arr[j])
        {
          down = 1;
        }
        if(j+1 <= n && arr[j+1] > arr[j])
        {
          if(down)
          {
            ++sofar;
            break;
          }
        }
        if(j+1 <= n && arr[j+1] == arr[j])
        {
          ++sofar;
          break;
        }
        ++sofar;
      }
      ans = max(ans, sofar);
    }
    printf("%d\n", ans);
  }
  //~ for(int i=1;i<=n;++i)
    //~ cerr << tmp[i] << " \n"[i == n];
  return 0;
}
