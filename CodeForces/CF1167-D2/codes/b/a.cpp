#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define all(x) (x).begin(),(x).end()


void solve(istream &in, ostream &out)
{
  
  cerr << "asd" << endl;
  vector<int> val{4, 8, 15, 16, 23, 42};
  reverse(all(val));

  auto qry = [&](int i, int j)->int
  {
    out << "? " << i << ' ' << j << endl;
    fflush(stdout);
    int res;
    in >> res;
    return res;
  };

  vector<int> P;
  for(int i=2;i<=5;++i)
    P.push_back(qry(1, i));

  int x;
  for(int v: val)
  {
    bool ok = true;
    for(int p: P)
      if(p % v) ok = false;

    if(ok)
    {
      x = v;
      break;
    }
  }

  vector<int> ans{x};

  for(int p: P)
    ans.push_back(p / x);

  for(int v: val)
    if(find(all(ans), v) == ans.end())
    {
      ans.push_back(v);
      break;
    }

  out << "!";
  for(int a: ans)
    out << " " << a;
  out << endl;
  fflush(stdout);

}

int main()
{
  solve(cin,cout);
  return 0;
}
