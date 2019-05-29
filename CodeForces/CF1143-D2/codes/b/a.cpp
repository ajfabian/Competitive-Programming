#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll val[18];

int main()
{
  val[0] = 1;
  for(int i=1;i<18;++i)
    val[i] = val[i-1] * 9ll;
  //~ cerr << "9 ** 17 = " << val[17] << endl;
  
  string s;
  cin >> s;
  
  int n = s.size();
  ll ans = val[n-1], cur = 1;
  for(int i=0;i<n;++i)
  {
    int curd = s[i] - '0';
    for(int d = 1; d < curd;++d)
    {
      ans = max(ans, cur * d * val[n - i - 1]);
    }
    cur = cur * curd;
  }
  cout << max(ans, cur) << endl;
  
  return 0;
}
