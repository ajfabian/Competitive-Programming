#include <bits/stdc++.h>
using namespace std;

char s[1000007];

int main()
{
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    int n;char x;
    scanf("%d %s %c", &n, s, &x);
    vector<int> nxt(n);
    int last = n;
    for(int i=n-1;~i;--i)
    {
      if(s[i] == x)
      {
        nxt[i] = last;
        last = i;
      }
    }
    //~ cerr << "=======\n";
    long long int ans = 0;
    for(int i=0;i<n;++i)
    {
      if(s[i] == x)
      {
        //~ cerr << "at: " << i << ' ' << (i+1) << ' ' << (nxt[i] - i) << endl;
        ans += 1ll * (i+1) * (nxt[i] - i);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
