#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define fr first
#define sc second
#define mp make_pair

const int mr[]{0,0,-1,1},
          mc[]{-1,1,0,0};

int main()
{
  int tt;
  scanf("%d", &tt);
  while(tt--)
  {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<pii> plants;
    multiset<pii> fence;
    for(int r, c, i=1;i<=k;++i)
    {
      scanf("%d%d", &r, &c);
      plants.emplace_back(r, c);
      for(int j=0;j<4;++j)
      {
        int nr = r + mr[j];
        int nc = c + mc[j];
        fence.insert(mp(nr, nc));
      }
    }
    
    for(pii _: plants) fence.erase(_);
    printf("%d\n", (int)fence.size());
  }
  return 0;
}
