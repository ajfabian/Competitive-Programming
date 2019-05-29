#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  int p=0, ne=0, z=0;
  for(int i=1;i<=n;++i)
  {
    int x;
    cin >> x;
    if(x > 0) ++p;
    if(x < 0) ++ne;
    if(x == 0) ++z;
  }
  
  int t = (n + 1) / 2;
  cerr << p << ' ' << ne << ' ' << z << endl;
  if(p >= t) return !(cout << "1\n");
  if(ne >= t) return !(cout << "-1\n");
  cout  << "0\n";
  
  return 0;
}
