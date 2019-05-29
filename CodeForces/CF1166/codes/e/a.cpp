#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e4+7;

int main()
{
  
  int n, m;
  scanf("%d%d", &m, &n);
  vector<bitset<N>> ve;
  for(int i=0;i<m;++i)
  {
    int k;
    scanf("%d", &k);
    ve.push_back(bitset<N>());
    while(k--)
    {
      int x;
      scanf("%d", &x);
      --x;
      ve.back().set(x);
    }
  }
  
  for(int i=0;i<m;++i)
    for(int j=0;j<m;++j) if(i != j)
    {
      if((ve[i] & ve[j]) == bitset<N>())
        return !(cout<<"impossible\n");
    }
    
    
  cout << "possible\n";


  return 0;
}
