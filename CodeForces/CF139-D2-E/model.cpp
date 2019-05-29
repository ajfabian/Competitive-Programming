#include <bits/stdc++.h>
using namespace std;

struct Mushroom
{
  int a, h, l, r;
};

typedef long double ld;

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  vector<Mushroom> tree;
  for(int i=1;i<=n;++i)
  {
    int a, h, l , r;
    scanf("%d%d%d%d", &a, &h, &l, &r);
    tree.push_back({a, h, l, r});
  }
  //~ cerr << "fuck\n";
  ld ans = 0;
  for(int i=1;i<=m;++i)
  {
    int x, z;
    scanf("%d%d", &x, &z);
    //~ cerr << "mush " << x << ' ' << z << endl;
    ld rans = z;
    for(auto t : tree)
    {
      if( t.l > 0 && t.a - t.h <= x && x < t.a)
        rans *= (100 - t.l) / 100.0;
      
      if( t.r > 0 && t.a < x && x <= t.a + t.h)
        rans *= (100 - t.r) / 100.0;
    }
    //~ cerr << fixed << setprecision(3) << rans << endl;
    ans += rans;
  }
  cout << fixed << setprecision(12) << ans << endl;
  
  return 0;
}
