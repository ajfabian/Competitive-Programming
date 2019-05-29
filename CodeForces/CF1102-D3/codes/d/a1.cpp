#include <bits/stdc++.h>
using namespace std;

void printv(vector<int> a)
{
  cerr << "=====\n";
  for(int i: a)
    cerr << i << ' ';
  cerr << "\n=====\n";
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  
  int n; cin >> n;
  string s;
  cin >> s;
  vector<int> a(n);
  vector<int> cur(3, 0), targ(3, n/3);
  for(int i=0;i<n;++i)
  {
    a[i] = s[i] - '0';
    ++cur[a[i]];
  }
  
  auto need = [&]()->int
  {
    int res = 0;
    for(int i=0;i<3;++i) res += abs(cur[i] - targ[i]);
    return res / 2;
  };
  
  string ans = "";
  int csteps = 0, best = need();
  
  for(int i=0;i<n;++i)
  {
    -- cur[a[i]];
    for(int j=0;j<3;++j)
    {
      if(targ[j] == 0) continue;
      --targ[j];
      if(csteps + need() + (a[i] != j) == best)
      {
        csteps += a[i] != j;
        ans += to_string(j);
        break;
      }
      ++targ[j];
    }
  }
  
  cout << ans << endl;
  
  
  
  return 0;
}
